#include <iostream>
#include <string>
using namespace std;

struct Task {
    string name;
    int priority;
};

class PriorityQueue {
private:
    Task* heap;
    int capacity;
    int size;
    bool isMaxHeap;

    int parent(int i) {
        return (i - 1) / 2;
    }
    int leftChild(int i) {
        return 2 * i + 1;
    }
    int rightChild(int i) {
        return 2 * i + 2;
    }

    void heapifyDown(int i) {
        int extreme = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (isMaxHeap) {
            if (left < size && heap[left].priority > heap[extreme].priority)
                extreme = left;
            if (right < size && heap[right].priority > heap[extreme].priority)
                extreme = right;
        }
        else {
            if (left < size && heap[left].priority < heap[extreme].priority)
                extreme = left;
            if (right < size && heap[right].priority < heap[extreme].priority)
                extreme = right;
        }

        if (extreme != i) {
            swap(heap[i], heap[extreme]);
            heapifyDown(extreme);
        }
    }

    void heapifyUp(int i) {
        while (i != 0) {
            int p = parent(i);
            if ((isMaxHeap && heap[i].priority > heap[p].priority) ||
                (!isMaxHeap && heap[i].priority < heap[p].priority)) {
                swap(heap[i], heap[p]);
                i = p;
            }
            else {
                break;
            }
        }
    }

public:
    PriorityQueue(int cap, bool maxHeap = true) {
        capacity = cap;
        size = 0; 
        isMaxHeap = maxHeap;
        heap = new Task[capacity];
    }

    ~PriorityQueue() {
        delete[] heap;
    }

    void insert(const string& name, int priority) {
        if (size == capacity) {
            cout << "Priority queue full!" << endl;
            return;
        }
        heap[size].name = name;
        heap[size].priority = priority;
        heapifyUp(size);
        size++;
    }

    Task extractTop() {
        if (size == 0) {
            cout << "Priority queue empty!" << endl;
            return Task{ "", -1 };
        }
        Task topTask = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return topTask;
    }

    bool empty() {
        return size == 0;
    }

    void buildHeap(Task arr[], int n) {
        if (n > capacity) {
            cout << "Array size exceeds queue capacity!" << endl;
            return;
        }
        size = n;
        for (int i = 0; i < n; i++) {
            heap[i] = arr[i];
        }
        for (int i = (size / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    // Display current queue array (unsorted but heap property maintained)
    void displayHeap() {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << "(" << heap[i].name << ", " << heap[i].priority << ")";
            if (i != size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

int main() {
    Task tasks[] = { {"task1", 3}, {"task2", 5}, {"task3", 1}, {"task4", 4}, {"task5", 2} };
    int n = sizeof(tasks) / sizeof(tasks[0]);

    // Min heap simulation
    PriorityQueue minPQ(n, false); // false = min heap
    minPQ.buildHeap(tasks, n);
    cout << "Min Heap after buildHeap:" << endl;
    minPQ.displayHeap();
    cout << "Extracting tasks by ascending priority from Min Heap:" << endl;
    while (!minPQ.empty()) {
        Task t = minPQ.extractTop();
        cout << "(" << t.name << ", " << t.priority << ")" << endl;
    }
    cout << endl;

    // Max heap simulation
    PriorityQueue maxPQ(n, true); // true = max heap
    maxPQ.buildHeap(tasks, n);
    cout << "Max Heap after buildHeap:" << endl;
    maxPQ.displayHeap();
    cout << "Extracting tasks by descending priority from Max Heap:" << endl;
    while (!maxPQ.empty()) {
        Task t = maxPQ.extractTop();
        cout << "(" << t.name << ", " << t.priority << ")" << endl;
    }

    return 0;
}
