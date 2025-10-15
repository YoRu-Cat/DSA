#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Tag
{
  string tagName;
  int lineNumber;

  Tag(string name = "", int line = 0)
  {
    tagName = name;
    lineNumber = line;
  }

  bool operator==(const Tag &other) const
  {
    return tagName == other.tagName;
  }
};

// Simple linked list node template for Stack
template <typename T>
class Node
{
public:
  T data;
  Node *next;

  Node(const T &val)
  {
    data = val;
    next = nullptr;
  }
};

// Stack implemented via linked list
template <typename T>
class Stack
{
private:
  Node<T> *top;

public:
  Stack()
  {
    top = nullptr;
  }
  bool isEmpty() const
  {
    return top == nullptr;
  }
  void push(const T &val)
  {
    Node<T> *newNode = new Node<T>(val);
    newNode->next = top;
    top = newNode;
  }
  bool pop()
  {
    if (isEmpty())
    {
      return false;
    }
    Node<T> *temp = top;
    top = top->next;
    delete temp;
    return true;
  }
  bool peak(T &val) const
  {
    if (isEmpty())
      return false;
    val = top->data;
    return true;
  }
  bool matchesTop(const T &val) const
  {
    if (isEmpty())
      return false;
    T topVal;
    if (!peak(topVal))
      return false;
    return val == topVal;
  }
};

class XMLParser
{
private:
  Stack<Tag> stack;
  int lineNumber;
  bool errorFound;
  vector<string> correctedLines;

public:
  XMLParser()
  {
    lineNumber = 0;
    errorFound = false;
  }

  // Utility to extract tag name ignoring attributes
  string extractTagName(const string &tag)
  {
    string name;
    size_t i = 0;
    // Skip initial '<' and '/'
    while (i < tag.length() && (tag[i] == '<' || tag[i] == '/'))
      i++;
    // Read until space, '>', or '/'
    while (i < tag.length() && tag[i] != ' ' && tag[i] != '>' && tag[i] != '/')
    {
      name += tag[i++];
    }
    return name;
  }

  void parse(const string &filename)
  {
    ifstream file(filename);
    if (!file.is_open())
    {
      cout << "File nahi khul rahi: " << filename << endl;
      return;
    }

    string line;
    lineNumber = 0;
    bool insideComment = false;
    errorFound = false;
    correctedLines.clear();

    cout << "=== XML Parsing Started ===" << endl;

    while (getline(file, line))
    {
      lineNumber++;
      string originalLine = line;
      bool lineModified = false;

      for (size_t i = 0; i < line.length(); ++i)
      {
        if (insideComment)
        {
          if (i + 2 < line.length() && line.substr(i, 3) == "-->")
          {
            insideComment = false;
            i += 2;
          }
          continue;
        }
        if (i + 3 < line.length() && line.substr(i, 4) == "<!--")
        {
          insideComment = true;
          i += 3;
          continue;
        }
        if (line[i] == '<')
        {
          size_t closePos = line.find('>', i);
          if (closePos == string::npos)
          {
            cout << "Error: Incomplete tag at line " << lineNumber << endl;
            cout << "Partial tag: " << line.substr(i) << endl
                 << endl;
            break;
          }
          string tag = line.substr(i, closePos - i + 1);

          // Quote fix karte hain
          string fixedTag = fixQuotesInTag(tag);
          if (fixedTag != tag)
          {
            cout << "Error: Quote issue fixed in tag at line " << lineNumber << endl;
            cout << "Original: " << tag << endl;
            cout << "Fixed: " << fixedTag << endl
                 << endl;

            // Line mein tag replace karte hain
            line.replace(i, tag.length(), fixedTag);
            closePos = i + fixedTag.length() - 1;
            tag = fixedTag;
            lineModified = true;
            errorFound = true;
          }

          bool isClosing = (tag.length() > 2 && tag[1] == '/');
          bool isSelfClosing = (tag.length() > 1 && tag[tag.length() - 2] == '/');

          string tagName = extractTagName(tag);

          if (isSelfClosing)
          {
            // Self closing tag, kuch nahi karna
          }
          else if (isClosing)
          {
            Tag topTag;
            if (!stack.peak(topTag))
            {
              cout << "Error: Closing tag without opening: " << tagName << " at line " << lineNumber << endl;
              errorFound = true;
            }
            else if (topTag.tagName == tagName)
            {
              stack.pop();
            }
            else
            {
              cout << "Error: Mismatched closing tag" << endl;
              cout << "Expected: </" << topTag.tagName << ">" << endl;
              cout << "Found: </" << tagName << ">" << endl;
              cout << "Line: " << lineNumber << endl;

              // Fix karte hain
              string correctTag = "</" + topTag.tagName + ">";
              line.replace(i, tag.length(), correctTag);
              lineModified = true;
              errorFound = true;

              cout << "Fixed to: " << correctTag << endl
                   << endl;
              stack.pop();
            }
          }
          else
          {
            stack.push(Tag(tagName, lineNumber));
          }

          i = closePos;
        }
      }

      correctedLines.push_back(line);
    }

    // Unclosed tags ke liye closing tags add karte hain
    vector<string> missingClosers;
    Tag leftover;
    while (stack.peak(leftover))
    {
      cout << "Error: Unclosed tag found" << endl;
      cout << "Tag: " << leftover.tagName << endl;
      cout << "Opened at line: " << leftover.lineNumber << endl;

      string closer = "</" + leftover.tagName + ">";
      missingClosers.push_back(closer);
      errorFound = true;

      cout << "Adding closing tag: " << closer << endl
           << endl;
      stack.pop();
    }

    // Missing closers add karte hain
    for (const string &closer : missingClosers)
    {
      correctedLines.push_back(closer);
    }

    file.close();

    // Corrected file banate hain agar errors the
    if (errorFound)
    {
      createCorrectedFile(filename);
    }
    else
    {
      cout << "XML file is valid. No errors found." << endl;
    }

    cout << "=== Parsing Complete ===" << endl;
  }

  // Quote issues fix karte hain
  string fixQuotesInTag(const string &tag)
  {
    string fixed = tag;
    char currentQuote = '\0';
    string attributeName = "";
    bool needsClosing = false;

    for (size_t i = 0; i < fixed.length(); i++)
    {
      char c = fixed[i];

      // Attribute name track karte hain
      if (currentQuote == '\0' && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
      {
        attributeName = "";
        size_t start = i;
        while (i < fixed.length() && fixed[i] != '=' && fixed[i] != ' ' && fixed[i] != '>')
        {
          attributeName += fixed[i];
          i++;
        }
        i--; // Loop increment ke liye adjust
        continue;
      }

      if (c == '"' || c == '\'')
      {
        if (currentQuote == c)
        {
          currentQuote = '\0'; // close quote
          needsClosing = false;
        }
        else if (currentQuote == '\0')
        {
          currentQuote = c; // open quote
          needsClosing = true;
        }
        else
        {
          // Quote type mismatch - expected quote add karte hain
          fixed.insert(i, 1, currentQuote);
          currentQuote = '\0';
          needsClosing = false;
        }
      }
      else if (c == '>' && needsClosing && currentQuote != '\0')
      {
        // Tag end ho gya but quote band nahi - close karte hain
        fixed.insert(i, 1, currentQuote);
        needsClosing = false;
        currentQuote = '\0';
      }
    }

    return fixed;
  }

  void createCorrectedFile(const string &originalFilename)
  {
    string correctedFilename = originalFilename + ".fixed.xml";
    ofstream outFile(correctedFilename);

    if (!outFile.is_open())
    {
      cout << "Error creating file: " << correctedFilename << endl;
      return;
    }

    for (size_t i = 0; i < correctedLines.size(); i++)
    {
      outFile << correctedLines[i];
      if (i < correctedLines.size() - 1)
      {
        outFile << endl;
      }
    }

    outFile.close();
    cout << "Corrected file created: " << correctedFilename << endl;
  }

  void createSampleFiles()
  {
    // Error XML file
    ofstream errorFile("sample_errors.xml");
    if (errorFile.is_open())
    {
      errorFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
      errorFile << "<root>" << endl;
      errorFile << "  <student id=\"69>" << endl; // Missing closing quote
      errorFile << "    <name>Magia Negra</name>" << endl;
      errorFile << "    <age>20</age>" << endl;
      errorFile << "  </person>" << endl; // Wrong closing tag
      errorFile << "  <student id='96'>" << endl;
      errorFile << "    <name>YoRu</name>" << endl;
      errorFile << "    <course>CS" << endl; // Missing closing tag
      errorFile << "  </student>" << endl;
      errorFile << "  <unclosed>" << endl; // No closer
      errorFile << "</root>" << endl;
      errorFile.close();
      cout << "Sample error file created: sample_errors.xml" << endl;
    }
  }
};

int main()
{
  XMLParser parser;
  int choice;

  cout << "=== XML Parser with Error Correction ===" << endl;

  do
  {
    cout << "\n=== MENU ===" << endl;
    cout << "1. Create sample files" << endl;
    cout << "2. Parse and fix XML file" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
      parser.createSampleFiles();
      cout << "\nSample files created successfully!" << endl;
      break;
    }
    case 2:
    {
      string filename;
      cout << "\nEnter XML filename to parse: ";
      cin >> filename;
      cout << endl;
      parser.parse(filename);
      break;
    }
    case 3:
    {
      cout << "\nExiting program..." << endl;
      break;
    }
    default:
    {
      cout << "\nInvalid choice! Please select between 1-3." << endl;
      break;
    }
    }
  } while (choice != 3);

  return 0;
}
