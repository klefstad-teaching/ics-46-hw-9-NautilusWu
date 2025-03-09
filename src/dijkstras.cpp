#include "dijkstras.h"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Dijkstra's algorithm
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    // n = G.numVertices
    int n = G.size();
    // cout << "n: " << n << endl;
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);

    // Put <distance, vertex> pairs in the priority queue, ordered by distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        // u is the src vertex of the edge with the smallest weight (distance)
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if ((distance[u] + weight) < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }

    return distance;
}

// Get the shortest path from source to destination
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) {
        return path; // No path
    }

    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }

    reverse(path.begin(), path.end());
    return path;
}

// Print the path and total cost
void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "No path exists." << endl;
        return;
    }

    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i != v.size() - 1) {
            cout << " ";
        }
    }
    cout << "\nTotal cost is " << total << endl;;
}


