#include <iostream>
using namespace std;

class MinHeap {
private:
    int* heap;
    int size;
    int capacity;

    void heapifyUp(int index) {
        while (index > 0 && heap[(index - 1) / 2] > heap[index]) {
            swap(heap[(index - 1) / 2], heap[index]);
            index = (index - 1) / 2;
        }
    }

public:
    MinHeap(int cap) {
        capacity = cap;
        heap = new int[capacity];
        size = 0;
    }

    void insert(int val) {
        if (size == capacity) {
            cout << "Heap is full!" << endl;
            return;
        }
        heap[size] = val;
        heapifyUp(size);
        size++;
    }

    void display() {
        cout << "Min Heap Array: [";
        for (int i = 0; i < size; i++) {
            cout << heap[i];
            if (i != size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    ~MinHeap() {
        delete[] heap;
    }
};

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    MinHeap minHeap(n);
    cout << "Enter elements:" << endl;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        minHeap.insert(val);
    }
    minHeap.display();
    return 0;
}
