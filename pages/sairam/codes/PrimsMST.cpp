#include <iostream>
#include <vector>
#include <queue>
#include <climits>

void primMST(vector<vector<pair<int, int>>> &graph) {
    int n = graph.size();
    vector<int> key(n, INT_MAX);
    vector<bool> mstSet(n, false);
    vector<int> parent(n, -1);

    key[0] = 0;

    for (int count = 0; count < n - 1; ++count) {
        int u = -1;

        for (int v = 0; v < n; ++v) {
            if (!mstSet[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        mstSet[u] = true;

        for (auto &[v, weight] : graph[u]) {
            if (!mstSet[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    cout << "Minimum Spanning Tree Edges:\n";
    for (int i = 1; i < n; ++i) {
        cout << parent[i] << " - " << i << endl;
    }
}
