#include <iostream>
using namespace std;

// Node class for linked list implementations
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

// 1. Queue using Array
template <typename T>
class QueueArray
{
private:
  static const int MAX_SIZE = 5;
  T arr[MAX_SIZE];
  int front;
  int rear;

public:
  QueueArray()
  {
    front = -1;
    rear = -1;
  }

  bool isEmpty()
  {
    return (front == -1 && rear == -1);
  }

  bool isFull()
  {
    return (rear + 1) % MAX_SIZE == front;
  }

  void enqueue(T value)
  {
    if (isFull())
    {
      cout << "Queue Overflow! Cannot enqueue " << value << endl;
      return;
    }
    if (isEmpty())
    {
      front = rear = 0;
    }
    else
    {
      rear = (rear + 1) % MAX_SIZE;
    }
    arr[rear] = value;
    cout << value << " enqueued successfully" << endl;
  }

  void dequeue()
  {
    if (isEmpty())
    {
      cout << "Queue Underflow! Cannot dequeue from empty queue" << endl;
      return;
    }
    cout << arr[front] << " dequeued successfully" << endl;
    if (front == rear)
    {
      front = rear = -1;
    }
    else
    {
      front = (front + 1) % MAX_SIZE;
    }
  }

  void display()
  {
    if (isEmpty())
    {
      cout << "Queue is empty" << endl;
      return;
    }
    cout << "Queue elements: ";
    int i = front;
    while (true)
    {
      cout << arr[i] << " ";
      if (i == rear)
        break;
      i = (i + 1) % MAX_SIZE;
    }
    cout << endl;
  }
};

// 2. Queue using Linked List
template <typename T>
class QueueLinkedList
{
private:
  Node<T> *front;
  Node<T> *rear;

public:
  QueueLinkedList()
  {
    front = nullptr;
    rear = nullptr;
  }

  bool isEmpty()
  {
    return front == nullptr;
  }

  void enqueue(T value)
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
      rear = nullptr;
    }
    delete temp;
  }

  void display()
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

  ~QueueLinkedList()
  {
    while (!isEmpty())
    {
      dequeue();
    }
  }
};

// 3. Circular Queue using Array
template <typename T>
class CircularQueueArray
{
private:
  static const int MAX_SIZE = 5;
  T arr[MAX_SIZE];
  int front;
  int rear;

public:
  CircularQueueArray()
  {
    front = -1;
    rear = -1;
  }

  bool isEmpty()
  {
    return front == -1 && rear == -1;
  }

  bool isFull()
  {
    return (rear + 1) % MAX_SIZE == front;
  }

  void enqueue(T value)
  {
    if (isFull())
    {
      cout << "Queue Overflow! Cannot enqueue " << value << endl;
      return;
    }
    if (isEmpty())
    {
      front = rear = 0;
    }
    else
    {
      rear = (rear + 1) % MAX_SIZE;
    }
    arr[rear] = value;
    cout << value << " enqueued successfully" << endl;
  }

  void dequeue()
  {
    if (isEmpty())
    {
      cout << "Queue Underflow! Cannot dequeue from empty queue" << endl;
      return;
    }
    cout << arr[front] << " dequeued successfully" << endl;
    if (front == rear)
    {
      front = rear = -1;
    }
    else
    {
      front = (front + 1) % MAX_SIZE;
    }
  }

  void display()
  {
    if (isEmpty())
    {
      cout << "Queue is empty" << endl;
      return;
    }
    cout << "Queue elements: ";
    int i = front;
    while (true)
    {
      cout << arr[i] << " ";
      if (i == rear)
        break;
      i = (i + 1) % MAX_SIZE;
    }
    cout << endl;
  }
};

// 4. Circular Queue using Linked List
template <typename T>
class CircularQueueLinkedList
{
private:
  Node<T> *rear;

public:
  CircularQueueLinkedList()
  {
    rear = nullptr;
  }

  bool isEmpty()
  {
    return rear == nullptr;
  }

  void enqueue(T value)
  {
    Node<T> *newNode = new Node<T>(value);
    if (isEmpty())
    {
      newNode->next = newNode;
      rear = newNode;
    }
    else
    {
      newNode->next = rear->next;
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
    Node<T> *front = rear->next;
    cout << front->data << " dequeued successfully" << endl;
    if (front == rear)
    {
      delete front;
      rear = nullptr;
    }
    else
    {
      rear->next = front->next;
      delete front;
    }
  }

  void display()
  {
    if (isEmpty())
    {
      cout << "Queue is empty" << endl;
      return;
    }
    cout << "Queue elements: ";
    Node<T> *temp = rear->next;
    do
    {
      cout << temp->data << " ";
      temp = temp->next;
    } while (temp != rear->next);
    cout << endl;
  }

  ~CircularQueueLinkedList()
  {
    while (!isEmpty())
    {
      dequeue();
    }
  }
};

void arrayQueue()
{
  QueueArray<int> q;
  int choice, value;

  do
  {
    cout << endl
         << "Queue using Array Operations:" << endl;
    cout << "1. Enqueue" << endl
         << "2. Dequeue" << endl
         << "3. Display" << endl
         << "4. Back to Main Menu" << endl;
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
      cout << "Returning to main menu" << endl;
      break;
    default:
      cout << "Invalid choice!" << endl;
    }
  } while (choice != 4);
}

void linkedQueue()
{
  QueueLinkedList<int> q;
  int choice, value;

  do
  {
    cout << endl
         << "Queue using Linked List Operations:" << endl;
    cout << "1. Enqueue" << endl
         << "2. Dequeue" << endl
         << "3. Display" << endl
         << "4. Back to Main Menu" << endl;
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
      cout << "Returning to main menu" << endl;
      break;
    default:
      cout << "Invalid choice!" << endl;
    }
  } while (choice != 4);
}

void circularArray()
{
  CircularQueueArray<int> cq;
  int choice, value;

  do
  {
    cout << "Circular Queue using Array Operations:" << endl;
    cout << "1. Enqueue" << endl
         << "2. Dequeue" << endl
         << "3. Display" << endl
         << "4. Back to Main Menu" << endl;
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
      cout << "Returning to main menu" << endl;
      break;
    default:
      cout << "Invalid choice!" << endl;
    }
  } while (choice != 4);
}

void circularLinked()
{
  CircularQueueLinkedList<int> cq;
  int choice, value;

  do
  {
    cout << endl
         << "Circular Queue using Linked List Operations:" << endl;
    cout << "1. Enqueue" << endl
         << "2. Dequeue" << endl
         << "3. Display" << endl
         << "4. Back to Main Menu" << endl;
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
      cout << "Returning to main menu" << endl;
      break;
    default:
      cout << "Invalid choice!" << endl;
    }
  } while (choice != 4);
}

int main()
{
  int mainChoice;

  do
  {
    cout << endl
         << "=== Queue Implementation Menu ===" << endl;
    cout << "1. Queue using Array" << endl;
    cout << "2. Queue using Linked List" << endl;
    cout << "3. Circular Queue using Array" << endl;
    cout << "4. Circular Queue using Linked List" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> mainChoice;

    switch (mainChoice)
    {
    case 1:
      arrayQueue();
      break;
    case 2:
      linkedQueue();
      break;
    case 3:
      circularArray();
      break;
    case 4:
      circularLinked();
      break;
    case 5:
      cout << "Exiting program" << endl;
      break;
    default:
      cout << "Invalid choice!" << endl;
    }
  } while (mainChoice != 5);

  return 0;
}