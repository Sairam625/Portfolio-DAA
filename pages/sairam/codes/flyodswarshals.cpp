#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;
void floydWarshallFlood(vector<vector<int>> &graph) {
    int n = graph.size();
    vector<vector<int>> dist = graph;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    cout << "Floyd-Warshall Flood Prediction Distances:\n";
    for (auto &row : dist) {
        for (int d : row) {
            if (d == INT_MAX) cout << "INF ";
            else cout << d << " ";
        }
        cout << endl;
    }
}