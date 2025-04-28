#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
using namespace std;

void parallelDFS(vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(start);
    visited[start] = true;
    cout << "DFS Traversal: ";
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        cout << current << " ";
        #pragma omp parallel for
        for (int i = 0; i < graph[current].size(); i++) {
            int neighbor = graph[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                #pragma omp critical
                {
                    s.push(neighbor);
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> graph = {{1, 2}, {0, 3, 4}, {0, 5}, {1}, {1, 5}, {2, 4}};
    int startNode = 0;
    parallelDFS(graph, startNode);
    return 0;
}
