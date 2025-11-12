#include <vector>
using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
  TreeNode *bstFromPreorder(vector<int> &preorder)
  {
    int index = 0;
    return constructBSTHelper(preorder, index, INT_MIN, INT_MAX);
  }

private:
  TreeNode *constructBSTHelper(vector<int> &preorder, int &index, int minVal, int maxVal)
  {
    if (index >= preorder.size())
      return nullptr;

    int val = preorder[index];
    if (val < minVal || val > maxVal)
      return nullptr;

    index++;
    TreeNode *root = new TreeNode(val);
    root->left = constructBSTHelper(preorder, index, minVal, val);
    root->right = constructBSTHelper(preorder, index, val, maxVal);

    return root;
  }
};
