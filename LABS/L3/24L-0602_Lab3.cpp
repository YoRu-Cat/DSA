#include <iostream>
#include <string>
using namespace std;
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node(T data = T()) {
        this->data = data;
        next = NULL;
        prev = NULL;
    }
};
template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
public:
    DoublyLinkedList() {
        head = tail = NULL;
    }
    void insertAtStart(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (head == NULL) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    void insertAtEnd(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (tail == NULL) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void insertAtPosition(int pos, T data) {
        if (pos < 0) {
            cout << "Invalid position\n";
            return;
        }
        if (pos == 0) {
            insertAtStart(data);
            return;
        }
        Node<T>* temp = head;
        int idx = 0;
        while (temp != NULL && idx < pos - 1) {
            temp = temp->next;
            idx++;
        }
        if (temp == NULL) {
            cout << "Position out of bounds\n";
            return;
        }
        if (temp->next == NULL) {
            insertAtEnd(data);
            return;
        }
        Node<T>* newNode = new Node<T>(data);
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
    }
    void deleteFromBeginning() {
        if (head == NULL) {
            cout << "List is empty\n";
            return;
        }
        Node<T>* temp = head;
        if (head == tail) {
            head = tail = NULL;
        }
        else {
            head = head->next;
            head->prev = NULL;
        }
        delete temp;
    }
    void deleteFromEnd() {
        if (tail == NULL) {
            cout << "List is empty\n";
            return;
        }
        Node<T>* temp = tail;
        if (head == tail) {
            head = tail = NULL;
        }
        else {
            tail = tail->prev;
            tail->next = NULL;
        }
        delete temp;
    }
    void deleteData(T value) {
        if (head == NULL) {
            cout << "List is empty\n";
            return;
        }
        Node<T>* temp = head;
        while (temp != NULL && temp->data != value) {
            temp = temp->next;
        }
        if (temp == NULL) {
            cout << "Element not found\n";
            return;
        }
        if (temp == head) {
            deleteFromBeginning();
        }
        else if (temp == tail) {
            deleteFromEnd();
        }
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
    }
    void displayForward() {
        Node<T>* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void displayBackward() {
        Node<T>* temp = tail;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }
    void traverse() {
        cout << "Forward: ";
        displayForward();
        cout << "Backward: ";
        displayBackward();
    }
    int search(T value) {
        Node<T>* temp = head;
        int pos = 0;
        while (temp) {
            if (temp->data == value)
                return pos;
            pos++;
            temp = temp->next;
        }
        return -1;
    }
};

class PlaylistManager {
private:
    DoublyLinkedList<string> playlist;
public:
    void addSong(const string& songName) {
        playlist.insertAtEnd(songName);
    }
    void deleteSong(const string& songName) {
        playlist.deleteData(songName);
    }
    void showForward() {
        playlist.displayForward();
    }
    void showBackward() {
        playlist.displayBackward();
    }
};

int main() {
    cout << "Manual 3 node creation and linking\n";
    Node<int>* n1 = new Node<int>(1);
    Node<int>* n2 = new Node<int>(2);
    Node<int>* n3 = new Node<int>(3);
    n1->next = n2;
    n2->next = n3;
    n3->prev = n2;
    n2->prev = n1;
    cout << "Forward: ";
    Node<int>* temp = n1;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "\nBackward: ";
    temp = n3;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->prev;
    }
    cout << endl << endl;
    DoublyLinkedList<int> dll;
    cout << "Insertions\n";
    dll.insertAtStart(10);
    cout << "After inserting 10 at start: ";
    dll.traverse();
    dll.insertAtEnd(20);
    cout << "After inserting 20 at end: ";
    dll.traverse();
    dll.insertAtEnd(30);
    cout << "After inserting 30 at end: ";
    dll.traverse();
    dll.insertAtPosition(2, 40);
    cout << "After inserting 40 at position 2: ";
    dll.traverse();
    cout << "\nDeletions\n";
    dll.deleteFromBeginning();
    cout << "After deleting from beginning: ";
    dll.displayForward();
    dll.deleteFromEnd();
    cout << "After deleting from end: ";
    dll.displayForward();
    dll.deleteData(20);
    cout << "After deleting node with value 20: ";
    dll.displayForward();
    cout << "\nSearch\n";
    dll.insertAtEnd(30);
    dll.insertAtEnd(60);
    cout << "Final list: ";
    dll.displayForward();
    int pos = dll.search(30);
    if (pos != -1)
        cout << "Element 30 found at position: " << pos << endl;
    else
        cout << "Element 30 not found\n";
    pos = dll.search(50);
    if (pos != -1)
        cout << "Element 50 found at position: " << pos << endl;
    else
        cout << "Element 50 not found\n";
    delete n1; delete n2; delete n3;
    cout << endl << endl;
    PlaylistManager pm;
    pm.addSong("Song1");
    pm.addSong("Song2");
    pm.addSong("Song3");
    pm.addSong("Song4");
    pm.addSong("Song5");
    pm.deleteSong("Song3");
    cout << "Playlist forward: ";
    pm.showForward();
    cout << "Playlist backward: ";
    pm.showBackward();
    return 0;
}


// Reversing the doubly linked list is very easy.
// It can allocate or reallocate memory easily during its execution.
// As with a singly linked list, it is the easiest data structure to implement.
// The traversal of this doubly linked list is bidirectional which is not possible in a singly linked list.