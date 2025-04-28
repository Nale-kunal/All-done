#include <iostream>  // Include for input/output operations
#include <omp.h>     // Include OpenMP library for parallel programming
using namespace std; // Use the standard namespace to avoid typing std::

/* Merge function to merge two sorted halves of the array:
   arr[l..m] and arr[m+1..r] into a sorted sequence */
void merge(int arr[], int l, int m, int r) {
    int i = l;       // Starting index of left subarray
    int j = m + 1;   // Starting index of right subarray
    int k = 0;       // Index for temp array
    int n = r - l + 1;  // Number of elements to merge

    int* temp = new int[n];  // Temporary array to hold merged result

    // Merge the two halves by comparing elements one by one
    while (i <= m && j <= r) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];  // Take from left subarray if smaller
        else
            temp[k++] = arr[j++];  // Else take from right subarray
    }

    // Copy any remaining elements from left subarray (if any)
    while (i <= m) temp[k++] = arr[i++];

    // Copy any remaining elements from right subarray (if any)
    while (j <= r) temp[k++] = arr[j++];

    // Copy the merged elements back into the original array
    for (int i = 0; i < n; i++)
        arr[l + i] = temp[i];

    delete[] temp;  // Free dynamically allocated memory
}

/* Parallel Merge Sort function:
   Recursively splits array and sorts halves in parallel using OpenMP */
void parallelMergeSort(int arr[], int l, int r) {
    if (l < r) {  // Base condition: only proceed if subarray has more than one element
        int m = (l + r) / 2;  // Find midpoint to split array

        #pragma omp parallel sections  // Start parallel sections
        {
            #pragma omp section  // First section sorts left half in parallel
            parallelMergeSort(arr, l, m);

            #pragma omp section  // Second section sorts right half in parallel
            parallelMergeSort(arr, m + 1, r);
        }  // Wait for both sections to finish here

        merge(arr, l, m, r);  // Merge the two sorted halves
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};  // Example array to sort
    int n = sizeof(arr) / sizeof(arr[0]);  // Calculate size of array

    cout << "Original Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";  // Print original array
    cout << endl;

    parallelMergeSort(arr, 0, n - 1);  // Call parallel merge sort on entire array

    cout << "Sorted Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";  // Print sorted array
    cout << endl;

    return 0;  // Exit program successfully
}
