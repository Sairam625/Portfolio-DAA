#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <map>

using namespace std;

// Vehicle class to represent each vehicle
class Vehicle {
public:
    string registration_number;
    int emission_level;
    
    Vehicle(string reg_num, int emission) : registration_number(reg_num), emission_level(emission) {}
    
    // Comparator for priority queue (Min-Heap)
    bool operator<(const Vehicle& other) const {
        return emission_level > other.emission_level;  // Lower emission levels have higher priority
    }
};

// Priority Queue (Min-Heap) to manage vehicles based on emission levels
class TrafficControl {
private:
    priority_queue<Vehicle> vehicleQueue;
    
public:
    void addVehicle(const Vehicle& vehicle) {
        vehicleQueue.push(vehicle);
    }
    
    void restrictVehicles(int max_emission) {
        while (!vehicleQueue.empty()) {
            Vehicle vehicle = vehicleQueue.top();
            if (vehicle.emission_level > max_emission) {
                cout << "Restricted Vehicle: " << vehicle.registration_number 
                     << ", Emission Level: " << vehicle.emission_level << endl;
                vehicleQueue.pop();
            } else {
                break;
            }
        }
    }
};

// Binary Search Tree (BST) to store vehicles sorted by emission level
class BST {
private:
    struct Node {
        Vehicle vehicle;
        Node* left;
        Node* right;
        
        Node(Vehicle v) : vehicle(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    void insert(Node*& node, const Vehicle& vehicle) {
        if (node == nullptr) {
            node = new Node(vehicle);
        } else if (vehicle.emission_level < node->vehicle.emission_level) {
            insert(node->left, vehicle);
        } else {
            insert(node->right, vehicle);
        }
    }
    
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << "BST Vehicle: " << node->vehicle.registration_number
                 << ", Emission Level: " << node->vehicle.emission_level << endl;
            inorder(node->right);
        }
    }
    
public:
    BST() : root(nullptr) {}
    
    void insert(const Vehicle& vehicle) {
        insert(root, vehicle);
    }
    
    void display() {
        inorder(root);
    }
};

// AVL Tree for maintaining balanced tree of vehicles
class AVLTree {
private:
    struct Node {
        Vehicle vehicle;
        Node* left;
        Node* right;
        int height;
        
        Node(Vehicle v) : vehicle(v), left(nullptr), right(nullptr), height(1) {}
    };
    
    Node* root;
    
    int height(Node* node) {
        return node ? node->height : 0;
    }
    
    int balanceFactor(Node* node) {
        return height(node->left) - height(node->right);
    }
    
    void updateHeight(Node* node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }
    
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    Node* balance(Node* node) {
        if (balanceFactor(node) > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        
        if (balanceFactor(node) < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        
        return node;
    }
    
    Node* insert(Node* node, const Vehicle& vehicle) {
        if (!node) return new Node(vehicle);
        
        if (vehicle.emission_level < node->vehicle.emission_level) {
            node->left = insert(node->left, vehicle);
        } else {
            node->right = insert(node->right, vehicle);
        }
        
        updateHeight(node);
        return balance(node);
    }
    
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << "AVL Tree Vehicle: " << node->vehicle.registration_number
                 << ", Emission Level: " << node->vehicle.emission_level << endl;
            inorder(node->right);
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(const Vehicle& vehicle) {
        root = insert(root, vehicle);
    }
    
    void display() {
        inorder(root);
    }
};

// Dijkstra's Algorithm for finding shortest path (Assume road network)
void dijkstra(vector<vector<int>>& graph, int source, int n) {
    vector<int> dist(n, INT_MAX);
    dist[source] = 0;
    set<pair<int, int>> pq;  // {distance, node}
    pq.insert({0, source});
    
    while (!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());
        
        for (int v = 0; v < n; v++) {
            if (graph[u][v] != -1) {
                int newDist = dist[u] + graph[u][v];
                if (newDist < dist[v]) {
                    pq.erase({dist[v], v});
                    dist[v] = newDist;
                    pq.insert({dist[v], v});
                }
            }
        }
    }
    
    cout << "Shortest Path Distances from Source:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << ": " << dist[i] << endl;
    }
}

int main() {
    // Create vehicles
    Vehicle v1("ABC123", 100);
    Vehicle v2("XYZ456", 150);
    Vehicle v3("LMN789", 200);
    
    // Priority Queue Example (Heap)
    TrafficControl trafficControl;
    trafficControl.addVehicle(v1);
    trafficControl.addVehicle(v2);
    trafficControl.addVehicle(v3);
    trafficControl.restrictVehicles(120);
    
    // Binary Search Tree (BST)
    BST bst;
    bst.insert(v1);
    bst.insert(v2);
    bst.insert(v3);
    bst.display();
    
    // AVL Tree
    AVLTree avl;
    avl.insert(v1);
    avl.insert(v2);
    avl.insert(v3);
    avl.display();
    
    // Dijkstra's Algorithm Example
    int n = 5;
    vector<vector<int>> graph = {
        {-1, 10, -1, -1, 5},
        {10, -1, 1, -1, -1},
        {-1, 1, -1, 4, -1},
        {-1, -1, 4, -1, 2},
        {5, -1, -1, 2, -1}
    };
    
    cout << "Running Dijkstra's Algorithm from Source Node 0:" << endl;
    dijkstra(graph, 0, n);
    
    return 0;
}
