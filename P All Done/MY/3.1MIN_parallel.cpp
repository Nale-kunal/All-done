#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>  // For min, max functions

using namespace std;

// Function to find minimum value using parallel reduction
void minReduction(const vector<int>& data) {
    if (data.empty()) {                  // Check if vector is empty
        cout << "Empty data\n";
        return;
    }
    int minVal = data[0];                // Initialize minVal with first element

    // Parallel for loop with min reduction on minVal
    #pragma omp parallel for reduction(min:minVal)
    for (int i = 0; i < (int)data.size(); i++) {
        minVal = min(minVal, data[i]);  // Update minVal with smaller value
    }

    cout << "Minimum Value: " << minVal << endl;
}

// Function to find maximum value using parallel reduction
void maxReduction(const vector<int>& data) {
    if (data.empty()) {
        cout << "Empty data\n";
        return;
    }
    int maxVal = data[0];                // Initialize maxVal with first element

    // Parallel for loop with max reduction on maxVal
    #pragma omp parallel for reduction(max:maxVal)
    for (int i = 0; i < (int)data.size(); i++) {
        maxVal = max(maxVal, data[i]);  // Update maxVal with larger value
    }

    cout << "Maximum Value: " << maxVal << endl;
}

// Function to calculate sum of elements using parallel reduction
void sumReduction(const vector<int>& data) {
    int sum = 0;                        // Initialize sum to zero

    // Parallel for loop with sum reduction on sum variable
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < (int)data.size(); i++) {
        sum += data[i];                // Add each element to sum
    }

    cout << "Sum: " << sum << endl;
}

// Function to calculate average using parallel sum reduction
void avgReduction(const vector<int>& data) {
    if (data.empty()) {
        cout << "Empty data\n";
        return;
    }
    int sum = 0;

    // Parallel for loop with sum reduction to calculate total sum
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < (int)data.size(); i++) {
        sum += data[i];
    }

    double avg = (double)sum / data.size();  // Calculate average by dividing sum by number of elements

    cout << "Average: " << avg << endl;
}

int main() {
    // Example vector to test all operations
    vector<int> data = {10, 20, 30, 40, 50};

    // Call functions to demonstrate parallel reductions
    minReduction(data);
    maxReduction(data);
    sumReduction(data);
    avgReduction(data);

    return 0;   // Exit successfully
}
