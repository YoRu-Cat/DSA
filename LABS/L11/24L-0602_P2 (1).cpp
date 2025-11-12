#include <iostream>
using namespace std;

template <typename T>
class MinHeap {
private:
    T* heap;
    int size;
    int capacity;

    void heapifyUp(int index) {
        while (index > 0 && heap[(index - 1) / 2] > heap[index]) {
            swap(heap[(index - 1) / 2], heap[index]);
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap(int cap) {
        capacity = cap;
        heap = new T[capacity];
        size = 0;
    }

    MinHeap(T arr[], int n) {
        capacity = n;
        heap = new T[capacity];
        size = n;
        for (int i = 0; i < n; i++) {
            heap[i] = arr[i];
        }
        for (int i = (size / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    void insert(T val) {
        if (size == capacity) {
            cout << "Heap is full!" << endl;
            return;
        }
        heap[size] = val;
        heapifyUp(size);
        size++;
    }

    T deleteRoot() {
        if (size == 0) {
            cout << "Heap is empty!" << endl;
            return T();
        }
        T root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return root;
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
    int arr[] = { 9, 5, 4, 1, 7, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    MinHeap<int> minHeap(arr, n);
    cout << "Heap built from array:" << endl;
    minHeap.display();

    minHeap.insert(2);
    cout << "After inserting 2:" << endl;
    minHeap.display();

    int minVal = minHeap.deleteRoot();
    cout << "Extracted root (min): " << minVal << endl;
    cout << "Heap after deleting root:" << endl;
    minHeap.display();

    return 0;
}
