#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void minReduction(vector<int>& data) {
    int minVal = data[0];
    #pragma omp parallel for reduction(min:minVal)
    for (int i = 0; i < data.size(); i++) {
        if (data[i] < minVal)
            minVal = data[i];
    }
    cout << "Minimum Value: " << minVal << endl;
}

void maxReduction(vector<int>& data) {
    int maxVal = data[0];
    #pragma omp parallel for reduction(max:maxVal)
    for (int i = 0; i < data.size(); i++) {
        if (data[i] > maxVal)
            maxVal = data[i];
    }
    cout << "Maximum Value: " << maxVal << endl;
}

void sumReduction(vector<int>& data) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < data.size(); i++) {
        sum += data[i];
    }
    cout << "Sum: " << sum << endl;
}

void avgReduction(vector<int>& data) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < data.size(); i++) {
        sum += data[i];
    }
    double avg = (double)sum / data.size();
    cout << "Average: " << avg << endl;
}

int main() {
    vector<int> data = {10, 20, 30, 40, 50};
    minReduction(data);
    maxReduction(data);
    sumReduction(data);
    avgReduction(data);
    return 0;
}
