#include <iostream>
using namespace std;

// MaxHeap for ascending order sort
template <typename T>
class MaxHeap {
private:
    T* heap;
    int size;
    int capacity;

    void heapifyDown(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] > heap[largest]) largest = left;
        if (right < size && heap[right] > heap[largest]) largest = right;

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

    void buildHeap() {
        for (int i = (size / 2) - 1; i >= 0; i--)
            heapifyDown(i);
    }

public:
    MaxHeap(T arr[], int n) {
        capacity = n;
        size = n;
        heap = new T[capacity];
        for (int i = 0; i < n; i++)
            heap[i] = arr[i];
        buildHeap();
    }

    void heapSort(T arr[]) {
        int originalSize = size;
        for (int i = size - 1; i >= 0; i--) {
            arr[i] = heap[0];                // largest element to end
            heap[0] = heap[size - 1];       // move last element to root
            size--;
            heapifyDown(0);
        }
        size = originalSize;
    }

    ~MaxHeap() {
        delete[] heap;
    }
};

// MinHeap for descending order sort
template <typename T>
class MinHeap {
private:
    T* heap;
    int size;
    int capacity;

    void heapifyDown(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] < heap[smallest]) smallest = left;
        if (right < size && heap[right] < heap[smallest]) smallest = right;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void buildHeap() {
        for (int i = (size / 2) - 1; i >= 0; i--)
            heapifyDown(i);
    }

public:
    MinHeap(T arr[], int n) {
        capacity = n;
        size = n;
        heap = new T[capacity];
        for (int i = 0; i < n; i++)
            heap[i] = arr[i];
        buildHeap();
    }

    void heapSortDescending(T arr[]) {
        int originalSize = size;
        for (int i = size - 1; i >= 0; i--) {
            arr[i] = heap[0];               // smallest element to end
            heap[0] = heap[size - 1];      // move last element to root
            size--;
            heapifyDown(0);
        }
        size = originalSize;
    }

    ~MinHeap() {
        delete[] heap;
    }
};

int main() {
    int arr1[] = { 19, 3, 15, 7, 8, 23, 74 };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    MaxHeap<int> maxHeap(arr1, n1);
    maxHeap.heapSort(arr1);
    cout << "Sorted array ascending (using MaxHeap): ";
    for (int i = 0; i < n1; i++) cout << arr1[i] << " ";
    cout << "\n";

    int arr2[] = { 10, 23, 5, 76, 8, 42, 11 };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    MinHeap<int> minHeap(arr2, n2);
    minHeap.heapSortDescending(arr2);
    cout << "Sorted array descending (using MinHeap): ";
    for (int i = 0; i < n2; i++) cout << arr2[i] << " ";
    cout << "\n";

    return 0;
}
