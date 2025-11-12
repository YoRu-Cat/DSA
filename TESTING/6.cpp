#include <iostream>
using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
private:
  int sum = 0;

public:
  TreeNode *convertBST(TreeNode *root)
  {
    if (root != nullptr)
    {
      convertBST(root->right); // Visit right subtree first
      sum += root->val;        // Add current node value to sum
      root->val = sum;         // Update current node with sum
      convertBST(root->left);  // Visit left subtree
    }
    return root;
  }
};

// Helper function to print inorder traversal
void inorder(TreeNode *root)
{
  if (root)
  {
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
  }
}

int main()
{
  // Example: BST [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
  TreeNode *root = new TreeNode(4);
  root->left = new TreeNode(1);
  root->right = new TreeNode(6);
  root->left->left = new TreeNode(0);
  root->left->right = new TreeNode(2);
  root->right->left = new TreeNode(5);
  root->right->right = new TreeNode(7);
  root->left->right->right = new TreeNode(3);
  root->right->right->right = new TreeNode(8);

  cout << "Original BST: ";
  inorder(root);
  cout << endl;

  Solution sol;
  sol.convertBST(root);

  cout << "Greater Tree: ";
  inorder(root);
  cout << endl;

  return 0;
}