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
class CircularQueue
{
private:
  Node<T> *rear; // Points to the last node; rear->next is the front

public:
  CircularQueue()
  {
    rear = nullptr;
  }

  bool isEmpty() const
  {
    return rear == nullptr;
  }

  void enqueue(const T &value)
  {
    Node<T> *newNode = new Node<T>(value);
    if (isEmpty())
    {
      newNode->next = newNode; // Circular link to itself
      rear = newNode;
    }
    else
    {
      newNode->next = rear->next; // New node points to front
      rear->next = newNode;       // Old rear points to new node
      rear = newNode;             // New node becomes rear
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
    Node<T> *front = rear->next;
    cout << front->data << " dequeued successfully" << endl;
    if (front == rear)
    { // Only one node
      delete front;
      rear = nullptr;
    }
    else
    {
      rear->next = front->next;
      delete front;
    }
  }

  void display() const
  {
    if (isEmpty())
    {
      cout << "Queue is empty" << endl;
      return;
    }
    cout << "Queue elements: ";
    Node<T> *temp = rear->next; // Start from front
    do
    {
      cout << temp->data << " ";
      temp = temp->next;
    } while (temp != rear->next);
    cout << endl;
  }

  ~CircularQueue()
  {
    while (!isEmpty())
    {
      dequeue();
    }
  }
};

int main()
{
  CircularQueue<int> cq;
  int choice, value;

  do
  {
    cout << "\nMenu: " << endl;
    cout << "1. Enqueue\n2. Dequeue\n3. Display\n4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter value to enqueue: ";
      cin >> value;
      cq.enqueue(value);
      break;
    case 2:
      cq.dequeue();
      break;
    case 3:
      cq.display();
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
