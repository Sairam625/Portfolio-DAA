#include <iostream>
using namespace std;


int find(int p[], int rank[], int u) 
{
    if (p[u] != u) {
        p[u] = find(p, rank, p[u]);  
    }
    return p[u];
}


void union(int p[], int rank[], int u, int v) {
    int rootU = find(p, rank, u);  
    int rootV = find(p, rank, v);  

    if (rootU != rootV) {
      
        if (rank[rootU] > rank[rootV]) {
            p[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            p[rootU] = rootV;
        } else {
            p[rootV] = rootU;  // If same rank, make one root
            rank[rootU]++;  // Increment rank
        }
    }
}

// Print the groups and their roots
void printGroups(int p[], int rank[], int n) {
    cout << "Groups:\n";
    for (int i = 0; i < n; i++) {
        cout << "Gathering " << i << " is in group " << find(p, rank, i) << endl;
    }
}

// Print the tree structure of the groups
void printHierarchy(int p[], int n) {
    cout << "\nTree Structure:\n";
    for (int i = 0; i < n; i++) {
        int root = find(p, rank, i);
        if (i != root) {
            cout << "Gathering " << i << ": Parent -> Gathering " << root << endl;
        } else {
            cout << "Gathering " << i << ": Root\n";
        }
    }
}

int main() {
    int n = 5;  // Number of gatherings
    int p[n], rank[n];

    // Initialize each gathering to be its own parent and rank to 0
    for (int i = 0; i < n; i++) {
        p[i] = i;
        rank[i] = 0;
    }

    int u, v;
    char choice;

    do {
        // Merge two gatherings
        cout << "Enter two gatherings to merge (u v): ";
        cin >> u >> v;
        union(p, rank, u, v);

        // Print the groups and their hierarchical structure
        printGroups(p, rank, n);
        printHierarchy(p, n);

        // Check if two gatherings are in the same group
        cout << "Enter two gatherings to check (u v): ";
        cin >> u >> v;
        if (find(p, rank, u) == find(p, rank, v)) {
            cout << "Gatherings " << u << "and" << v << "are in the same group.\n";
        } else {
            cout << "Gatherings" << u << " and " << v << "are in different groups.\n";
        }

        // Ask if the user wants to continue
        cout << "Do you want to continue? (y/n): ";
        cin >> choice;

    } while (choice == 'y');

    return 0;
}
