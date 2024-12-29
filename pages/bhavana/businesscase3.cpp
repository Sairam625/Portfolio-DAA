#include <bits/stdc++.h>
using namespace std;

class SafetyRoute 
{
public:
    int n; 
    vector<int> dist, path, visited;
    int start;  
    vector<vector<int>> graph;

    void input() 
{
        graph.resize(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; i++) graph[i][i] = 0;

        int e;
        cout << "Enter number of roads: ";
        cin >> e;
        cout << "Enter roads (start, end, cost):\n";
        for (int i = 0; i < e; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u][v] = w;
            graph[v][u] = w;
        }
    }

    void init() {
        visited.resize(n, 0);
        dist.resize(n, INT_MAX);
        path.resize(n, -1);

        cout << "Enter starting location: ";
        cin >> start;
        dist[start] = 0;
    }

    // Dijkstra's algorithm to find the safest route
    void dijkstra()
{
        for (int i = 0; i < n - 1; i++) {
            int minDist = INT_MAX, minIdx = -1;
          for (int j = 0; j < n; j++) 
          {
                if (!visited[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    minIdx = j;
                }
            }

            visited[minIdx] = 1;

            // Update distances for neighbors
            for (int j = 0; j < n; j++)
              {
                if (!visited[j] && graph[minIdx][j] != INT_MAX && dist[minIdx] + graph[minIdx][j] < dist[j]) 
                {
                    dist[j] = dist[minIdx] + graph[minIdx][j];
                    path[j] = minIdx;
                }
            }
        }
    }

    //  safest route from the source to each location
    void printRoute(int dest) {
        if (dist[dest] == INT_MAX) {
            cout << "No path to location " << dest << endl;
            return;
        }

        vector<int> route;
        int curr = dest;

        // Reconstruct the path
        while (curr != -1) {
            route.push_back(curr);
            curr = path[curr];
        }

        // Print the path in reverse order
        cout << "Safe route from " << start << " to " << dest << ": ";
        for (int i = route.size() - 1; i >= 0; i--) {
            cout << route[i];
            if (i != 0) cout << " -> ";
        }
        cout << "\tTotal safety score: " << dist[dest] << endl;
    }
};

int main() {
    SafetyRoute sr;
    cout << "Enter number of locations: ";
    cin >> sr.n;

    sr.input();  
    sr.init();  

    sr.dijkstra();  

    // Safest path for each location
    for (int i = 0; i < sr.n; i++) {
        sr.printRoute(i);
    }

    return 0;
}
