#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
struct Edge {
    int u, v, weight;
};

bool compareEdge(const Edge &e1, const Edge &e2) {
    return e1.weight < e2.weight;
}

int findParent(vector<int> &parent, int node) {
    if (parent[node] != node) {
        parent[node] = findParent(parent, parent[node]);
    }
    return parent[node];
}

void unionSet(vector<int> &parent, vector<int> &rank, int u, int v) {
    int rootU = findParent(parent, u);
    int rootV = findParent(parent, v);

    if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

void kruskalDamageAssessment(vector<Edge> &edges, int n) {
    sort(edges.begin(), edges.end(), compareEdge);

    vector<int> parent(n);
    vector<int> rank(n, 0);
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    vector<Edge> mst;
    for (const auto &edge : edges) {
        if (findParent(parent, edge.u) != findParent(parent, edge.v)) {
            mst.push_back(edge);
            unionSet(parent, rank, edge.u, edge.v);
        }
    }

    cout << "Kruskal Damage Assessment MST Edges:\n";
    for (const auto &edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }
}

int main() {
    vector<vector<int>> graphBFS = {
        {1, 2},
        {0, 3},
        {0, 3},
        {1, 2}
    };
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}
    };
    kruskalDamageAssessment(edges, 4);

    return 0;
}
