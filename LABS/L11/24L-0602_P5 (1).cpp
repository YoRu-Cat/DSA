#include <iostream>
using namespace std;

class Heap {
private:
    int* heap;
    int size;
    int capacity;

    void heapify(int i, bool isMaxHeap) {
        int extreme = i; // largest for MaxHeap, smallest for MinHeap
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
            heapify(extreme, isMaxHeap);
        }
    }

public:
    Heap(int arr[], int n) {
        capacity = n;
        size = n;
        heap = new int[capacity];
        for (int i = 0; i < n; i++)
            heap[i] = arr[i];
    }

    void buildHeap(bool isMaxHeap) {
        for (int i = (size / 2) - 1; i >= 0; i--) {
            heapify(i, isMaxHeap);
        }
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
    int arrMax[] = { 40, 10, 30, 5, 60, 15 };
    int nMax = sizeof(arrMax) / sizeof(arrMax[0]);
    Heap maxHeap(arrMax, nMax);
    maxHeap.buildHeap(true);
    cout << "Max Heap built using heapify: ";
    maxHeap.display();

    int arrMin[] = { 10, 2, 15, 20, 5, 1 };
    int nMin = sizeof(arrMin) / sizeof(arrMin[0]);
    Heap minHeap(arrMin, nMin);
    minHeap.buildHeap(false);
    cout << "Min Heap built using heapify: ";
    minHeap.display();

    return 0;
}
