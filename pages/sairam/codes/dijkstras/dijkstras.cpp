#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
using namespace std;

// Define a pair to represent (distance, node)
typedef pair<int, int> pii;

void dijkstra(const unordered_map<int, vector<pii>>& graph, int start) {
    // Initialize distances and predecessors
    unordered_map<int, int> distances;
    unordered_map<int, int> predecessors;

    for (const auto& node : graph) {
        distances[node.first] = numeric_limits<int>::max(); // Set all distances to infinity
        predecessors[node.first] = -1; // -1 indicates no predecessor
    }

    // Set the distance to the start node to 0
    distances[start] = 0;

    // Priority queue to store (distance, node)
    priority_queue<pii, vector<pii>, greater<pii>> priorityQueue;
    priorityQueue.push({0, start});

    // Process the priority queue
    while (!priorityQueue.empty()) {
        int currentDistance = priorityQueue.top().first;
        int currentNode = priorityQueue.top().second;
        priorityQueue.pop();

        // Iterate over the neighbors of the current node
        for (const auto& neighbor : graph.at(currentNode)) {
            int neighborNode = neighbor.first;
            int weight = neighbor.second;
            int distance = currentDistance + weight;

            // If a shorter path is found
            if (distance < distances[neighborNode]) {
                distances[neighborNode] = distance;
                predecessors[neighborNode] = currentNode;

                // Update the priority queue
                priorityQueue.push({distance, neighborNode});
            }
        }
    }

    // Output the results
    cout << "Shortest distances from start node:" << endl;
    for (const auto& distance : distances) {
        cout << "Node " << distance.first << ": " << distance.second << endl;
    }

    cout << "Predecessors for each node:" << endl;
    for (const auto& predecessor : predecessors) {
        cout << "Node " << predecessor.first << ": " << prede
