#include <iostream>
#include <string>
using namespace std;

// 24L-0602 - Assignment 3: Special BST Implementation

// Part A: SpecialBST Template Class
template <typename K, typename V>
class SpecialBST
{
private:
  class Node
  {
  public:
    K key;
    V val;
    Node *left;
    Node *right;

    Node(const K &k, const V &v)
    {
      key = k;
      val = v;
      left = nullptr;
      right = nullptr;
    }
  };

  Node *root;

  // Right rotation
  Node *rotR(Node *node)
  {
    Node *newR = node->left;
    node->left = newR->right;
    newR->right = node;
    return newR;
  }

  // Left rotation
  Node *rotL(Node *node)
  {
    Node *newR = node->right;
    node->right = newR->left;
    newR->left = node;
    return newR;
  }

  // Node ko root tak le jana
  Node *splay(Node *node, const K &key)
  {
    if (node == nullptr || node->key == key)
    {
      return node;
    }

    // Key is in left subtree
    if (key < node->key)
    {
      if (node->left == nullptr)
      {
        return node;
      }

      if (key < node->left->key)
      {
        node->left->left = splay(node->left->left, key);
        node = rotR(node);
      }
      else if (key > node->left->key)
      {
        node->left->right = splay(node->left->right, key);
        if (node->left->right != nullptr)
        {
          node->left = rotL(node->left);
        }
      }

      return (node->left == nullptr) ? node : rotR(node);
    }
    // Key is in right subtree
    else
    {
      if (node->right == nullptr)
      {
        return node;
      }

      if (key > node->right->key)
      {
        node->right->right = splay(node->right->right, key);
        node = rotL(node);
      }
      else if (key < node->right->key)
      {
        node->right->left = splay(node->right->left, key);
        if (node->right->left != nullptr)
        {
          node->right = rotR(node->right);
        }
      }

      return (node->right == nullptr) ? node : rotL(node);
    }
  }

  // Insert karne ka helper
  Node *ins(Node *node, const K &key, const V &val)
  {
    if (node == nullptr)
    {
      return new Node(key, val);
    }

    if (key < node->key)
    {
      node->left = ins(node->left, key, val);
    }
    else if (key > node->key)
    {
      node->right = ins(node->right, key, val);
    }
    else
    {
      // Duplicate key nahi insert karte
      return node;
    }

    return node;
  }

  // Delete karne ka helper
  Node *del(Node *node, const K &key)
  {
    if (node == nullptr)
    {
      return nullptr;
    }

    if (key < node->key)
    {
      node->left = del(node->left, key);
    }
    else if (key > node->key)
    {
      node->right = del(node->right, key);
    }
    else
    {
      // Delete hone wala node mil gaya
      if (node->left == nullptr)
      {
        Node *temp = node->right;
        delete node;
        return temp;
      }
      else if (node->right == nullptr)
      {
        Node *temp = node->left;
        delete node;
        return temp;
      }

      // Do children wale node ka case - inorder successor dhundo
      Node *temp = node->right;
      while (temp->left != nullptr)
      {
        temp = temp->left;
      }

      node->key = temp->key;
      node->val = temp->val;
      node->right = del(node->right, temp->key);
    }

    return node;
  }

  // Delete hone wale node ka parent dhundo
  Node *findPar(Node *node, const K &key)
  {
    if (node == nullptr || (node->left == nullptr && node->right == nullptr))
    {
      return node;
    }

    if ((node->left != nullptr && node->left->key == key) ||
        (node->right != nullptr && node->right->key == key))
    {
      return node;
    }

    if (key < node->key && node->left != nullptr)
    {
      return findPar(node->left, key);
    }
    else if (key > node->key && node->right != nullptr)
    {
      return findPar(node->right, key);
    }

    return node;
  }

  // Level order traversal helper
  void lvlOrd(Node *node, V *arr, int &idx, int maxS)
  {
    if (node == nullptr || idx >= maxS)
    {
      return;
    }

    // Manual queue implementation using array
    Node **que = new Node *[1000];
    int frnt = 0, rear = 0;

    que[rear++] = node;

    while (frnt < rear && idx < maxS)
    {
      Node *curr = que[frnt++];
      arr[idx++] = curr->val;

      if (curr->left != nullptr)
      {
        que[rear++] = curr->left;
      }
      if (curr->right != nullptr)
      {
        que[rear++] = curr->right;
      }
    }

    delete[] que;
  }

  // Inorder traversal helper
  void inOrd(Node *node, V *arr, int &idx, int maxS)
  {
    if (node == nullptr || idx >= maxS)
    {
      return;
    }

    inOrd(node->left, arr, idx, maxS);
    if (idx < maxS)
    {
      arr[idx++] = node->val;
    }
    inOrd(node->right, arr, idx, maxS);
  }

  // Count nodes
  int cntN(Node *node)
  {
    if (node == nullptr)
    {
      return 0;
    }
    return 1 + cntN(node->left) + cntN(node->right);
  }

  // Destroy tree
  void dest(Node *node)
  {
    if (node != nullptr)
    {
      dest(node->left);
      dest(node->right);
      delete node;
    }
  }

public:
  // Default constructor
  SpecialBST()
  {
    root = nullptr;
  }

  // Destructor
  ~SpecialBST()
  {
    dest(root);
  }

  // Insert function
  bool insert(K key, V val)
  {
    int oldC = cntN(root);
    root = ins(root, key, val);

    if (cntN(root) > oldC)
    {
      // New node inserted - splay it to root
      root = splay(root, key);
      return true;
    }

    // Duplicate key - phir bhi splay kar do
    root = splay(root, key);
    return false;
  }

  // Search function
  V *search(K key)
  {
    root = splay(root, key);

    if (root != nullptr && root->key == key)
    {
      return &(root->val);
    }

    return nullptr;
  }

  // Delete function
  bool delN(K key)
  {
    if (root == nullptr)
    {
      return false;
    }

    // First check if key exists
    Node *temp = root;
    bool found = false;

    while (temp != nullptr)
    {
      if (temp->key == key)
      {
        found = true;
        break;
      }
      else if (key < temp->key)
      {
        temp = temp->left;
      }
      else
      {
        temp = temp->right;
      }
    }

    if (!found)
    {
      return false;
    }

    // Find parent before deletion
    Node *par = findPar(root, key);

    // Delete the node
    root = del(root, key);

    // Splay parent to root
    if (par != nullptr && root != nullptr)
    {
      root = splay(root, par->key);
    }

    return true;
  }

  // Get values level-wise (returns dynamic array)
  V *getValsLvl(int &size)
  {
    size = cntN(root);
    if (size == 0)
    {
      return nullptr;
    }

    V *arr = new V[size];
    int idx = 0;
    lvlOrd(root, arr, idx, size);
    size = idx;
    return arr;
  }

  // Get values inorder (returns dynamic array)
  V *getValsIn(int &size)
  {
    size = cntN(root);
    if (size == 0)
    {
      return nullptr;
    }

    V *arr = new V[size];
    int idx = 0;
    inOrd(root, arr, idx, size);
    size = idx;
    return arr;
  }
};

// Part B: Student class
class Student
{
public:
  int rollNum;
  string fName;
  string lName;
  int batch;
  string dept;
  float cgpa;

  Student()
  {
    rollNum = 0;
    fName = "";
    lName = "";
    batch = 0;
    dept = "";
    cgpa = 0.0f;
  }

  Student(int rn, string fn, string ln, int b, string d, float c)
  {
    rollNum = rn;
    fName = fn;
    lName = ln;
    batch = b;
    dept = d;
    cgpa = c;
  }
};

// Part B: StudentList class
class StudentList
{
private:
  SpecialBST<int, Student> tree;

public:
  bool InsertNewStudent(int rollNumber, string firstName, string lastName, int batch, string department, float cgpa)
  {
    Student std(rollNumber, firstName, lastName, batch, department, cgpa);
    return tree.insert(rollNumber, std);
  }

  bool deleteStudent(int rollNumber)
  {
    return tree.delN(rollNumber);
  }

  bool updateStudent(int oldRollNumber, int newRollNumber, string newFirstName, string newLastName, int newBatch, string newDepartment, float newCgpa)
  {
    // Search for old roll number
    Student *std = tree.search(oldRollNumber);
    if (std == nullptr)
    {
      return false;
    }

    // If roll number is changing, check for duplicate
    if (oldRollNumber != newRollNumber)
    {
      Student *dup = tree.search(newRollNumber);
      if (dup != nullptr)
      {
        return false; // New roll number already exists
      }

      // Delete old entry and insert new one
      tree.delN(oldRollNumber);
      Student newS(newRollNumber, newFirstName, newLastName,
                   newBatch, newDepartment, newCgpa);
      return tree.insert(newRollNumber, newS);
    }
    else
    {
      // Just update the values
      std->fName = newFirstName;
      std->lName = newLastName;
      std->batch = newBatch;
      std->dept = newDepartment;
      std->cgpa = newCgpa;
      return true;
    }
  }

  void printAllStudents()
  {
    int size;
    Student *stds = tree.getValsIn(size);

    if (stds == nullptr)
    {
      cout << "No students found!" << endl;
      return;
    }

    cout << "Total Students: " << size << endl;

    for (int i = 0; i < size; i++)
    {
      cout << "Roll Number: " << stds[i].rollNum << endl;
      cout << "First Name: " << stds[i].fName << endl;
      cout << "Last Name: " << stds[i].lName << endl;
      cout << "Batch: " << stds[i].batch << endl;
      cout << "Department: " << stds[i].dept << endl;
      cout << "CGPA: " << stds[i].cgpa << endl;
      if (i < size - 1)
        cout << endl;
    }

    delete[] stds;
  }

  Student *searchStudent(int rollNumber)
  {
    return tree.search(rollNumber);
  }
};

// Part C: Main program with menu
int main()
{
  StudentList sList;
  char ch;

  cout << "24L-0602 - Assignment 3: Special BST Student Management" << endl;
  cout << "========================================================" << endl;

  do

  {
    cout << "\nPress I to insert a new student." << endl;
    cout << "Press D to delete a student." << endl;
    cout << "Press S to search a student by roll number." << endl;
    cout << "Press U to update the data of a student." << endl;
    cout << "Press P to print all students sorted by roll number." << endl;
    cout << "Press E to exit." << endl;
    cout << "> ";
    cin >> ch;

    switch (ch)
    {
    case 'I':
    case 'i':
    {
      int rn, b;
      string fn, ln, d;
      float c;

      cout << "Please enter the data of new student in the order:" << endl;
      cout << "Roll Number(only integers), First Name, Last Name, Batch(only integers), Department, CGPA(float only)" << endl;
      cout << "> ";
      cin >> rn >> fn >> ln >> b >> d >> c;

      if (sList.InsertNewStudent(rn, fn, ln, b, d, c))
      {
        cout << "New student inserted successfully!" << endl;
      }
      else
      {
        cout << "Roll Number already exists!" << endl;
      }
      break;
    }

    case 'D':
    case 'd':
    {
      int rn;
      cout << "Enter roll number to delete: ";
      cin >> rn;

      if (sList.deleteStudent(rn))
      {
        cout << "Student deleted successfully!" << endl;
      }
      else
      {
        cout << "Student with roll number " << rn << " not found!" << endl;
      }
      break;
    }

    case 'S':
    case 's':
    {
      int rn;
      cout << "Enter roll number to search: ";
      cin >> rn;

      Student *std = sList.searchStudent(rn);
      if (std != nullptr)
      {
        cout << "Student found:" << endl;
        cout << "Roll Number: " << std->rollNum << endl;
        cout << "First Name: " << std->fName << endl;
        cout << "Last Name: " << std->lName << endl;
        cout << "Batch: " << std->batch << endl;
        cout << "Department: " << std->dept << endl;
        cout << "CGPA: " << std->cgpa << endl;
      }
      else
      {
        cout << "Student with roll number " << rn << " not found!" << endl;
      }
      break;
    }

    case 'U':
    case 'u':
    {
      int oldRn, newRn, newB;
      string newFn, newLn, newD;
      float newC;

      cout << "Enter old roll number: ";
      cin >> oldRn;
      cout << "Enter new data (Roll Number, First Name, Last Name, Batch, Department, CGPA): ";
      cin >> newRn >> newFn >> newLn >> newB >> newD >> newC;

      if (sList.updateStudent(oldRn, newRn, newFn, newLn, newB, newD, newC))
      {
        cout << "Student updated successfully!" << endl;
      }
      else
      {
        cout << "Update failed! Either student not found or new roll number already exists." << endl;
      }
      break;
    }

    case 'P':
    case 'p':
    {
      sList.printAllStudents();
      break;
    }

    case 'E':
    case 'e':
    {
      cout << "Exiting program. Thank you!" << endl;
      break;
    }

    default:
    {
      cout << "Invalid choice! Please try again." << endl;
      break;
    }
    }

  } while (ch != 'E' && ch != 'e');

  return 0;
}
