#include <iostream>
using namespace std;

class Heap {
private:
    int* heap;
    int size;
    int capacity;

    void heapifyDown(int i, bool isMaxHeap) {
        int extreme = i; // index of largest for MaxHeap or smallest for MinHeap
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (isMaxHeap) {
            if (left < size && heap[left] > heap[extreme])
                extreme = left;
            if (right < size && heap[right] > heap[extreme])
                extreme = right;
        }
        else {
            if (left < size && heap[left] < heap[extreme])
                extreme = left;
            if (right < size && heap[right] < heap[extreme])
                extreme = right;
        }

        if (extreme != i) {
            swap(heap[i], heap[extreme]);
            heapifyDown(extreme, isMaxHeap);
        }
    }

public:
    Heap(int cap) {
        capacity = cap;
        heap = new int[capacity];
        size = 0;
    }

    void insert(int val, bool isMaxHeap) {
        if (size == capacity) {
            cout << "Heap is full!" << endl;
            return;
        }
        heap[size] = val;
        int current = size;
        size++;
        while (current > 0) {
            int parent = (current - 1) / 2;
            if (isMaxHeap) {
                if (heap[current] > heap[parent]) {
                    swap(heap[current], heap[parent]);
                    current = parent;
                }
                else {
                    break;
                }
            }
            else {
                if (heap[current] < heap[parent]) {
                    swap(heap[current], heap[parent]);
                    current = parent;
                }
                else {
                    break;
                }
            }
        }
    }

    void deleteRoot(bool isMaxHeap) {
        if (size <= 0) {
            cout << "Heap is empty!" << endl;
            return;
        }
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0, isMaxHeap);
    }

    void display() {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << heap[i];
            if (i != size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    ~Heap() {
        delete[] heap;
    }
};

int main() {
    int elements[] = { 10, 20, 5, 6, 1, 8, 9 };
    int n = sizeof(elements) / sizeof(elements[0]);

    // Max Heap test
    Heap maxHeap(n);
    for (int i = 0; i < n; i++) {
        maxHeap.insert(elements[i], true);
    }
    cout << "Max Heap before deletion: ";
    maxHeap.display();

    maxHeap.deleteRoot(true);
    cout << "Max Heap after deleting root: ";
    maxHeap.display();

    // Min Heap test
    Heap minHeap(n);
    for (int i = 0; i < n; i++) {
        minHeap.insert(elements[i], false);
    }
    cout << "Min Heap before deletion: ";
    minHeap.display();

    minHeap.deleteRoot(false);
    cout << "Min Heap after deleting root: ";
    minHeap.display();

    return 0;
}
