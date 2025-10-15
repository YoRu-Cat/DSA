#include <iostream>
using namespace std;

template <typename T>
class ArrStack {
private:
    T* array;
    int size;
    int top;

    bool isEmpty() {
        return top == -1;
    }
    bool isFull() {
        return top == size - 1;
    }
public:
    ArrStack(int tsize = 10) {  // Constructor name fixed to ArrStack and default size added
        top = -1;
        size = tsize;
        array = new T[size];
    }
    void push(T elem) {
        if (isFull()) {
            cout << "Stack is full" << endl;
            return;
        }
        array[++top] = elem;
        cout << "Pushed data: " << array[top] << endl;
    }
    T pop() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return T();
        }
        return array[top--];  // 'arr' corrected to 'array'
    }
    T peek() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return T();
        }
        return array[top];    // 'arr' corrected to 'array'
    }
};

template <typename T>
class LLStack {
private:
    struct Node {
        T data;
        Node* next;
    };
    Node* top;

    bool isEmpty() {
        return top == nullptr;
    }

public:
    LLStack() {
        top = nullptr;
    }
    void push(T elem) {
        Node* newNode = new Node;
        newNode->data = elem;
        newNode->next = top;
        top = newNode;
        cout << "Pushed data: " << newNode->data << endl;
    }
    T pop() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return T();
        }
        Node* temp = top;
        T val = top->data;
        top = top->next;
        delete temp;
        return val;
    }
    T peek() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return T();
        }
        return top->data;
    }
};

int main()
{
    ArrStack<int> st1;
    st1.push(11);
    st1.push(19);
    st1.push(69);
    cout << "Popped: " << st1.pop() << endl;
    cout << "Top element: " << st1.peek() << endl;

    LLStack<int> st2;
    st2.push(12);
    st2.push(45);
    st2.push(96);
    cout << "Popped: " << st2.pop() << endl;
    cout << "Top element: " << st2.peek() << endl;
}
