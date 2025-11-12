class Solution
{
public:
  TreeNode *balanceBST(TreeNode *root)
  {
    vector<int> arr;
    inorder(root, arr);
    return buildBalanced(arr, 0, arr.size() - 1);
  }

private:
  void inorder(TreeNode *node, vector<int> &arr)
  {
    if (!node)
      return;
    inorder(node->left, arr);
    arr.push_back(node->val);
    inorder(node->right, arr);
  }

  TreeNode *buildBalanced(vector<int> &arr, int start, int end)
  {
    if (start > end)
      return nullptr;

    int mid = start + (end - start) / 2;
    TreeNode *node = new TreeNode(arr[mid]);

    node->left = buildBalanced(arr, start, mid - 1);
    node->right = buildBalanced(arr, mid + 1, end);

    return node;
  }
};
