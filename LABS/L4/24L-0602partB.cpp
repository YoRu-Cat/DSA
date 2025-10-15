#include <iostream>
#include <string>
using namespace std;


// Circular doubly linked list node
template <typename T>
class CircularDNode {
public:
    T data;
    CircularDNode<T>* next;
    CircularDNode<T>* prev;
    CircularDNode(T data = T()) {
        this->data = data;
        next = this; // point to itself initially
        prev = this;
    }
};

template <typename T>
class CircularDoublyLinkedList {
private:
    CircularDNode<T>* tail; // Points to last node, tail->next is head
public:
    CircularDoublyLinkedList() {
        tail = NULL;
    }
    // Insert at end
    void insertAtEnd(T data) {
        CircularDNode<T>* newNode = new CircularDNode<T>(data);
        if (tail == NULL) {
            tail = newNode;
        }
        else {
            newNode->next = tail->next;
            newNode->prev = tail;
            tail->next->prev = newNode;
            tail->next = newNode;
            tail = newNode;
        }
    }
    // Insert at beginning
    void insertAtBeginning(T data) {
        CircularDNode<T>* newNode = new CircularDNode<T>(data);
        if (tail == NULL) {
            tail = newNode;
        }
        else {
            newNode->next = tail->next;
            newNode->prev = tail;
            tail->next->prev = newNode;
            tail->next = newNode;
        }
    }
    // Traverse forward and print
    void traverse() {
        if (tail == NULL) {
            cout << "List is empty\n";
            return;
        }
        CircularDNode<T>* temp = tail->next; // head
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != tail->next);
        cout << endl;
    }
    // Traverse backward and print
    void traverseBackward() {
        if (tail == NULL) {
            cout << "List is empty\n";
            return;
        }
        CircularDNode<T>* temp = tail; // tail is last node
        do {
            cout << temp->data << " ";
            temp = temp->prev;
        } while (temp != tail);
        cout << endl;
    }
    // Delete from beginning
    void deleteFromBeginning() {
        if (tail == NULL) {
            cout << "List is empty\n";
            return;
        }
        CircularDNode<T>* head = tail->next;
        if (head == tail) { // Only one node
            delete head;
            tail = NULL;
        }
        else {
            tail->next = head->next;
            head->next->prev = tail;
            delete head;
        }
    }
    // Delete from end
    void deleteFromEnd() {
        if (tail == NULL) {
            cout << "List is empty\n";
            return;
        }
        CircularDNode<T>* head = tail->next;
        if (tail == head) { // Only one node
            delete tail;
            tail = NULL;
        }
        else {
            CircularDNode<T>* temp = tail->prev;
            temp->next = head;
            head->prev = temp;
            delete tail;
            tail = temp;
        }
    }
    // Delete node with specific key
    void deleteData(T key) {
        if (tail == NULL) {
            cout << "List is empty\n";
            return;
        }
        CircularDNode<T>* curr = tail->next; // head
        bool found = false;
        do {
            if (curr->data == key) {
                found = true;
                break;
            }
            curr = curr->next;
        } while (curr != tail->next);
        if (!found) {
            cout << "Element not found\n";
            return;
        }
        if (curr == tail && curr == tail->next) { // only one node
            delete curr;
            tail = NULL;
        }
        else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            if (curr == tail) {
                tail = curr->prev;
            }
            delete curr;
        }
    }
    // Search operation
    int search(T value) {
        if (tail == NULL)
            return -1;
        CircularDNode<T>* temp = tail->next; // head
        int pos = 0;
        do {
            if (temp->data == value)
                return pos;
            temp = temp->next;
            pos++;
        } while (temp != tail->next);
        return -1;
    }
};

int main() {
    cout << "Doubly Circular Linked List Demo\n";

    CircularDoublyLinkedList<int> cdll;

    int choice, val;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert at beginning\n";
        cout << "2. Insert at end\n";
        cout << "3. Delete from beginning\n";
        cout << "4. Delete from end\n";
        cout << "5. Delete by value\n";
        cout << "6. Traverse forward\n";
        cout << "7. Traverse backward\n";
        cout << "8. Search\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter value to insert at beginning: ";
            cin >> val;
            cdll.insertAtBeginning(val);
            break;
        case 2:
            cout << "Enter value to insert at end: ";
            cin >> val;
            cdll.insertAtEnd(val);
            break;
        case 3:
            cdll.deleteFromBeginning();
            break;
        case 4:
            cdll.deleteFromEnd();
            break;
        case 5:
            cout << "Enter value to delete: ";
            cin >> val;
            cdll.deleteData(val);
            break;
        case 6:
            cout << "List forward: ";
            cdll.traverse();
            break;
        case 7:
            cout << "List backward: ";
            cdll.traverseBackward();
            break;
        case 8:
            cout << "Enter value to search: ";
            cin >> val;
            {
                int pos = cdll.search(val);
                if (pos != -1)
                    cout << "Element found at position " << pos << endl;
                else
                    cout << "Element not found\n";
            }
            break;
        case 9:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 9);

    return 0;
}
