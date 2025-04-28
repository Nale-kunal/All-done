#include <iostream>
#include <omp.h>
using namespace std;

// Sequential Bubble Sort
void bubbleSequential(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// Parallel Bubble Sort (Odd-Even Transposition)
void bubbleParallel(int arr[], int n) {
    #pragma omp parallel
    {
        for (int i = 0; i < n; i++) {
            #pragma omp for
            for (int j = 1; j < n - 1; j += 2) {
                if (arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
            }
            #pragma omp barrier

            #pragma omp for
            for (int j = 0; j < n - 1; j += 2) {
                if (arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
            }
            #pragma omp barrier
        }
    }
}

int main() {
    int n = 10000; // Use a large enough dataset to see speedup
    int *arr = new int[n];
    int *brr = new int[n];

    // Initialize arrays with same random data
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
        brr[i] = arr[i];
    }

    double start, end;

    start = omp_get_wtime();
    bubbleSequential(arr, n);
    end = omp_get_wtime();
    cout << "Sequential Bubble Sort took: " << (end - start) << " seconds\n";

    start = omp_get_wtime();
    bubbleParallel(brr, n);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort took: " << (end - start) << " seconds\n";

    delete[] arr;
    delete[] brr;

    return 0;
}
