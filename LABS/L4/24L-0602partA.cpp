#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <set>
using namespace std;
int main() {
    cout << "1. Iterator Basics:\n";
    vector<int> v{1, 2, 3, 4, 5};
    cout << "Using iterator to print elements: ";
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\nUsing reverse iterator to print elements: ";
    for (vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl << endl;
    // 2. Iterator with STL list<string>:
    cout << "2. Iterator with STL Containers:\n";
    list<string> students {"AhmWendie", "YoRu", "Nigga", "Tard"};
    cout << "a) Print all names: ";
    for (list<string>::iterator it = students.begin(); it != students.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    // b) Erase a name using an iterator (erase "Nigga")
    for (list<string>::iterator it = students.begin(); it != students.end(); ++it) {
        if (*it == "Nigga") {
            students.erase(it);
            break;
        }
    }
    cout << "b) After erasing 'Nigga': ";
    for (list<string>::iterator it = students.begin(); it != students.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    // c) Insert a new name at a specific position (insert "katyusha" at position 2)
    int insertPos = 2;
    list<string>::iterator it = students.begin();
    int idx = 0;
    while (it != students.end() && idx < insertPos) {
        ++it;
        ++idx;
    }
    students.insert(it, "katyusha");
    cout << "c) After inserting 'katyusha' at position 2: ";
    for (list<string>::iterator it2 = students.begin(); it2 != students.end(); ++it2) {
        cout << *it2 << " ";
    }
    cout << endl << endl;

    // 3. Set Iterator:
    cout << "3. Set Iterator:\n";
    set<int> uniqueNumbers {30, 10, 20, 40, 20, 10, 50};
    cout << "Using iterator to print sorted unique elements: ";
    for (set<int>::iterator it = uniqueNumbers.begin(); it != uniqueNumbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    // Compare iteration vs indexing in vector (since set does not support indexing)
    vector<int> vecFromSet(uniqueNumbers.begin(), uniqueNumbers.end());
    cout << "Comparing iteration vs indexing on vector converted from set:\n";
    cout << "Iteration: ";
    for (vector<int>::iterator it = vecFromSet.begin(); it != vecFromSet.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\nIndexing: ";
    for (size_t i = 0; i < vecFromSet.size(); ++i) {
        cout << vecFromSet[i] << " ";
    }
    cout << endl;

    return 0;
}
