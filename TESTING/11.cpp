#include <iostream>
using namespace std;

template <typename T>
class AVLTree
{
  struct Node
  {
    T key;
    Node *left;
    Node *right;
    int height;

    Node(T k)
    {
      key = k;
      left = right = NULL;
      height = 1;
    }
  };

  Node *root;

  int LL_rotations, RR_rotations, LR_rotations, RL_rotations;

  int max(int a, int b)
  {
    return (a > b) ? a : b;
  }

  int height(Node *N)
  {
    if (N == NULL)
      return 0;
    return N->height;
  }

  Node *rightRotate(Node *y)
  {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
  }

  Node *leftRotate(Node *x)
  {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
  }

  int getBalance(Node *N)
  {
    if (N == NULL)
      return 0;
    return height(N->left) - height(N->right);
  }

  Node *insert(Node *node, T key)
  {
    if (node == NULL)
      return new Node(key);
    if (key < node->key)
      node->left = insert(node->left, key);
    else if (key > node->key)
      node->right = insert(node->right, key);
    else
      return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
    {
      LL_rotations++;
      return rightRotate(node);
    }
    if (balance < -1 && key > node->right->key)
    {
      RR_rotations++;
      return leftRotate(node);
    }
    if (balance > 1 && key > node->left->key)
    {
      LR_rotations++;
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key)
    {
      RL_rotations++;
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
    return node;
  }

  Node *minValueNode(Node *node)
  {
    Node *current = node;
    while (current->left != NULL)
      current = current->left;
    return current;
  }

  Node *deleteNode(Node *root, T key)
  {
    if (root == NULL)
      return root;

    if (key < root->key)
      root->left = deleteNode(root->left, key);
    else if (key > root->key)
      root->right = deleteNode(root->right, key);
    else
    {
      if ((root->left == NULL) || (root->right == NULL))
      {
        Node *temp = root->left ? root->left : root->right;
        if (temp == NULL)
        {
          temp = root;
          root = NULL;
        }
        else
        {
          *root = *temp;
        }
        delete temp;
      }
      else
      {
        Node *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
      }
    }
    if (root == NULL)
      return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
    {
      LL_rotations++;
      return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0)
    {
      LR_rotations++;
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
    {
      RR_rotations++;
      return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0)
    {
      RL_rotations++;
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
    return root;
  }

  void preOrder(Node *root)
  {
    if (root != NULL)
    {
      int bal = getBalance(root);
      cout << root->key << "(" << root->height << "," << bal << ") ";
      preOrder(root->left);
      preOrder(root->right);
    }
  }

  int treeHeight(Node *root)
  {
    if (root == NULL)
      return 0;
    int lh = treeHeight(root->left);
    int rh = treeHeight(root->right);
    return 1 + (lh > rh ? lh : rh);
  }

  void printLevel(Node *root, int level)
  {
    if (root == NULL)
      return;
    if (level == 1)
    {
      int bal = getBalance(root);
      cout << root->key << "(" << root->height << "," << bal << ") ";
    }
    else if (level > 1)
    {
      printLevel(root->left, level - 1);
      printLevel(root->right, level - 1);
    }
  }

  // BFS traversal without queue
  void bfs(Node *root)
  {
    int h = treeHeight(root);
    for (int i = 1; i <= h; i++)
    {
      printLevel(root, i);
    }
  }

  // BFS search for a key
  bool bfsSearch(Node *root, T key)
  {
    int h = treeHeight(root);
    for (int i = 1; i <= h; i++)
    {
      if (searchAtLevel(root, key, i))
        return true;
    }
    return false;
  }

  bool searchAtLevel(Node *root, T key, int level)
  {
    if (root == NULL)
      return false;
    if (level == 1)
    {
      if (root->key == key)
        return true;
    }
    else if (level > 1)
    {
      if (searchAtLevel(root->left, key, level - 1) ||
          searchAtLevel(root->right, key, level - 1))
        return true;
    }
    return false;
  }

  // DFS traversals
  void dfsPreOrder(Node *root)
  {
    if (root != NULL)
    {
      int bal = getBalance(root);
      cout << root->key << "(" << root->height << "," << bal << ") ";
      dfsPreOrder(root->left);
      dfsPreOrder(root->right);
    }
  }

  void dfsInOrder(Node *root)
  {
    if (root != NULL)
    {
      dfsInOrder(root->left);
      int bal = getBalance(root);
      cout << root->key << "(" << root->height << "," << bal << ") ";
      dfsInOrder(root->right);
    }
  }

  void dfsPostOrder(Node *root)
  {
    if (root != NULL)
    {
      dfsPostOrder(root->left);
      dfsPostOrder(root->right);
      int bal = getBalance(root);
      cout << root->key << "(" << root->height << "," << bal << ") ";
    }
  }

  // DFS search for a key
  bool dfsSearch(Node *root, T key)
  {
    if (root == NULL)
      return false;
    if (root->key == key)
      return true;
    return dfsSearch(root->left, key) || dfsSearch(root->right, key);
  }

  bool validateAVL(Node *root)
  {
    if (root == NULL)
      return true;
    int lh = height(root->left);
    int rh = height(root->right);
    if (abs(lh - rh) > 1)
      return false;
    if (!validateAVL(root->left) || !validateAVL(root->right))
      return false;
    return true;
  }

public:
  AVLTree()
  {
    root = NULL;
    LL_rotations = RR_rotations = LR_rotations = RL_rotations = 0;
  }

  void insert(T key)
  {
    root = insert(root, key);
  }

  void remove(T key)
  {
    root = deleteNode(root, key);
  }

  void printPreOrder()
  {
    preOrder(root);
    cout << endl;
  }

  void printLevelOrder()
  {
    int h = treeHeight(root);
    for (int i = 1; i <= h; i++)
    {
      printLevel(root, i);
      cout << endl;
    }
  }

  void printBFS()
  {
    cout << "BFS Traversal: ";
    bfs(root);
    cout << endl;
  }

  bool searchBFS(T key)
  {
    return bfsSearch(root, key);
  }

  // DFS public methods
  void printDFSPreOrder()
  {
    cout << "DFS PreOrder: ";
    dfsPreOrder(root);
    cout << endl;
  }

  void printDFSInOrder()
  {
    cout << "DFS InOrder: ";
    dfsInOrder(root);
    cout << endl;
  }

  void printDFSPostOrder()
  {
    cout << "DFS PostOrder: ";
    dfsPostOrder(root);
    cout << endl;
  }

  bool searchDFS(T key)
  {
    return dfsSearch(root, key);
  }

  bool isBalanced()
  {
    return validateAVL(root);
  }

  void printRotations()
  {
    cout << "LL Rotations: " << LL_rotations << endl;
    cout << "RR Rotations: " << RR_rotations << endl;
    cout << "LR Rotations: " << LR_rotations << endl;
    cout << "RL Rotations: " << RL_rotations << endl;
  }
};

int main()
{
  AVLTree<int> tree;

  int insertKeys[] = {10, 20, 30, 40, 50, 25};
  for (int k : insertKeys)
    tree.insert(k);

  cout << "Preorder after insertion: ";
  tree.printPreOrder();
  cout << "\nLevel order after insertion: " << endl;
  tree.printLevelOrder();

  cout << "\nBFS Traversal: ";
  tree.printBFS();

  cout << "\nDFS Traversals:" << endl;
  tree.printDFSPreOrder();
  tree.printDFSInOrder();
  tree.printDFSPostOrder();

  cout << "\nBFS Search for 25: " << (tree.searchBFS(25) ? "FOUND" : "NOT FOUND") << endl;
  cout << "BFS Search for 35: " << (tree.searchBFS(35) ? "FOUND" : "NOT FOUND") << endl;

  cout << "DFS Search for 25: " << (tree.searchDFS(25) ? "FOUND" : "NOT FOUND") << endl;
  cout << "DFS Search for 35: " << (tree.searchDFS(35) ? "FOUND" : "NOT FOUND") << endl;

  tree.remove(40);

  cout << "\nPreorder after deletion: ";
  tree.printPreOrder();
  cout << "\nLevel order after deletion: " << endl;
  tree.printLevelOrder();

  cout << "\nTree Balanced: " << (tree.isBalanced() ? "TRUE" : "FALSE") << endl;

  cout << "\nRotations Summary: " << endl;
  tree.printRotations();

  return 0;
}