#include <iostream>
using namespace std;

template <typename T>
class CircularQueue
{
private:
  static const int MAX_SIZE = 5;
  T arr[MAX_SIZE];
  int front;
  int rear;

public:
  CircularQueue()
  {
    front = -1;
    rear = -1;
  }

  bool isEmpty() const
  {
    return front == -1 && rear == -1;
  }

  bool isFull() const
  {
    return (rear + 1) % MAX_SIZE == front;
  }

  void enqueue(const T &value)
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
      rear = (rear + 1) % MAX_SIZE; // Wrap around here
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
    { // Queue becomes empty after dequeue
      front = rear = -1;
    }
    else
    {
      front = (front + 1) % MAX_SIZE; // Wrap around here
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
    int i = front;
    while (true)
    {
      cout << arr[i] << " ";
      if (i == rear)
        break;
      i = (i + 1) % MAX_SIZE; // Wrap around while displaying
    }
    cout << endl;
  }
};

int main()
{
  CircularQueue<int> cq;
  int choice, value;

  do
  {
    cout << "\nMenu:\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\nEnter your choice: ";
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
