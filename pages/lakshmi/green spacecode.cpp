#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

// Binary Search Tree (BST) for managing green space locations
class BST {
    struct Node {
        int id;
        std::string name;
        Node* left;
        Node* right;
        Node(int id, std::string name) : id(id), name(name), left(nullptr), right(nullptr) {}
    };
    Node* root;

    void insert(Node*& root, int id, std::string name) {
        if (!root) {
            root = new Node(id, name);
        } else if (id < root->id) {
            insert(root->left, id, name);
        } else {
            insert(root->right, id, name);
        }
    }

    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            std::cout << "Green Space ID: " << root->id << ", Name: " << root->name << std::endl;
            inorder(root->right);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(int id, std::string name) {
        insert(root, id, name);
    }

    void display() {
        inorder(root);
    }
};

// Kruskal's Algorithm for minimum spanning tree (MST)
class Kruskal {
    struct Edge {
        int u, v, weight;
        bool operator<(const Edge& e) const {
            return weight < e.weight;
        }
    };

    std::vector<int> parent, rank;
    std::vector<Edge> edges;

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unionSets(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);
        if (root_u != root_v) {
            if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            } else {
                parent[root_u] = root_v;
                if (rank[root_u] == rank[root_v]) rank[root_v]++;
            }
        }
    }

public:
    Kruskal(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    void computeMST() {
        std::sort(edges.begin(), edges.end());
        std::vector<Edge> mst;
        for (const auto& edge : edges) {
            if (find(edge.u) != find(edge.v)) {
                mst.push_back(edge);
                unionSets(edge.u, edge.v);
            }
        }

        std::cout << "Minimum Spanning Tree (MST) for Green Spaces: \n";
        for (const auto& edge : mst) {
            std::cout << "Connect Green Space " << edge.u << " with Green Space " << edge.v << " with weight " << edge.weight << std::endl;
        }
    }
};

// Segment Tree for querying and updating green space area coverage
class SegmentTree {
    std::vector<int> tree, arr;
    int n;

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        int left_query = query(2 * node, start, mid, l, r);
        int right_query = query(2 * node + 1, mid + 1, end, l, r);
        return left_query + right_query;
    }

public:
    SegmentTree(const std::vector<int>& arr) : arr(arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

// Heap for prioritizing green spaces based on usage
class GreenSpaceHeap {
    struct GreenSpace {
        int id;
        int usage;  // Number of visitors
        bool operator<(const GreenSpace& other) const {
            return usage < other.usage;
        }
    };

    std::priority_queue<GreenSpace> pq;

public:
    void addGreenSpace(int id, int usage) {
        pq.push({id, usage});
    }

    void display() {
        std::cout << "Green spaces with the highest usage:\n";
        while (!pq.empty()) {
            GreenSpace gs = pq.top();
            std::cout << "Green Space ID: " << gs.id << ", Usage: " << gs.usage << std::endl;
            pq.pop();
        }
    }
};

int main() {
    // Example of managing green spaces
    BST bst;
    bst.insert(1, "Park A");
    bst.insert(2, "Park B");
    bst.insert(3, "Park C");

    std::cout << "Green Spaces in the City (BST):\n";
    bst.display();

    // Kruskal's Algorithm Example
    Kruskal kruskal(4);  // 4 green spaces
    kruskal.addEdge(0, 1, 5);
    kruskal.addEdge(1, 2, 2);
    kruskal.addEdge(2, 3, 3);
    kruskal.addEdge(0, 2, 6);
    kruskal.computeMST();

    // Segment Tree Example
    std::vector<int> areas = {10, 20, 30, 40, 50};
    SegmentTree st(areas);
    std::cout << "Query for total area in range [1, 3]: " << st.query(1, 3) << std::endl;

    // Green Space Heap Example
    GreenSpaceHeap gsh;
    gsh.addGreenSpace(1, 100);
    gsh.addGreenSpace(2, 200);
    gsh.addGreenSpace(3, 150);
    gsh.display();

    return 0;
}
