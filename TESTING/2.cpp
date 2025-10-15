#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
  T data;
  Node<T> *next;
  Node<T> *prev;
  Node(T data = T())
  {
    this->data = data;
    next = NULL;
    prev = NULL;
  }
};

template <typename T>
class DoublyLinkList
{
private:
  Node<T> *tail;

public:
  DoublyLinkList()
  {
    tail = NULL;
  }
  void insertAtStart(T data)
  {
    Node<T> *newNode = new Node<T>(data);
    if (tail == NULL)
    {
      tail = newNode;
    }
    else
    {
      newNode->next = tail->next;
      newNode->prev = tail;
      tail->next->prev = newNode;
      tail->next = newNode;
    }
  }
  void insertAtEnd(T data)
  {
    Node<T> *newNode = new Node<T>(data);
    if (tail == NULL)
    {
      tail = newNode;
      tail->next = tail;
      tail->prev = tail;
    }
    else
    {
      newNode->next = tail->next;
      newNode->prev = tail;
      tail->next->prev = newNode;
      tail->next = newNode;
      tail = newNode;
    }
  }
  void insertAtPosition(T data, int pos)
  {
    if (pos < 0)
    {
      cout << "Invalid position " << endl;
      return;
    }
    if (pos == 0)
    {
      insertAtStart(data);
      return;
    }
    Node<T> *temp = tail->next; // head
    int cnt = 0;
    while (cnt < pos - 1 && temp != tail)
    {
      temp = temp->next;
      cnt++;
    }
    if (temp == tail)
    {
      insertAtEnd(data);
      return;
    }
    Node<T> *newNode = new Node<T>(data);
    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
  }
  void deletefromBegining()
  {
    if (tail == NULL)
    {
      cout << "List is empty ";
      return;
    }
    Node<T> *head = tail->next;
    if (tail == head)
    {
      delete head;
      tail = NULL;
    }
    else
    {
      tail->next = head->next;
      head->next->prev = tail;
      delete head;
    }
  }
  void deletefromEnd()
  {
    if (tail == NULL)
    {
      cout << "List is empty ";
      return;
    }
    Node<T> *head = tail->next;
    if (tail == head)
    {
      delete head;
      tail = NULL;
    }
    else
    {
      tail->prev->next = head;
      head->prev = tail->prev;
      delete tail;
      tail = tail->prev;
    }
  }
  void deletefromPos(T data)
  {
    if (tail == NULL)
    {
      cout << "List is empty ";
      return;
    }
    Node<T> *head = tail->next;
    bool found = false;
    do
    {
      if (head->data == data)
      {
        found = true;
        break;
      }
      if (!found)
      {
        cout << "Element not found ";
        return;
      }
      break;
    }
    if (head == tail && head == tail->next)
    {
      delete head;
      tail = NULL;
    }
    else
    {
      head->next->prev = head->prev;
      head->prev->next = head->next;
      if (head == tail)
      {
        tail = head->prev;
      }
      delete head;
    }
  }
  T search(T value)
  {
    if (tail == NULL)
    {
      cout << "List is empty" << endl;
      return T();
    }
    Node<T> *head = tail->next;
    do
    {
      if (head->data == value)
      {
        return head->data;
      }
      head = head->next;
    } while (head != tail->next);
    return T();
  }

  void removeSubList(T start, T end)
  {
    if (tail == NULL)
    {
      cout << "List is empty ";
      return;
    }
    Node<T> *head = tail->next;
    Node<T> *startNode = NULL;
    Node<T> *endNode = NULL;
    bool foundStart = false;
    bool foundEnd = false;

    do
    {
      if (head->data == start)
      {
        startNode = head;
        foundStart = true;
      }
      if (head->data == end && foundStart)
      {
        endNode = head;
        foundEnd = true;
        break;
      }
      head = head->next;
    } while (head != tail->next);

    if (!foundStart || !foundEnd)
    {
      cout << "Sublist not found ";
      return;
    }

    if (startNode == tail->next && endNode == tail)
    {
      delete head;
      tail = NULL;
      return;
    }

    startNode->prev->next = endNode->next;
    endNode->next->prev = startNode->prev;

    if (tail >= startNode && tail <= endNode)
    {
      tail = startNode->prev;
    }

    Node<T> *temp = startNode;
    while (temp != endNode)
    {
      Node<T> *next = temp->next;
      delete temp;
      temp = next;
    }
    delete endNode;
  }
  void merge(DoublyLinkList<T> &other)
  {
    if (other.tail == NULL)
      return;
    if (tail == NULL)
    {
      tail = other.tail;
      other.tail = NULL;
      return;
    }

    Node<T> *thisHead = tail->next;
    Node<T> *otherHead = other.tail->next;

    tail->next = otherHead;
    otherHead->prev = tail;
    other.tail->next = thisHead;
    thisHead->prev = other.tail;
    tail = other.tail;

    other.tail = NULL;
  }

  void sort()
  {
    if (tail == NULL || tail->next == tail)
      return;

    bool swapped;
    Node<T> *current;
    do
    {
      swapped = false;
      current = tail->next;
      do
      {
        if (current->data > current->next->data)
        {
          T temp = current->data;
          current->data = current->next->data;
          current->next->data = temp;
          swapped = true;
        }
        current = current->next;
      } while (current != tail);
    } while (swapped);
  }
  // Iterator class for traversing the doubly linked list
  class Iterator
  {
  private:
    Node<T> *current; // Pointer to current node in iteration

  public:
    // Constructor initializes the iterator with a node
    Iterator(Node<T> *node)
    {
      current = node;
    }

    // Get the data at current position
    T &operator*()
    {
      return current->data;
    }

    // Move to next node (prefix increment)
    Iterator &operator++()
    {
      if (current != NULL)
      {
        current = current->next;
      }
      return *this;
    }

    // Move to previous node (prefix decrement)
    Iterator &operator--()
    {
      if (current != NULL)
      {
        current = current->prev;
      }
      return *this;
    }

    // Compare two iterators
    bool operator!=(const Iterator &other)
    {
      return current != other.current;
    }
  };

  // Returns iterator pointing to first element
  Iterator begin()
  {
    if (tail == NULL)
    {
      return Iterator(NULL);
    }
    return Iterator(tail->next); // Points to head
  }

  // Returns iterator pointing to position after last element
  Iterator end()
  {
    if (tail == NULL)
    {
      return Iterator(NULL);
    }
    return Iterator(NULL); // Points to null for end iterator
  }

  // Returns iterator pointing to last element
  Iterator rbegin()
  {
    if (tail == NULL)
    {
      return Iterator(NULL);
    }
    return Iterator(tail);
  }

  // Returns iterator pointing to position before first element
  Iterator rend()
  {
    if (tail == NULL)
    {
      return Iterator(NULL);
    }
    return Iterator(tail->next->prev);
  }

  // Delete the longest sequence of a given value
  void deleteLongestSequence(T value)
  {
    if (tail == NULL)
    {
      cout << "List is empty" << endl;
      return;
    }

    Node<T> *current = tail->next; // Start from head
    Node<T> *seqStart = NULL;
    Node<T> *longestSeqStart = NULL;

    int currentLength = 0;
    int maxLength = 0;

    do
    {
      if (current->data == value)
      {
        if (currentLength == 0)
        {
          seqStart = current;
        }
        currentLength++;

        if (currentLength > maxLength)
        {
          maxLength = currentLength;
          longestSeqStart = seqStart;
        }
      }
      else
      {
        currentLength = 0;
      }

      current = current->next;
    } while (current != tail->next);

    // If no sequence found
    if (maxLength == 0)
    {
      return;
    }

    // Delete the longest sequence
    Node<T> *seqEnd = longestSeqStart;
    for (int i = 1; i < maxLength; i++)
    {
      seqEnd = seqEnd->next;
    }

    // If the sequence covers the entire list
    if (maxLength == 1 && tail == tail->next)
    {
      delete tail;
      tail = NULL;
      return;
    }

    // Adjust pointers
    seqEnd->next->prev = longestSeqStart->prev;
    longestSeqStart->prev->next = seqEnd->next;

    // If sequence contains tail, update tail
    if (tail >= longestSeqStart && tail <= seqEnd)
    {
      tail = longestSeqStart->prev;
    }

    // Delete nodes in sequence
    current = longestSeqStart;
    while (current != seqEnd->next)
    {
      Node<T> *temp = current;
      current = current->next;
      delete temp;
    }
  }
};

int main()
{
  DoublyLinkList<int> list;

  // Testing insertion operations
  list.insertAtStart(10);
  list.insertAtEnd(20);
  list.insertAtPosition(15, 1);

  // Testing deletion operations
  list.deletefromBegining();
  list.deletefromEnd();
  list.deletefromPos(15);

  // Testing search
  int found = list.search(10);
  cout << "Search result: " << found << endl;

  // Testing sublist removal
  list.insertAtEnd(30);
  list.insertAtEnd(40);
  list.insertAtEnd(50);
  list.removeSubList(30, 50);

  // Testing merge
  DoublyLinkList<int> list2;
  list2.insertAtEnd(60);
  list2.insertAtEnd(70);
  list.merge(list2);

  // Testing sort
  list.sort();

  // Testing iterator
  cout << "Forward iteration: ";
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}