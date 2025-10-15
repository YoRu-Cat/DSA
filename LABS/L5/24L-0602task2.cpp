#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
  T data;
  Node<T> *next;
  Node(T value)
  {
    data = value;
    next = nullptr;
  }
};

template <typename T>
class Queue
{
private:
  Node<T> *front;
  Node<T> *rear;

public:
  Queue()
  {
    front = nullptr;
    rear = nullptr;
  }

  bool isEmpty() const
  {
    return front == nullptr;
  }

  void enqueue(const T &value)
  {
    Node<T> *newNode = new Node<T>(value);
    if (isEmpty())
    {
      front = rear = newNode;
    }
    else
    {
      rear->next = newNode;
      rear = newNode;
    }
    cout << value << " enqueued successfully" << endl;
  }

  void dequeue()
  {
    if (isEmpty())
    {
      cout << "Queue Underflow! Cannot dequeue from empty queue" << endl;
      return;
    }
    Node<T> *temp = front;
    cout << front->data << " dequeued successfully" << endl;
    front = front->next;
    if (front == nullptr)
    {
      rear = nullptr; // Queue is empty now
    }
    delete temp;
  }

  void display() const
  {
    if (isEmpty())
    {
      cout << "Queue is empty" << endl;
      return;
    }
    cout << "Queue elements: ";
    Node<T> *temp = front;
    while (temp != nullptr)
    {
      cout << temp->data << " ";
      temp = temp->next;
    }
    cout << endl;
  }

  ~Queue()
  {
    while (!isEmpty())
    {
      dequeue();
    }
  }
};

int main()
{
  Queue<int> q;
  int choice, value;

  do
  {
    cout << "\nMenu:\n";
    cout << "1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter value to enqueue: ";
      cin >> value;
      q.enqueue(value);
      break;
    case 2:
      q.dequeue();
      break;
    case 3:
      q.display();
      break;
    case 4:
      cout << "Exiting program\n";
      break;
    default:
      cout << "Invalid choice!\n";
    }
  } while (choice != 4);

  return 0;
}
