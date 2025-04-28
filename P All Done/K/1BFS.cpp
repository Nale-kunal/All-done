#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

void parallelBFS(vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);
    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";
        #pragma omp parallel for
        for (int i = 0; i < graph[current].size(); i++) {
            int neighbor = graph[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                #pragma omp critical
                {
                    q.push(neighbor);
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> graph = {{1, 2}, {0, 3, 4}, {0, 5}, {1}, {1, 5}, {2, 4}};
    int startNode = 0;
    parallelBFS(graph, startNode);
    return 0;
}
