#include <iostream>
#include <cctype>

using namespace std;

template <typename T>
class LLStack
{
private:
    struct Node
    {
        T data;
        Node *next;
    };
    Node *top;

public:
    LLStack()
    {
        top = nullptr;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }
    void push(T elem)
    {
        Node *newNode = new Node;
        newNode->data = elem;
        newNode->next = top;
        top = newNode;
    }
    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return T();
        }
        Node *temp = top;
        T val = top->data;
        top = top->next;
        delete temp;
        return val;
    }
    T peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return T();
        }
        return top->data;
    }
};

bool isMatchingPair(char c1, char c2)
{
    return (c1 == '(' && c2 == ')') ||
           (c1 == '{' && c2 == '}') ||
           (c1 == '[' && c2 == ']');
}

bool isBalanced(string expr)
{
    LLStack<char> stack;
    for (char ch : expr)
    {
        if (ch == '(' || ch == '{' || ch == '[')
        {
            stack.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (stack.isEmpty())
                return false;
            char topChar = stack.pop();
            if (!isMatchingPair(topChar, ch))
                return false;
        }
    }
    return stack.isEmpty();
}

int evaluatePostfix(string expr)
{
    LLStack<int> stack;
    for (char ch : expr)
    {
        if (isdigit(ch))
        { // im assuming i can use cctype to check if char is digit
            stack.push(ch - '0');
        }
        else
        {
            int val1 = stack.pop();
            int val2 = stack.pop();
            switch (ch)
            {
            case '+':
                stack.push(val2 + val1);
                break;
            case '-':
                stack.push(val2 - val1);
                break;
            case '*':
                stack.push(val2 * val1);
                break;
            case '/':
                stack.push(val2 / val1);
                break;
            }
        }
    }
    return stack.pop();
}

int preced(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

string infixToPostfix(string expr)
{
    LLStack<char> st;
    string result = "";

    for (char c : expr)
    {
        // using cctype to check if its an alphabet ot a number
        if (isalnum(c))
        {
            result += c;
        }
        // If '(', push kar dana stack man
        else if (c == '(')
        {
            st.push(c);
        }
        // If ')', pop until '(' nai mil jata
        else if (c == ')')
        {
            while (!st.isEmpty() && st.peek() != '(')
            {
                result += st.pop();
            }
            if (!st.isEmpty())
                st.pop(); // pop '('
        }
        else
        {
            while (!st.isEmpty() && preced(st.peek()) >= preced(c))
            {
                result += st.pop();
            }
            st.push(c);
        }
    }
    // Pop remaining operators
    while (!st.isEmpty())
    {
        result += st.pop();
    }
    return result;
}
int main()
{
    string exp1 = "{[()]})";
    cout << exp1 << " is " << (isBalanced(exp1) ? "Balanced" : "Not Balanced") << endl;

    string exp2 = "{([)]}";
    cout << exp2 << " is " << (isBalanced(exp2) ? "Balanced" : "Not Balanced") << endl;

    string exp3 = "{[()]}";
    cout << exp3 << " is " << (isBalanced(exp3) ? "Balanced" : "Not Balanced") << endl;

    string exp4 = "{[()]}{}";
    cout << exp4 << " is " << (isBalanced(exp4) ? "Balanced" : "Not Balanced") << endl;

    string postfixExp = "23*54*+9-";
    cout << "Postfix Expression: " << postfixExp << endl;
    int result = evaluatePostfix(postfixExp);
    cout << "Evaluated Result: " << result << endl;

    string infixExp = "(A+B)*C";
    cout << "Infix Expression: " << infixExp << endl;
    string infix = infixToPostfix(infixExp);
    cout << "Postfix Expression: " << infix << endl;
    return 0;
}
