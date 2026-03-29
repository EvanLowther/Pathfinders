#include "dijkstras.h"
#include <functional> // for std::greater
#include <limits>
using namespace std;

Dijkstras::Dijkstras(const Graph& graph, int startNode, int endNode) {
    int n = graph.size();

    // Distance from start to each node (initialized to large value)
    vector<int> distance(n, numeric_limits<int>::max());
    distance[startNode] = 0;

    // Priority queue stores (distance, node)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, startNode});

    // Predecessor array to reconstruct path
    vector<int> predecessor(n, -1);

    while(!pq.empty()) {
        auto [dist, currNode] = pq.top();
        pq.pop();

        if(dist > distance[currNode]) continue; // outdated entry
        if(currNode == endNode) break;          // reached goal

        // Explore neighbors
        for(int next : graph.neighbors(currNode)) {
            if(distance[next] > distance[currNode] + 1) { // edge weight = 1
                distance[next] = distance[currNode] + 1;
                pq.push({distance[next], next});
                predecessor[next] = currNode;
            }
        }

        visited.push_back(currNode); // record visit order
    }

    visitedCount = visited.size(); // total visited nodes
    shortestPath = printShortestPath(predecessor.data(), startNode, endNode); // reconstruct path
}

// Reconstruct shortest path as vector
vector<int> Dijkstras::printShortestPath(int* predecessor, int startNode, int endNode) {
    vector<int> path;
    int it = endNode;

    // If no path exists
    if(predecessor[it] == -1 && it != startNode) {
        pathCount = 0;
        return path;
    }

    while(it != -1) {
        path.insert(path.begin(), it); // prepend
        pathCount++;
        if(it == startNode) break;
        it = predecessor[it];
    }

    return path;
}

// Get shortest path
vector<int> Dijkstras::getShortestPath() {
    return shortestPath;
}

// All visited nodes
vector<int> Dijkstras::getVisited() {
    return visited;
}

// Total visited nodes count
int Dijkstras::getVisitedCount() {
    return visitedCount;
}

// Shortest Path length (number of nodes)
int Dijkstras::getPathCount() {
    return pathCount;
}