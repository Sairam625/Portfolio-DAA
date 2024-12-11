// Online C++ compiler to run C++ program online//
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adjMatrix;

    Graph(int V) {
        this->V = V;
        adjMatrix = {
            {0, 20, 30, 50, INT_MAX},
            {20, 0, 25, INT_MAX, 15},
            {30, 25, 0, 15, 10},
            {50, INT_MAX, 15, 0, 40},
            {INT_MAX, 15, 10, 40, 0}
        };
    }

    void dijkstra(int start, vector<int>& dist, vector<int>& parent) {
        dist.assign(V, INT_MAX);
        parent.assign(V, -1);
        dist[start] = 0;

        vector<bool> visited(V, false);

        for (int count = 0; count < V - 1; ++count) {
            int u = -1;

            // Find the vertex with the smallest distance value
            for (int i = 0; i < V; ++i) {
                if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                    u = i;
                }
            }

            // Mark the selected vertex as visited
            visited[u] = true;

            // Update distance values of adjacent vertices
            for (int v = 0; v < V; ++v) {
                if (adjMatrix[u][v] != INT_MAX && !visited[v] && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    void getShortestPath(int start, int end, const vector<int>& parent) {
        vector<int> path;
        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }

        cout << "Shortest path from location " << start << " to " << end << ": ";
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Graph g(5);

    // Task Assignment Example: Truck at DC -> Task to load at W1
    vector<int> dist(5);
    vector<int> parent(5);
    g.dijkstra(0, dist, parent);
    g.getShortestPath(0, 3, parent); // Shortest path from DC to W1

    return 0;
}
