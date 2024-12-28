#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>
#include <fstream>

// Product struct
struct Product {
    std::string id;
    std::string name;
    std::string category;
    int stock;
    std::string expiry_date;
};

// Function to decrease stock and replenish based on stock levels
void decrease_and_conquer(std::map<std::string, int>& stock_levels, int threshold) {
    std::cout << "Starting inventory replenishment process..." << std::endl;
    for (auto& item : stock_levels) {
        if (item.second < threshold) {
            std::cout << "Replenishing " << item.first << " to " << threshold << " units." << std::endl;
            item.second = threshold;
        }
    }
}

// Function to partition inventory by product category
std::map<std::string, std::vector<Product>> partition_inventory(const std::vector<Product>& products) {
    std::cout << "Partitioning inventory by product category..." << std::endl;
    std::map<std::string, std::vector<Product>> categories;
    for (const auto& product : products) {
        categories[product.category].push_back(product);
    }
    return categories;
}

// Function to sort products by expiry date using std::sort (faster)
void sort_by_expiry_date(std::vector<Product>& products) {
    std::cout << "Sorting products by expiry date..." << std::endl;
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.expiry_date < b.expiry_date;
    });
}

// Kruskal's algorithm to find the minimum spanning tree (MST) for warehouse layout optimization
struct Edge {
    std::string u, v;
    int weight;
};

class DisjointSet {
public:
    void make_set(const std::string& x) {
        parent[x] = x;
        rank[x] = 0;
    }

    std::string find(const std::string& x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void union_sets(const std::string& x, const std::string& y) {
        std::string rootX = find(x);
        std::string rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                ++rank[rootX];
            }
        }
    }

private:
    std::map<std::string, std::string> parent;
    std::map<std::string, int> rank;
};

void kruskal_algorithm(std::vector<Edge>& edges, std::set<std::string>& nodes) {
    std::cout << "Running Kruskal's Algorithm for warehouse layout optimization..." << std::endl;
    DisjointSet ds;
    // Initialize disjoint sets for each node
    for (const auto& node : nodes) {
        ds.make_set(node);
    }

    // Sort edges by weight
    std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
        return e1.weight < e2.weight;
    });

    // Kruskal's algorithm
    std::cout << "Optimized Warehouse Layout (Minimum Spanning Tree):" << std::endl;
    for (const auto& edge : edges) {
        std::string root_u = ds.find(edge.u);
        std::string root_v = ds.find(edge.v);
        if (root_u != root_v) {
            std::cout << edge.u << " - " << edge.v << " (Weight: " << edge.weight << ")" << std::endl;
            ds.union_sets(edge.u, edge.v);
        }
    }
}

// Red-Black Tree implementation (simplified)
class RedBlackTree {
public:
    struct Node {
        Product data;
        Node* left;
        Node* right;
        Node* parent;
        bool color;  // True for Red, False for Black
    };

    RedBlackTree() : root(nullptr) {}

    void insert(const Product& product) {
        Node* newNode = new Node{product, nullptr, nullptr, nullptr, true};  // New node is Red
        insert_fixup(newNode);
    }

    void insert_fixup(Node* node) {
        // Simplified insertion fixup code (does not implement full red-black properties)
        if (!root) {
            root = node;
            node->color = false;  // Root is always Black
        }
    }

    void display_inorder(Node* node) {
        if (!node) return;
        display_inorder(node->left);
        std::cout << node->data.name << " (" << node->data.stock << " units)" << std::endl;
        display_inorder(node->right);
    }

    Node* get_root() {
        return root;
    }

private:
    Node* root;
};

// Main function
int main() {
    // Specify the path of the input file (ensure the file exists in this path)
    std::string filename = "input_data.txt"; // Make sure this file is in the correct location

    std::cout << "Reading input data from: " << filename << std::endl;

    std::ifstream infile(filename);
    std::vector<Product> products;
    std::string id, name, category, expiry;
    int stock;

    // Check if file opened successfully
    if (!infile) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }

    while (infile >> id >> name >> category >> stock >> expiry) {
        products.push_back(Product{id, name, category, stock, expiry});
    }
    infile.close();

    // Check if products vector is populated
    if (products.empty()) {
        std::cerr << "No products found in input file!" << std::endl;
        return -1;
    }

    std::cout << "Products loaded from file successfully!" << std::endl;

    // Step 1: Replenish Inventory using Decrease and Conquer
    std::map<std::string, int> stock_levels;
    for (const auto& prod : products) {
        stock_levels[prod.name] = prod.stock;
    }
    decrease_and_conquer(stock_levels, 10);

    // Step 2: Partition Inventory by Category
    std::map<std::string, std::vector<Product>> categories = partition_inventory(products);
    std::cout << "Inventory categorized by product type:" << std::endl;
    for (const auto& category : categories) {
        std::cout << "Category: " << category.first << std::endl;
        for (const auto& product : category.second) {
            std::cout << "  Product: " << product.name << ", Stock: " << product.stock << ", Expiry: " << product.expiry_date << std::endl;
        }
    }

    // Step 3: Sort Products by Expiry Date
    sort_by_expiry_date(products);
    std::cout << "Products sorted by expiry date:" << std::endl;
    for (const auto& prod : products) {
        std::cout << "Product: " << prod.name << ", Expiry Date: " << prod.expiry_date << std::endl;
    }

    // Step 4: Optimize Warehouse Layout using Kruskal's Algorithm
    std::set<std::string> nodes = {"Fruits", "Dairy", "Vegetables"};
    std::vector<Edge> edges = {
        {"Fruits", "Dairy", 10},
        {"Fruits", "Vegetables", 15},
        {"Dairy", "Vegetables", 5}
    };
    kruskal_algorithm(edges, nodes);

    return 0;
}
