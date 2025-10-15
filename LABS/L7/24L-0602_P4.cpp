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
        if (node == NULL) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void mirror(Node* node) {
        if (node == NULL)
            return;
        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;
        mirror(node->left);
        mirror(node->right);
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
        cout << endl;
    }

    void mirror() {
        mirror(root);
    }
};

int main() {
    BinaryTree<int> bt;
    int nodes[] = { 4, 2, 5, 1, 3 };
    for (int val : nodes) {
        bt.insert(val);
    }

    cout << "Inorder before mirror: ";
    bt.inorder();

    bt.mirror();

    cout << "Inorder after mirror: ";
    bt.inorder();

    return 0;
}
