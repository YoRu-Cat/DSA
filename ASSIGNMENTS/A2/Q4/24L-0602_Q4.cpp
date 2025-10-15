#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// Simple stack using linked nodes
template <class T>
class Stack
{
private:
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
  Node *topNode;

public:
  Stack()
  {
    topNode = nullptr;
  }

  ~Stack()
  {
    T temp;
    while (pop(temp))
    {
    }
  }
  bool IsEmpty()
  {
    return topNode == nullptr;
  }

  bool push(const T &val)
  {
    Node *newNode = new Node(val);
    newNode->next = topNode;
    topNode = newNode;
    return true;
  }

  bool pop(T &val)
  {
    if (IsEmpty())
    {
      return false;
    }
    val = topNode->data;
    Node *temp = topNode;
    topNode = topNode->next;
    delete temp;
    return true;
  }
};

int getDigit(int number, int d)
{
  return (number / static_cast<int>(pow(10, d))) % 10;
}

// String ke character separate  kara ke lia
int getCharIndex(const string &str, int d, int maxLen)
{
  int pos = maxLen - 1 - d;
  if (pos >= 0 && pos < str.length())
  {
    return str[pos] - 'a';
  }
  return 0; // Treat missing characters as 'a'
}

// Radix Sort for Integers
void radixSortInt(vector<int> &arr)
{
  int n = arr.size();
  if (n == 0)
  {
    return;
  }

  // Find max number to know max digits
  int maxVal = arr[0];
  for (int i = 1; i < n; i++)
  {
    if (arr[i] > maxVal)
    {
      maxVal = arr[i];
    }
  }

  int maxDigits = 0;
  while (maxVal > 0)
  {
    maxVal /= 10;
    maxDigits++;
  }

  // 10 stacks bane digits ke lia
  Stack<int> digitStacks[10];
  Stack<int> tempStack;

  for (int d = 0; d < maxDigits; d++)
  {
    // Put numbers in stacks based on d-th digit
    for (int i = 0; i < n; i++)
    {
      int digit = getDigit(arr[i], d);
      digitStacks[digit].push(arr[i]);
    }

    // Collect numbers back to array in the right order
    int index = 0;
    for (int digit = 0; digit < 10; digit++)
    {
      int val;
      while (digitStacks[digit].pop(val))
      {
        tempStack.push(val);
      }

      // Pop from temp stack back to array
      while (tempStack.pop(val))
      {
        arr[index++] = val;
      }
    }
  }
}

// Radix Sort for Strings
void radixSortString(vector<string> &arr)
{
  int n = arr.size();
  if (n == 0)
  {
    return;
  }

  // Find maximum length string
  int maxLen = 0;
  for (int i = 0; i < n; i++)
  {
    if (arr[i].length() > maxLen)
    {
      maxLen = arr[i].length();
    }
  }

  // 26 stacks letters ke lia
  Stack<string> charStacks[26];
  Stack<string> tempStack;

  // Sort from rightmost character to leftmost
  for (int d = 0; d < maxLen; d++)
  {
    // Strings ko character ke base pa stack mein input kara
    for (int i = 0; i < n; i++)
    {
      int charIndex = getCharIndex(arr[i], d, maxLen);
      charStacks[charIndex].push(arr[i]);
    }

    // Waps array mein collect karo
    int index = 0;
    for (int c = 0; c < 26; c++)
    {
      string val;
      while (charStacks[c].pop(val))
      {
        tempStack.push(val);
      }

      while (tempStack.pop(val))
      {
        arr[index++] = val;
      }
    }
  }
}

int main()
{
  int choice;

  cout << "=== Radix Sort Implementation ===" << endl;
  cout << "Choose sorting type:" << endl;
  cout << "1. Integer Radix Sort" << endl;
  cout << "2. String Radix Sort" << endl;
  cout << "3. Demo both sorts" << endl;
  cout << "Enter choice (1-3): ";
  cin >> choice;

  switch (choice)
  {
  case 1:
  {
    vector<int> intArr = {170, 45, 75, 90, 802, 24, 2, 66};

    cout << "\n--- Integer Radix Sort ---" << endl;
    cout << "Before sorting: ";
    for (int v : intArr)
    {
      cout << v << " ";
    }
    cout << endl;

    radixSortInt(intArr);

    cout << "After sorting: ";
    for (int v : intArr)
    {
      cout << v << " ";
    }
    cout << endl;
    break;
  }

  case 2:
  {
    vector<string> strArr = {"cat", "dog", "apple", "ball", "car", "ant", "bat"};

    cout << "\n--- String Radix Sort ---" << endl;
    cout << "Before sorting: ";
    for (const string &s : strArr)
    {
      cout << s << " ";
    }
    cout << endl;

    radixSortString(strArr);

    cout << "After sorting: ";
    for (const string &s : strArr)
    {
      cout << s << " ";
    }
    cout << endl;
    break;
  }

  case 3:
  {
    // Demo Integer Sort
    vector<int> intArr = {170, 45, 75, 90, 802, 24, 2, 66};

    cout << "\n--- Integer Radix Sort Demo ---" << endl;
    cout << "Before sorting: ";
    for (int v : intArr)
    {
      cout << v << " ";
    }
    cout << endl;

    radixSortInt(intArr);

    cout << "After sorting: ";
    for (int v : intArr)
    {
      cout << v << " ";
    }
    cout << endl;

    // Demo String Sort
    vector<string> strArr = {"cat", "dog", "apple", "ball", "car", "ant", "bat"};

    cout << "\n--- String Radix Sort Demo ---" << endl;
    cout << "Before sorting: ";
    for (const string &s : strArr)
    {
      cout << s << " ";
    }
    cout << endl;

    radixSortString(strArr);

    cout << "After sorting: ";
    for (const string &s : strArr)
    {
      cout << s << " ";
    }
    cout << endl;
    break;
  }

  default:
  {
    cout << "Invalid choice!" << endl;
    break;
  }
  }

  return 0;
}
