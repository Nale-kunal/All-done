#include <iostream>
#include <omp.h>  // Include OpenMP for parallel programming
using namespace std;

// Parallel Bubble Sort
void parallelBubbleSort(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        
        // Parallelize odd and even indexed comparisons
        #pragma omp parallel for shared(arr, swapped)
        for (int j = 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }

        #pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }

        if (!swapped) break;  // Exit early if no swaps occurred
    }
}

// Merge Sort
void merge(int arr[], int l, int m, int r) {
    int i = l, j = m + 1, k = 0;
    int* temp = new int[r - l + 1];
    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (int i = 0; i < k; i++) arr[l + i] = temp[i];
    delete[] temp;
}

// Parallel Merge Sort
void parallelMergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, l, m);

            #pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

// Print Array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr1[] = {12, 11, 13, 5, 6, 7};  // Original array
    int n = sizeof(arr1) / sizeof(arr1[0]);

    // Sorting with Parallel Bubble Sort
    int bubbleSortArr[] = {12, 11, 13, 5, 6, 7};
    parallelBubbleSort(bubbleSortArr, n);

    // Sorting with Parallel Merge Sort
    int mergeSortArr[] = {12, 11, 13, 5, 6, 7};
    parallelMergeSort(mergeSortArr, 0, n - 1);

    // Print Sorted Arrays
    cout << "Bubble Sort Result: ";
    printArray(bubbleSortArr, n);

    cout << "Merge Sort Result: ";
    printArray(mergeSortArr, n);

    return 0;
}
