#include <iostream>
#include <vector>
using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
  TreeNode *sortedArrayToBST(vector<int> &nums)
  {
    return helper(nums, 0, nums.size() - 1);
  }

private:
  TreeNode *helper(vector<int> &nums, int left, int right)
  {
    if (left > right)
    {
      return nullptr;
    }

    int mid = left + (right - left) / 2;
    TreeNode *root = new TreeNode(nums[mid]);

    root->left = helper(nums, left, mid - 1);
    root->right = helper(nums, mid + 1, right);

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
  Solution sol;
  vector<int> nums = {-10, -3, 0, 5, 9};

  TreeNode *root = sol.sortedArrayToBST(nums);

  cout << "Inorder traversal of BST: ";
  inorder(root);
  cout << endl;

  return 0;
}