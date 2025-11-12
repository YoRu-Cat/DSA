#include <string>
#include <iostream>
using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec
{
public:
  // Encodes a tree to a single string.
  string serialize(TreeNode *root)
  {
    string result = "";
    preorder(root, result);
    return result;
  }

  void preorder(TreeNode *root, string &result)
  {
    if (!root)
    {
      result += "null,";
      return;
    }
    result += to_string(root->val) + ",";
    preorder(root->left, result);
    preorder(root->right, result);
  }

  // Decodes your encoded data to tree.
  TreeNode *deserialize(string data)
  {
    int idx = 0;
    return buildTree(data, idx);
  }

  TreeNode *buildTree(string &data, int &idx)
  {
    string val = "";
    while (idx < data.length() && data[idx] != ',')
    {
      val += data[idx];
      idx++;
    }
    idx++; // skip comma

    if (val == "null")
      return nullptr;

    TreeNode *root = new TreeNode(stoi(val));
    root->left = buildTree(data, idx);
    root->right = buildTree(data, idx);

    return root;
  }
};
