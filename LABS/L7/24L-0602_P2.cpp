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

    Node* iteraInsert(Node* node, T val) {
        if (node == NULL) {
            return new Node(val);
        }
        Node* current = node;
        while (true) {
            if (val < current->data) {
                if (current->left == NULL) {
                    current->left = new Node(val);
                    break;
                }
                else {
                    current = current->left;
                }
            }
            else if (val > current->data) {
                if (current->right == NULL) {
                    current->right = new Node(val);
                    break;
                }
                else {
                    current = current->right;
                }
            }
            else {
                break;
            }
        }
        return node;
    }

    bool Search(Node* node, T val, int& comparisons) {
        if (node == NULL) {
            return false;
        }
        comparisons++;
        if (node->data == val) {
            return true;
        }
        else if (val < node->data) {
            return Search(node->left, val, comparisons);
        }
        else {
            return Search(node->right, val, comparisons);
        }
    }

    void inorder(Node* node) {
        if (node == NULL) return;
        inorder(node->left);
        cout << node->data << endl;
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == NULL) return;
        cout << node->data << endl;
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == NULL) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << endl;
    }

public:
    BinaryTree() : root(NULL) {}

    void insert(T val) {
        root = insert(root, val);
    }

    void iteraInsert(T val) {
        root = iteraInsert(root, val);
    }

    bool Search(T val, int& comparisons) {
        return Search(root, val, comparisons);
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
};

int main() {
    int seq[] = { 50, 30, 70, 20, 40, 60, 80 };
    BinaryTree<int> bst;

    for (int val : seq) {
        bst.insert(val);
    }

    cout << "Inorder traversal:" << endl;
    bst.inorder();
    cout << endl;

    int comparisons = 0;
    int searchVal = 60;
    bool found = bst.Search(searchVal, comparisons);
    if (found) {
        cout << "Element " << searchVal << " found in the BST. ";
    }
    else {
        cout << "Element " << searchVal << " not found in the BST. ";
    }
    cout << "Comparisons made: " << comparisons << endl << endl;

    BinaryTree<int> bstIter;
    for (int val : seq) {
        bstIter.iteraInsert(val);
    }
    cout << "Inorder traversal after iterative inserts:" << endl;
    bstIter.inorder();
    cout << endl;

    return 0;
}
