#include <iostream>
using namespace std;

template <typename T>
class CircularNode
{
public:
    T data;
    CircularNode<T> *next;
    CircularNode(T data = T())
    {
        this->data = data;
        next = NULL;
    }
};

template <typename T>
class JosephusCircle
{
private:
    CircularNode<T> *tail;

public:
    JosephusCircle()
    {
        tail = NULL;
    }
    // Create circular linked list with N nodes
    void create(int N)
    {
        for (int i = 1; i <= N; i++)
        {
            insertAtEnd(i);
        }
    }
    void insertAtEnd(T data)
    {
        CircularNode<T> *newNode = new CircularNode<T>(data);
        if (tail == NULL)
        {
            tail = newNode;
            tail->next = tail;
        }
        else
        {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
    }

    T solveJosephus(int k)
    {
        if (tail == NULL)
            return T();

        CircularNode<T> *head = tail->next; // start from head
        CircularNode<T> *prev = tail;

        // Continue eliminating till only one node remains
        while (head->next != head)
        {
            // count to k-th node
            for (int count = 1; count < k; count++)
            {
                prev = head;
                head = head->next;
            }
            // head is kth node to remove
            cout << "Killing: " << head->data << endl;
            prev->next = head->next;
            if (head == tail)
            {
                tail = prev; // update tail if removed node is tail
            }
            delete head;
            head = prev->next;
        }
        return head->data;
    }
};

int main()
{
    int N, k;
    cout << "Enter number of people (N): ";
    cin >> N;
    cout << "Enter step count (k): ";
    cin >> k;

    JosephusCircle<int> jc;
    jc.create(N);

    int survivor = jc.solveJosephus(k);
    cout << "Last person remaining is at position: " << survivor << endl;

    return 0;
}
