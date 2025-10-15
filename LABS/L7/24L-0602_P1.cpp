#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
class BinaryTree {
private:
    class Node {
    public:
        T data;
        Node* left;
        Node* right;
        Node(T val = T()) {
            data = val;
            left = right = NULL;
        }
    };

    Node* root;
    Node* insert(Node* root, T val) {
        if (root == NULL) {
            return new Node(val);
        }
        if (val < root->data) {
            root->left = insert(root->left, val);
        }
        else {
            root->right = insert(root->right, val);
        }
        return root;
    }

    void inorder(Node* root) {
        if (root == NULL) return;
        inorder(root->left);
        cout << root->data << endl;
        inorder(root->right);
    }

    void preorder(Node* root) {
        if (root == NULL) return;
        cout << root->data << endl;
        preorder(root->left);
        preorder(root->right);
    }

    void postorder(Node* root) {
        if (root == NULL) return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data << endl;
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
};

int main() {
    ifstream infile("unique_human_names.txt");
    if (!infile) {
        cout << "Error opening file" << endl;
        return -1;
    }

    BinaryTree<string> treeStr;
    string name;

    while (getline(infile, name)) {
        if (!name.empty()) {
            treeStr.insert(name);
        }
    }
    infile.close();

    cout << "Preorder: " << endl;
    treeStr.preorder();
    cout << endl;

    cout << "Inorder: " << endl;
    treeStr.inorder();
    cout << endl;

    cout << "Postorder: " << endl;
    treeStr.postorder();
    cout << endl;

    int nodes[] = { 4, 2, 5, 1, 3 };
    BinaryTree<int> treeInt;
    for (int v : nodes) {
        treeInt.insert(v);
    }

    cout << "Preorder: " << endl;
    treeInt.preorder();
    cout << endl;

    cout << "Inorder: " << endl;
    treeInt.inorder();
    cout << endl;

    cout << "Postorder: " << endl;
    treeInt.postorder();
    cout << endl;

    return 0;
}
