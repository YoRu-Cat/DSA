#include <iostream>
using namespace std;

template <typename T>
class InvertibleStack
{
private:
  T *arr;
  int capacity;
  int size;
  int front; // Top element ka index when normal
  int rear;  // Top element ka index when flipped
  bool isFlipped;

  void resize(int newCapacity)
  {
    T *newArr = new T[newCapacity];

    // Elements ko si order mein copy karo
    for (int i = 0; i < size; i++)
    {
      if (!isFlipped)
      {
        int index = (front - i + capacity) % capacity;
        newArr[i] = arr[index];
      }
      else
      {
        int index = (rear + i) % capacity;
        newArr[i] = arr[index];
      }
    }

    delete[] arr;
    arr = newArr;
    capacity = newCapacity;

    // Pointers reset kar do
    if (size > 0)
    {
      front = size - 1;
      rear = 0;
    }
    else
    {
      front = -1;
      rear = 0;
    }
    isFlipped = false;
  }

  void doubleCapacity()
  {
    resize(capacity * 2);
  }

  void halveCapacity()
  {
    resize(capacity / 2);
  }

public:
  InvertibleStack(int initialCapacity = 4)
  {
    capacity = initialCapacity;
    arr = new T[capacity];
    size = 0;
    front = -1; // First element add hone par 0 ho jayega
    rear = 0;
    isFlipped = false;
  }

  ~InvertibleStack()
  {
    delete[] arr;
  }

  bool isEmpty()
  {
    return size == 0;
  }

  bool isFull()
  {
    return size == capacity;
  }

  void push(T element)
  {
    if (isFull())
    {
      doubleCapacity();
    }

    if (size == 0)
    {
      // First element both pointers isi par point karte hain
      front = 0;
      rear = 0;
      arr[0] = element;
    }
    else if (!isFlipped)
    {
      // Normal mode mein front par push karo
      front = (front + 1) % capacity;
      arr[front] = element;
    }
    else
    {
      // Flipped mode mein rear par push karo
      rear = (rear - 1 + capacity) % capacity;
      arr[rear] = element;
    }
    size++;
  }

  T pop()
  {
    if (isEmpty())
    {
      cout << "Stack underflow!" << endl;
      return T();
    }

    T element;
    if (!isFlipped)
    {
      // Normal: front se nikalo
      element = arr[front];
      front = (front - 1 + capacity) % capacity;
    }
    else
    {
      // Flipped: rear se nikalo
      element = arr[rear];
      rear = (rear + 1) % capacity;
    }

    size--;

    // Halve capacity agar zyada empty ho
    if (size > 0 && size <= capacity / 4 && capacity > 4)
    {
      halveCapacity();
    }

    return element;
  }
  T peek()
  {
    if (isEmpty())
    {
      cout << "Stack is empty!" << endl;
      return T();
    }

    if (!isFlipped)
    {
      return arr[front];
    }
    else
    {
      return arr[rear];
    }
  }

  void flipStack()
  {
    if (isEmpty())
    {
      return;
    }

    // Bas flag toggle kar do, pointers nai change kara
    isFlipped = !isFlipped;
  }

  void display()
  {
    if (isEmpty())
    {
      cout << "Stack is empty" << endl;
      return;
    }

    cout << "Stack (top to bottom): ";
    for (int i = 0; i < size; i++)
    {
      if (!isFlipped)
      {
        // Normal: start from front, go backwards
        int index = (front - i + capacity) % capacity;
        cout << arr[index] << " ";
      }
      else
      {
        // Flipped: start from rear, go forwards
        int index = (rear + i) % capacity;
        cout << arr[index] << " ";
      }
    }
    cout << endl;
  }

  int getSize()
  {
    return size;
  }

  void displayInfo()
  {
    cout << "Size: " << size << ", Capacity: " << capacity;
    cout << ", Front: " << front << ", Rear: " << rear;
    cout << ", Flipped: " << (isFlipped ? "Yes" : "No") << endl;
  }
};

// Test function
void testInvertibleStack()
{
  InvertibleStack<int> stack;

  cout << "=== Testing Invertible Stack ===" << endl;

  // Push some elements
  cout << "\n1. Pushing elements 1, 2, 3, 4, 5:" << endl;
  for (int i = 1; i <= 5; i++)
  {
    stack.push(i);
  }
  stack.display();
  stack.displayInfo();

  // Test normal pop
  cout << "\n2. Popping one element:" << endl;
  cout << "Popped: " << stack.pop() << endl;
  stack.display();

  // Test flip
  cout << "\n3. Flipping stack:" << endl;
  stack.flipStack();
  stack.display();
  stack.displayInfo();

  // Test pop after flip
  cout << "\n4. Popping after flip:" << endl;
  cout << "Popped: " << stack.pop() << endl;
  stack.display();

  // Test multiple flips
  cout << "\n5. Flipping again:" << endl;
  stack.flipStack();
  stack.display();

  // Push more elements
  cout << "\n6. Pushing 10, 20:" << endl;
  stack.push(10);
  stack.push(20);
  stack.display();
  stack.displayInfo();

  // Test capacity doubling
  cout << "\n7. Pushing more elements to test doubling:" << endl;
  for (int i = 30; i <= 50; i += 10)
  {
    stack.push(i);
  }
  stack.display();
  stack.displayInfo();

  // Test flip with larger stack
  cout << "\n8. Flipping larger stack:" << endl;
  stack.flipStack();
  stack.display();

  // Test capacity halving
  cout << "\n9. Popping many elements to test halving:" << endl;
  while (!stack.isEmpty())
  {
    cout << "Popped: " << stack.pop() << " ";
    if (stack.getSize() % 2 == 0)
    {
      cout << endl;
      stack.displayInfo();
    }
  }
  cout << endl;
}

int main()
{
  int choice;

  do
  {
    cout << "\n=== Invertible Stack Menu ===" << endl;
    cout << "1. Run comprehensive test" << endl;
    cout << "2. Interactive mode" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
      testInvertibleStack();
      break;
    }
    case 2:
    {
      InvertibleStack<int> stack;
      int option, value;

      do
      {
        cout << "\n--- Interactive Stack Operations ---" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Peek" << endl;
        cout << "4. Flip Stack" << endl;
        cout << "5. Display" << endl;
        cout << "6. Show Info" << endl;
        cout << "7. Back to main menu" << endl;
        cout << "Enter option: ";
        cin >> option;

        switch (option)
        {
        case 1:
        {
          cout << "Enter value to push: ";
          cin >> value;
          stack.push(value);
          cout << "Pushed " << value << endl;
          break;
        }
        case 2:
        {
          if (!stack.isEmpty())
          {
            cout << "Popped: " << stack.pop() << endl;
          }
          else
          {
            cout << "Stack is empty!" << endl;
          }
          break;
        }
        case 3:
        {
          if (!stack.isEmpty())
          {
            cout << "Top element: " << stack.peek() << endl;
          }
          else
          {
            cout << "Stack is empty!" << endl;
          }
          break;
        }
        case 4:
        {
          stack.flipStack();
          cout << "Stack flipped!" << endl;
          break;
        }
        case 5:
        {
          stack.display();
          break;
        }
        case 6:
        {
          stack.displayInfo();
          break;
        }
        case 7:
        {
          cout << "Returning to main menu..." << endl;
          break;
        }
        default:
        {
          cout << "Invalid option!" << endl;
          break;
        }
        }
      } while (option != 7);
      break;
    }
    case 3:
    {
      cout << "Exiting program..." << endl;
      break;
    }
    default:
    {
      cout << "Invalid choice!" << endl;
      break;
    }
    }
  } while (choice != 3);

  return 0;
}