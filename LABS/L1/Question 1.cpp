#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class List
{
public:
	virtual void insert(T element) = 0;		// Add element
	virtual void remove(int index) = 0;		// Remove element at index
	virtual T get(int index) = 0;					// Get element at index
	virtual int g_size() = 0;							// Get current size
	virtual void display() = 0;						// Display all elements
	virtual bool isEmpty() = 0;						// Check if empty
	virtual bool contains(T element) = 0; // Check if element exists
	virtual void clear() = 0;							// Clear list
	virtual ~List() {}
};

class Person
{
public:
	string name;
	string gender;
	int age;
	Person(string n = "", string g = "", int a = 0)
	{ // Constructor
		name = n;
		gender = g;
		age = a;
	}
	friend ostream &operator<<(ostream &os, const Person &p)
	{ // Output formatting
		os << "Name: " << p.name << ", Gender: " << p.gender << ", Age: " << p.age;
		return os;
	}
	bool operator==(const Person &other) const
	{ // Equality check for contains function
		return name == other.name && gender == other.gender && age == other.age;
	}
};

template <typename T> // The template is used when the specific data type is not defined
class ArrayList : public List<T>
{
private:
	T *arr;
	int capacity;
	int size;
	void regrow() // Double capacity and copy elements
	{
		capacity = capacity * 2;
		T *temp = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
	}

public:
	ArrayList(int capacity = 5, int size = 0) // Constructor initializes array
	{
		this->capacity = capacity;
		this->size = size;
		arr = new T[capacity];
	}
	T get(int index) override // Return element at index or throw error
	{
		if (index >= 0 && index < size)
		{
			return arr[index];
		}
		else
		{
			throw invalid_argument("Error occurred");
		}
	}
	void insert(T element) override // Insert element, resize if needed
	{
		if (size >= capacity)
		{
			regrow();
		}
		arr[size++] = element;
	}
	void display() override // Print all elements
	{
		for (int i = 0; i < size; i++)
		{
			cout << arr[i] << endl;
		}
	}
	void remove(int index) override // Remove element by shifting left
	{
		if (index >= size || index < 0)
		{
			throw invalid_argument("Index out of bound");
		}
		for (int i = index; i < size - 1; i++)
		{
			arr[i] = arr[i + 1];
		}
		size--;
	}
	int g_size() override // Getter for size
	{
		return size;
	}
	bool isEmpty() override // Check if list is empty
	{
		if (size == 0)
		{
			return true;
		}
		return false;
	}
	bool contains(T element) override // Check if element exists
	{
		for (int i = 0; i < size; i++)
		{
			if (arr[i] == element)
			{
				return true;
			}
		}
		return false;
	}
	void clear() override // Clear list by resetting size
	{
		size = 0;
	}
	void inputPerson()
	{ // Input a Person object from user and insert
		string nam, gen;
		int ag;
		cout << "Enter name: ";
		cin >> nam;
		if (nam == "")
		{
			cout << "Invalid Name ";
			return;
		}
		cout << "Enter gender: ";
		cin >> gen;
		cout << "Enter age: ";
		cin >> ag;
		if (ag < 0)
		{
			cout << "Invalid Age ";
			return;
		}
		insert(Person(nam, gen, ag));
	}
	void inputRemove()
	{ // Input index and remove if valid
		int idx;
		cout << "Enter index to remove: ";
		cin >> idx;
		if (idx >= 0 && idx < size)
		{
			remove(idx);
			cout << "Removed element at index " << idx << endl;
		}
		else
		{
			cout << "Invalid index. No element removed." << endl;
		}
	}
	void inputContains()
	{ // Input Person and check if contained
		string nam, gen;
		int ag;
		cout << "Enter name: ";
		cin >> nam;
		if (nam == "")
		{
			cout << "Invalid Name ";
			return;
		}
		cout << "Enter gender: ";
		cin >> gen;
		cout << "Enter age: ";
		cin >> ag;
		if (ag < 0)
		{
			cout << "Invalid Age ";
			return;
		}
		Person p(nam, gen, ag);
		if (contains(p))
		{
			cout << "Person found." << endl;
		}
		else
		{
			cout << "Person not found." << endl;
		}
	}
	~ArrayList()
	{
		delete[] arr; // Free dynamically allocated memory
	}
};

int main()
{
	ArrayList<Person> people;
	int n = 0, per = 0;
	cout << "Enter the number of persons: ";
	cin >> n;
	if (n < 0)
	{
		cout << "Invalid size";
		return 0;
	}
	for (int i = 0; i < n; i++)
	{
		people.inputPerson();
	}
	cout << "All Persons : " << endl;
	people.display();
	people.inputRemove();
	people.display();
	cout << "\nEnter the index to get the person : " << endl;
	cin >> per;
	if (per < 0 || per > people.g_size())
	{
		cout << "Invalid input" << endl;
		return 0;
	}
	cout << "\nAccessing index : " << people.get(per) << endl;
	cout << "\nTotal current size is: " << people.g_size() << endl;
	if (people.isEmpty())
	{
		cout << "List is empty " << endl;
	}
	else
	{
		cout << "List is not empty " << endl;
	}
	people.inputContains();
	people.clear();
	if (people.isEmpty())
	{
		cout << "List is empty " << endl;
	}
	else
	{
		cout << "List is not empty " << endl;
	}
	return 0;
}

// we use templates when a specific data type is not used and we have a flexible amount of data that cant be defined
// by any data type, templates come in handy there. also we use abstract classes for data reusability in this example there
// were not many instances of the use of reusability of code, but with big programs we use it for reusability