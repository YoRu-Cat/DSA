#include <iostream>
using namespace std;

template <typename T>
class BinaryTree {
private:
    class Node {
    public:
        T data;
        Node* left;
        Node* right;
        Node(T val) {
            data = val;
            left = right = NULL;
        }
    };
    Node* root;

    Node* insert(Node* node, T val) {
        if (node == NULL) {
            return new Node(val);
        }
        if (val < node->data) {
            node->left = insert(node->left, val);
        }
        else {
            node->right = insert(node->right, val);
        }
        return node;
    }

    void inorder(Node* node) {
        if (node == NULL) 
            return;
        inorder(node->left);
        cout << node->data << endl;
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == NULL) 
            return;
        cout << node->data << endl;
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == NULL) 
            return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << endl;
    }

    int height(Node* node) {
        if (node == NULL) 
            return 0;
        int lHeight = height(node->left);
        int rHeight = height(node->right);
        return 1 + (lHeight > rHeight ? lHeight : rHeight);
    }

    int countLeaves(Node* node) {
        if (node == NULL) 
            return 0;
        if (node->left == NULL && node->right == NULL) 
            return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }

public:
    BinaryTree() {
        root = NULL;
    }

    void insert(T val) {
        root = insert(root, val);
    }

    void inorder() {
        inorder(root);
    }

    void preorder() {
        preorder(root);
    }

    void postorder() {
        postorder(root);
    }

    int height() {
        return height(root);
    }

    int countLeaves() {
        return countLeaves(root);
    }
};

int main() {
    BinaryTree<int> bt;
    bt.insert(10);
    bt.insert(5);
    bt.insert(15);
    bt.insert(3);
    bt.insert(7);
    bt.insert(12);
    bt.insert(18);

    cout << "Inorder traversal:" << endl;
    bt.inorder();

    cout << "Height of tree: " << bt.height() << endl;
    cout << "Total leaf nodes: " << bt.countLeaves() << endl;

    return 0;
}
