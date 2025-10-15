#include <iostream>
using namespace std;

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
    bool empty() {
        return isEmpty();
    }
};

class SpecialStack {
    LLStack<int> st;     // main stack
    LLStack<int> minSt;  // auxiliary stack to track minimums

public:
    void push(int elem) {
        st.push(elem);
        if (minSt.empty() || elem <= minSt.peek()) {
            minSt.push(elem);
        }
        else {
            minSt.push(minSt.peek());
        }
    }

    void pop() {
        if (st.empty()) {
            cout << "Stack is empty\n";
            return;
        }
        st.pop();
        minSt.pop();
    }

    int top() {
        if (st.empty()) {
            cout << "Stack is empty\n";
            return -1;
        }
        return st.peek();
    }

    int getMin() {
        if (minSt.empty()) {
            cout << "Stack is empty\n";
            return -1;
        }
        return minSt.peek();
    }
};

int main() {
    SpecialStack s;
    s.push(5);
    s.push(2);
    s.push(8);
    s.push(1);

    cout << "Current Min: " << s.getMin() << endl;
    s.pop();
    cout << "Current Min after pop: " << s.getMin() << endl;

    return 0;
}
