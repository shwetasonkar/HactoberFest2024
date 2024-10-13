#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Define a structure to represent a graph edge
struct Edge {
    int destination;
    int weight;
};

// Function to implement Dijkstra's algorithm
vector<int> dijkstra(int start, const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<int> distances(n, numeric_limits<int>::max());
    distances[start] = 0;

    // Min-heap priority queue to store (distance, vertex)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start}); // Start with the source node

    while (!pq.empty()) {
        auto [current_distance, current_vertex] = pq.top();
        pq.pop();

        // If the distance is greater than the recorded one, skip
        if (current_distance > distances[current_vertex]) {
            continue;
        }

        // Explore neighbors
        for (const Edge& edge : graph[current_vertex]) {
            int neighbor = edge.destination;
            int weight = edge.weight;
            int new_distance = current_distance + weight;

            // If a shorter path is found
            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                pq.push({new_distance, neighbor});
            }
        }
    }

    return distances;
}

int main() {
    // Example graph as an adjacency list
    vector<vector<Edge>> graph = {
        {{1, 4}, {2, 1}}, // Node 0 connected to Node 1 (weight 4) and Node 2 (weight 1)
        {{3, 1}},         // Node 1 connected to Node 3 (weight 1)
        {{1, 2}, {3, 5}}, // Node 2 connected to Node 1 (weight 2) and Node 3 (weight 5)
        {}                // Node 3 has no outgoing edges
    };

    int start_node = 0;
    vector<int> distances = dijkstra(start_node, graph);

    // Output the distances from the start node
    cout << "Distances from node " << start_node << ":\n";
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] == numeric_limits<int>::max()) {
            cout << "Node " << i << ": Unreachable\n";
        } else {
            cout << "Node " << i << ": " << distances[i] << "\n";
        }
    }

    return 0;
}
