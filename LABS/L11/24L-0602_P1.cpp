#include <iostream>
using namespace std;

template <typename T>
class MaxHeap {
private:
    T* heap;
    int size;
    int capacity;

    void heapifyUp(int index) {
        while (index > 0 && heap[(index - 1) / 2] < heap[index]) {
            swap(heap[(index - 1) / 2], heap[index]);
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap(int cap) {
        capacity = cap;
        heap = new T[capacity];
        size = 0;
    }

    MaxHeap(T arr[], int n) {
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
        cout << "Max Heap Array: [";
        for (int i = 0; i < size; i++) {
            cout << heap[i];
            if (i != size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    ~MaxHeap() {
        delete[] heap;
    }
};

int main() {
    int arr[] = { 30, 20, 40, 10, 50, 60 };
    int n = sizeof(arr) / sizeof(arr[0]);
    MaxHeap<int> maxHeap(arr, n);
    cout << "Heap built from array:" << endl;
    maxHeap.display();

    maxHeap.insert(35);
    cout << "After inserting 35:" << endl;
    maxHeap.display();

    int maxVal = maxHeap.deleteRoot();
    cout << "Extracted root (max): " << maxVal << endl;
    cout << "Heap after deleting root:" << endl;
    maxHeap.display();

    return 0;
}
