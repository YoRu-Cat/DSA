#include <iostream>
using namespace std;

// Node class for linked list
template <typename T>
class Node
{
public:
  T data;
  Node<T> *next;
  Node(T data = T())
  {
    next = NULL;
    this->data = data;
  }
};

// Abstract List interface
template <typename T>
class List
{
public:
  virtual void insertAtEnd(T element) = 0;
  virtual void insertAtStart(T element) = 0;
  virtual void insertAtPosition(int posi, T data) = 0;
  virtual int search(T element) = 0;
  virtual void deleteData(T element) = 0;
  virtual void deleteFromBeginning() = 0;
  virtual void deleteFromEnd() = 0;
  virtual void reverse() = 0;
  virtual void display() = 0;
  virtual ~List() {}
};

// Singly linked list implementation
template <typename T>
class LinkList : public List<T>
{
private:
  Node<T> *head;
  Node<T> *tail;

public:
  LinkList()
  {
    tail = head = NULL;
  }

  void insertAtEnd(T data) override
  {
    Node<T> *n = new Node<T>(data);
    if (head == NULL)
    {
      head = n;
      tail = n;
    }
    else
    {
      tail->next = n;
      tail = n;
    }
  }

  void insertAtStart(T data) override
  {
    Node<T> *n = new Node<T>(data);
    if (head == NULL)
    {
      head = n;
      tail = n;
    }
    else
    {
      n->next = head;
      head = n;
    }
  }

  int search(T data) override
  {
    Node<T> *temp = head;
    int i = 0;
    while (temp != NULL)
    {
      if (temp->data == data)
      {
        return i;
      }
      i++;
      temp = temp->next;
    }
    return -1;
  }

  void insertAtPosition(int posi, T data) override
  {
    if (posi < 0)
    {
      cout << "Invalid position\n";
      return;
    }
    if (posi == 0)
    {
      insertAtStart(data);
      return;
    }
    Node<T> *temp = head;
    for (int i = 1; i < posi && temp != NULL; i++)
    {
      temp = temp->next;
    }
    if (temp == NULL)
    {
      cout << "Position out of bounds\n";
      return;
    }
    Node<T> *n = new Node<T>(data);
    n->next = temp->next;
    temp->next = n;
    if (temp == tail)
    {
      tail = n;
    }
  }

  void deleteFromBeginning() override
  {
    if (head == NULL)
    {
      cout << "List is empty\n";
      return;
    }
    Node<T> *temp = head;
    head = head->next;
    if (head == NULL)
    {
      tail = NULL;
    }
    delete temp;
  }

  void deleteFromEnd() override
  {
    if (head == NULL)
    {
      cout << "List is empty\n";
      return;
    }
    if (head == tail)
    {
      delete head;
      head = tail = NULL;
      return;
    }
    Node<T> *temp = head;
    while (temp->next != tail)
    {
      temp = temp->next;
    }
    delete tail;
    tail = temp;
    tail->next = NULL;
  }

  void deleteData(T data) override
  {
    if (head == NULL)
    {
      cout << "List is empty\n";
      return;
    }
    if (head->data == data && head == tail)
    {
      delete head;
      head = tail = NULL;
      return;
    }
    if (head->data == data)
    {
      Node<T> *temp = head;
      head = head->next;
      delete temp;
      return;
    }
    Node<T> *temp = head->next;
    Node<T> *prev = head;
    while (temp != NULL)
    {
      if (temp->data == data)
      {
        prev->next = temp->next;
        if (temp == tail)
        {
          tail = prev;
        }
        delete temp;
        return;
      }
      prev = temp;
      temp = temp->next;
    }
    cout << "Element not found\n";
  }

  void reverse() override
  {
    if (head == NULL || head->next == NULL)
    {
      cout << "List is empty\n";
      return;
    }
    Node<T> *prev = NULL;
    Node<T> *temp = head;
    Node<T> *next = NULL;
    tail = head;
    while (temp != NULL)
    {
      next = temp->next;
      temp->next = prev;
      prev = temp;
      temp = next;
    }
    head = prev;
  }

  void display() override
  {
    if (head == NULL)
    {
      cout << "List is empty";
    }
    else
    {
      Node<T> *temp = head;
      while (temp != NULL)
      {
        cout << temp->data << " ";
        temp = temp->next;
      }
    }
    cout << endl;
  }

  bool isEmpty() const
  {
    return head == NULL;
  }

  // Get data at a specific position (index)
  bool getAt(int index, T &data) const
  {
    Node<T> *temp = head;
    int i = 0;
    while (temp != NULL && i < index)
    {
      temp = temp->next;
      i++;
    }
    if (temp == NULL)
      return false;
    data = temp->data;
    return true;
  }

  // Search with custom condition predicate
  template <typename P>
  int searchIf(P pred) const
  {
    Node<T> *temp = head;
    int i = 0;
    while (temp != NULL)
    {
      if (pred(temp->data))
        return i;
      temp = temp->next;
      i++;
    }
    return -1;
  }
};

// Represents a polynomial term (coefficient * x^exponent)
class Term
{
public:
  int coeffi;
  int expone;

  Term(int coef = 0, int exp = 0)
  {
    coeffi = coef;
    expone = exp;
  }

  bool operator==(const Term &other) const
  {
    return coeffi == other.coeffi && expone == other.expone;
  }
};

// Output operator for displaying terms in algebraic form
ostream &operator<<(ostream &out, const Term &t)
{
  if (t.coeffi == 0)
    return out;
  if (t.expone == 0)
  {
    out << t.coeffi;
    return out;
  }
  if (t.coeffi == 1)
  {
    if (t.expone == 1)
      out << "x";
    else
      out << "x^" << t.expone;
    return out;
  }
  if (t.coeffi == -1)
  {
    if (t.expone == 1)
      out << "-x";
    else
      out << "-x^" << t.expone;
    return out;
  }
  out << t.coeffi;
  if (t.expone == 1)
    out << "x";
  else
    out << "x^" << t.expone;
  return out;
}

// Polynomial class using LinkList of Terms
class Polynomial
{
private:
  LinkList<Term> terms;

public:
  // Create polynomial by input from user
  void createPolynomial()
  {
    int n;
    cout << "Enter number of terms: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
      int c, e;
      cout << "Enter coeffi for term " << (i + 1) << ": ";
      cin >> c;
      cout << "Enter expone for term " << (i + 1) << ": ";
      cin >> e;
      insertTermInOrder(Term(c, e));
    }
  }

  // Insert term in descending order by exponent, combine like terms
  void insertTermInOrder(const Term &t)
  {
    if (t.coeffi == 0)
    {
      return;
    }

    int pos = -1;
    Term currTerm;
    int i = 0;
    while (terms.getAt(i, currTerm))
    {
      if (currTerm.expone == t.expone)
      {
        pos = i;
        break;
      }
      i++;
    }
    if (pos != -1)
    {
      Term existingTerm;
      terms.getAt(pos, existingTerm);
      int newCoef = existingTerm.coeffi + t.coeffi;
      terms.deleteData(existingTerm);
      if (newCoef != 0)
        insertTermInOrder(Term(newCoef, t.expone));
      return;
    }

    if (terms.isEmpty())
    {
      terms.insertAtEnd(t);
      return;
    }
    int i2 = 0;
    Term currTerm2;
    while (terms.getAt(i2, currTerm2))
    {
      if (currTerm2.expone < t.expone)
        break;
      i2++;
    }
    terms.insertAtPosition(i2, t);
  }

  // Display polynomial in readable form
  void displayPolynomial() const
  {
    if (terms.isEmpty())
    {
      cout << "0\n";
      return;
    }
    bool first = true;
    int i = 0;
    Term t;
    while (terms.getAt(i, t))
    {
      if (t.coeffi == 0)
      {
        i++;
        continue;
      }
      if (!first && t.coeffi > 0)
        cout << "+";
      cout << t;
      first = false;
      i++;
    }
    cout << endl;
  }

  // Add two polynomials and return the result
  static Polynomial add(const Polynomial &p1, const Polynomial &p2)
  {
    Polynomial result;
    int i = 0;
    Term t;
    while (p1.terms.getAt(i, t))
    {
      result.insertTermInOrder(t);
      i++;
    }
    i = 0;
    while (p2.terms.getAt(i, t))
    {
      result.insertTermInOrder(t);
      i++;
    }
    return result;
  }
};

int main()
{
  // Linked list test
  LinkList<int> list;
  list.insertAtEnd(10);
  list.insertAtStart(5);
  list.insertAtPosition(1, 7);
  cout << "List after insertions: ";
  list.display();
  cout << "Element 7 found at index: " << list.search(7) << endl;
  list.deleteData(7);
  cout << "List after deleting 7: ";
  list.display();
  list.reverse();
  cout << "Reversed list: ";
  list.display();

  // Polynomial test
  Polynomial p1, p2, sum;
  cout << "Create first polynomial:\n";
  p1.createPolynomial();
  cout << "First polynomial: ";
  p1.displayPolynomial();

  cout << "Create second polynomial:\n";
  p2.createPolynomial();
  cout << "Second polynomial: ";
  p2.displayPolynomial();

  sum = Polynomial::add(p1, p2);
  cout << "Sum of polynomials: ";
  sum.displayPolynomial();

  return 0;
}
