#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adj;  // Adjacency list

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);  // Because undirected graph
    }

    // Parallel DFS starting from startVertex
    void parallelDFS(int startVertex) {
        vector<bool> visited(V, false);

        #pragma omp parallel
        {
            #pragma omp single
            {
                dfsUtil(startVertex, visited);
            }
        }
        cout << endl;
    }

private:
    void dfsUtil(int v, vector<bool>& visited) {
        bool alreadyVisited = false;

        // Critical section to safely check and update visited[v]
        #pragma omp critical
        {
            if (visited[v]) {
                alreadyVisited = true;  // Node already visited
            } else {
                visited[v] = true;      // Mark as visited
                cout << v << " ";       // Print node
            }
        }

        if (alreadyVisited) return;    // If visited, exit immediately

        // Spawn tasks for all neighbors
        for (int neighbor : adj[v]) {
            #pragma omp task
            dfsUtil(neighbor, visited);
        }
    }

public:
    // Parallel BFS starting from startVertex using frontier method
    void parallelBFS(int startVertex) {
        vector<bool> visited(V, false);

        vector<int> currentLevel;
        vector<int> nextLevel;

        visited[startVertex] = true;
        currentLevel.push_back(startVertex);

        while (!currentLevel.empty()) {
            nextLevel.clear();

            #pragma omp parallel
            {
                // Thread-local storage for neighbors in next level
                vector<int> localNext;

                // Parallel for loop over current level nodes
                #pragma omp for nowait
                for (int i = 0; i < (int)currentLevel.size(); i++) {
                    int v = currentLevel[i];

                    // Print current node (critical to avoid jumbled output)
                    #pragma omp critical
                    cout << v << " ";

                    // Explore neighbors
                    for (int neighbor : adj[v]) {
                        bool notVisited = false;

                        // Check and mark neighbor visited atomically
                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                visited[neighbor] = true;
                                notVisited = true;
                            }
                        }

                        // Add to thread-local next level if not visited before
                        if (notVisited) {
                            localNext.push_back(neighbor);
                        }
                    }
                }

                // Merge thread-local next level into global nextLevel safely
                #pragma omp critical
                nextLevel.insert(nextLevel.end(), localNext.begin(), localNext.end());
            }

            // Move to next BFS level
            currentLevel = nextLevel;
        }
        cout << endl;
    }
};

int main() {
    Graph g(7);

    // Build graph edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    cout << "Parallel DFS starting from node 0:" << endl;
    g.parallelDFS(0);
    cout << endl;

    cout << "Parallel BFS starting from node 0:" << endl;
    g.parallelBFS(0);

    return 0;
}
