#include <iostream>
using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BST
{
public:
  TreeNode *trimBST(TreeNode *root, int low, int high)
  {
    if (!root)
      return nullptr;

    // If current node's value is less than low, trim left subtree
    if (root->val < low)
    {
      return trimBST(root->right, low, high);
    }

    // If current node's value is greater than high, trim right subtree
    if (root->val > high)
    {
      return trimBST(root->left, low, high);
    }

    // Current node is within range, recursively trim both subtrees
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);

    return root;
  }

  void inorder(TreeNode *root)
  {
    if (root)
    {
      inorder(root->left);
      cout << root->val << " ";
      inorder(root->right);
    }
  }
};

int main()
{
  BST bst;

  // Create sample BST: 3, 0, 4, null, 2, null, null, 1
  TreeNode *root = new TreeNode(3);
  root->left = new TreeNode(0);
  root->right = new TreeNode(4);
  root->left->right = new TreeNode(2);
  root->left->right->left = new TreeNode(1);

  cout << "Original BST: ";
  bst.inorder(root);
  cout << endl;

  root = bst.trimBST(root, 1, 3);

  cout << "Trimmed BST [1,3]: ";
  bst.inorder(root);
  cout << endl;

  return 0;
}