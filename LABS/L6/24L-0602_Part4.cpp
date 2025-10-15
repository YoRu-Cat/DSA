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

class UndoRedo {
    LLStack<string> undoStack;
    LLStack<string> redoStack;
    string currentState;

public:
    UndoRedo(string init = "") {
        currentState = init;
    }

    void doAct(string state) {
        undoStack.push(currentState);
        currentState = state;
        // Clear redoStack on new action
        while (!redoStack.empty()) {
            redoStack.pop();
        }
        cout << "Action done, current state: " << currentState << endl;
    }

    void undo() {
        if (undoStack.empty()) {
            cout << "Nothing to undo" << endl;
            return;
        }
        redoStack.push(currentState);
        currentState = undoStack.pop();
        cout << "Undo performed, current state: " << currentState << endl;
    }

    void redo() {
        if (redoStack.empty()) {
            cout << "Nothing to redo" << endl;
            return;
        }
        undoStack.push(currentState);
        currentState = redoStack.pop();
        cout << "Redo performed, current state: " << currentState << endl;
    }
};

class BrowserNavigation {
    LLStack<string> bkStack;
    LLStack<string> frdStack;
    string currentPage;

public:
    BrowserNavigation(string homepage = "") {
        currentPage = homepage;
    }

    void visit(string url) {
        if (!currentPage.empty()) {
            bkStack.push(currentPage);
        }
        currentPage = url;
        // Clear forward stack when new page is visited
        while (!frdStack.empty()) {
            frdStack.pop();
        }
        cout << "Visited: " << url << endl;
    }

    void back() {
        if (bkStack.empty()) {
            cout << "No page to go back to" << endl;
            return;
        }
        frdStack.push(currentPage);
        currentPage = bkStack.pop();
        cout << "Back to: " << currentPage << endl;
    }

    void forward() {
        if (frdStack.empty()) {
            cout << "No page to go forward to" << endl;
            return;
        }
        bkStack.push(currentPage);
        currentPage = frdStack.pop();
        cout << "Forward to: " << currentPage << endl;
    }
};

int main() {
    // Undo/Redo Simulation
    UndoRedo editor("Text v1");
    editor.doAct("Text v2");
    editor.doAct("Text v3");
    editor.undo();
    editor.undo();
    editor.redo();
    editor.redo();

    cout << "\n";

    // Browser Back/Forward Simulation
    BrowserNavigation browser("home.com");
    browser.visit("page1.com");
    browser.visit("page2.com");
    browser.back();
    browser.back();
    browser.forward();
    browser.visit("page3.com");
    browser.forward();

    return 0;
}
