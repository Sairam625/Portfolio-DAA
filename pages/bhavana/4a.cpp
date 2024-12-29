#include <bits/stdc++.h> 
using namespace std;

struct E { int u, v, w; };    // Edge structure where u: source, v: destination, w: weight

int find(int p[], int x) { 
    if (p[x] != x) p[x] = find(p, p[x]); 
    return p[x]; 
}

void unite(int p[], int r[], int x, int y) { 
    int rx = find(p, x), ry = find(p, y);
    if (rx != ry) {
        if (r[rx] > r[ry]) p[ry] = rx; 
        else if (r[rx] < r[ry]) p[rx] = ry; 
        else { p[ry] = rx; r[rx]++; }
    }
}

void kruskal(int V, int E, vector<E>& edges) { 
    sort(edges.begin(), edges.end(), [](E a, E b) { return a.w < b.w; });

    int p[V], r[V]; 
    for (int i = 0; i < V; i++) p[i] = i, r[i] = 0;

    vector<E> mst; 
    int cost = 0;

    for (int i = 0; i < E; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (find(p, u) != find(p, v)) {
            mst.push_back(edges[i]); cost += edges[i].w;
            unite(p, r, u, v);
        }
    }

    cout << "MST Edges: \n";
    for (auto& e : mst) cout << e.u << " - " << e.v << " : " << e.w << endl;
    cout << "Total cost: " << cost << endl;
}

int main() {
    int V, E; 
    cout << "Enter V and E: "; 
    cin >> V >> E;

    vector<E> edges(E);
    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; i++) cin >> edges[i].u >> edges[i].v >> edges[i].w;

    kruskal(V, E, edges);
    return 0;
}
