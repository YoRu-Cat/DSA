// Definition for singly-linked list.
struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Definition for a binary tree node.
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
  TreeNode *sortedListToBST(ListNode *head)
  {
    int length = GetLen(head);
    return helper(head, 0, length - 1);
  }

private:
  int GetLen(ListNode *head)
  {
    int leng = 0;
    while (head)
    {
      leng++;
      head = head->next;
    }
    return leng;
  }
  TreeNode *helper(ListNode *&head, int left, int right)
  {
    if (left > right)
    {
      return nullptr;
    }
    int mid = left + (right - left) / 2;
    TreeNode *leftC = helper(head, left, mid - 1);
    TreeNode *root = new TreeNode(head->val);
    head = head->next;
    TreeNode *rightC = helper(head, mid + 1, right);
    root->left = leftC;
    root->right = rightC;
    return root;
  }
};