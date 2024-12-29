#include <bits/stdc++.h>
using namespace std;

// BFS to find shortest path from source
void bfs(int graph[10][10], int n, int src) {
    vector<int> dist(n, INT_MAX);  
    queue<int> q;
    
    dist[src] = 0;
    q.push(src);
    
    while (!q.empty()) {
        int spot = q.front();
        q.pop();
        
        for (int i = 0; i < n; i++) {
            if (graph[spot][i] != 0 && dist[i] == INT_MAX) {
                dist[i] = dist[spot] + 1;  // Update distance
                q.push(i);
            }
        }
    }

    cout << "BFS distances from spot " << src << ": ";
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX) {
            cout << "INF ";
        } else {
            cout << dist[i] << " ";
        }
    }
    cout << endl;
}

// Floyd-Warshall to find shortest paths between all spots
void floydWarshall(int graph[10][10], int n) 
{
    int dist[10][10];
 // Initialize distance matrix from graph
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 0 && i != j) {
                dist[i][j] = INT_MAX;  // No path exists
            }
            else {
                dist[i][j] = graph[i][j];  // Direct path exists
            }
        }
    }

    // Update shortest paths using intermediate spots
    for (int k = 0; k < n; k++) 
    {
        for (int i = 0; i < n; i++) 
    {
            for (int j = 0; j < n; j++) 
            {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) 
                {
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];  // Shortest path found here
                    }
                }
            }
        }
    }

   
    cout << "Shortest paths between all places: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of gathering places: ";
    cin >> n;

  int graph[10][10];
    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
            if (graph[i][j] == 0 && i != j) // No path
            {
                graph[i][j] = INT_MAX;  
            }
        }
    }


    int src;
    cout << "Enter source gathering spot for BFS: ";
    cin >> src;
    bfs(graph, n, src);

    floydWarshall(graph, n);

    return 0;
}
