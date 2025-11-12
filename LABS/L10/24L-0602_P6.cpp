#include <iostream>
using namespace std;

class HeapSort {
private:
    void heapify(int arr[], int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && arr[l] > arr[largest])
            largest = l;

        if (r < n && arr[r] > arr[largest])
            largest = r;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

public:
    void heapSort(int arr[], int n) {
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        for (int i = n - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
};

int main() {
    int arr[] = { 10, 3, 5, 1, 4, 2 };
    int n = sizeof(arr) / sizeof(arr[0]);

    HeapSort hs;
    hs.heapSort(arr, n);

    cout << "Sorted Array : ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << (i < n - 1 ? ", " : "\n");
    return 0;
}
