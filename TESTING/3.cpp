#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
  T data;
  Node *next;
  Node *prev;
  Node(T data = T())
  {
    this->data = data;
    next = prev = NULL;
  }
};

template <typename T>
class LinkList
{
private:
  Node<T> *tail;

public:
  LinkList()
  {
    tail = NULL;
  }
  void insertAtStart(T data)
  {
    Node<T> *n = new Node<T>(data);
    if (tail == NULL)
    {
      tail = n;
      tail->next = tail; // Make it circular
      tail->prev = tail;
    }
    else
    {
      Node<T> *head = tail->next; // Store original head
      n->next = head;             // New node points to old head
      n->prev = tail;             // New node's prev points to tail
      tail->next = n;             // Tail points to new node (new head)
      head->prev = n;             // Old head's prev points to new node
    }
  }
  void insertAtEnd(T data)
  {
    Node<T> *n = new Node<T>(data);
    if (tail == NULL)
    {
      tail = n;
      tail->next = tail; // Make it circular
      tail->prev = tail;
    }
    else
    {
      n->next = tail->next;
      n->prev = tail;
      tail->next = n;
      tail->next->prev = n;
      tail = n;
    }
  }
  void insertData(int pos, T data)
  {
    if (pos < 0)
    {
      cout << "invalid position nigga";
      return;
    }
    if (pos == 0)
    {
      insertAtStart(data);
      return;
    }
    Node<T> *temp = tail->next;
    for (int i = 0; temp != NULL && i < pos - 1; i++)
    {
      temp = temp->next;
    }
    if (temp == NULL)
    {
      cout << "Position out of bounds ";
      return;
    }
    if (temp->next == NULL)
    {
      insertAtEnd(data);
      return;
    }
    Node<T> *n = new Node<T>(data);
    n->next = temp->next;
    n->prev = temp;
    temp->next = n;
    temp->next->prev = n;
  }
  void deleteFromStart()
  {
    if (tail == NULL)
    {
      cout << "Already empty ";
      return;
    }
    if (tail == tail->next)
    {
      tail = NULL;
    }
    else
    {
      tail->next = tail->next->next;
      tail->next->next->prev = tail;
    }
  }
  void deleteFromEnd()
  {
    if (tail == NULL)
    {
      cout << "Already empty ";
      return;
    }
    if (tail == tail->next)
    {
      tail = NULL;
    }
    else
    {
      tail->prev->next = tail->next;
      tail->next->prev = tail->prev;
      tail = tail->prev;
    }
  }
  void display()
  {
    if (tail == NULL)
    {
      cout << "List is empty ";
    }
    else
    {
      Node<T> *temp = tail->next; // Start from head (tail->next)
      do
      {
        cout << temp->data << " ";
        temp = temp->next;
      } while (temp != tail->next); // Stop when we reach head again
    }
  }
};

int main()
{
  LinkList<int> lt;
  lt.insertAtStart(69);
  lt.insertAtStart(96);
  lt.insertAtStart(84);
  lt.insertAtStart(47);
  lt.deleteFromEnd();
  lt.insertAtEnd(85);
  lt.insertAtEnd(74);
  lt.insertAtEnd(12);
  lt.insertData(3, 56);
  lt.insertData(5, 32);
  lt.insertData(7, 41);
  lt.deleteFromStart();
  lt.display();
}