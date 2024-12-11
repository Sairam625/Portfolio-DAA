#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
using namespace std;
typedef pair<int, int> pii;

void dijkstra(const unordered_map<int, vector<pii>>& graph, int start) {
    
    unordered_map<int, int> distances;
    unordered_map<int, int> predecessors;

    for (const auto& node : graph) {
        distances[node.first] = numeric_limits<int>::max(); 
        predecessors[node.first] = -1; 
    }
    distances[start] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> priorityQueue;
    priorityQueue.push({0, start});

    
    while (!priorityQueue.empty()) {
        int currentDistance = priorityQueue.top().first;
        int currentNode = priorityQueue.top().second;
        priorityQueue.pop();

        
        for (const auto& neighbor : graph.at(currentNode)) {
            int neighborNode = neighbor.first;
            int weight = neighbor.second;
            int distance = currentDistance + weight;

            
            if (distance < distances[neighborNode]) {
                distances[neighborNode] = distance;
                predecessors[neighborNode] = currentNode;

                
                priorityQueue.push({distance, neighborNode});
            }
        }
    }


    cout << "Shortest distances from start node:" << endl;
    for (const auto& distance : distances) {
        cout << "Node " << distance.first << ": " << distance.second << endl;
    }

    cout << "Predecessors for each node:" << endl;
    for (const auto& predecessor : predecessors) {
        cout << "Node " << predecessor.first << ": " << prede
