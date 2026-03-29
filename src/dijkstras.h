#pragma once

#include "graph.h"
#include <set>
#include <vector>
#include <queue>

class Dijkstras{
    std::vector<int> shortestPath; // store path as vector

    std::vector<int> visited;   // store all visited nodes
    int visitedCount = 0;       // total visited nodes
    int pathCount = 0;          // number of nodes in shortest path

public:
    // Constructor runs Dijkstra and fills visited + shortestPath
    Dijkstras(const Graph& graph, int startNode, int endNode);

    // Reconstruct shortest path from predecessors array
    std::vector<int> printShortestPath(int* predecessors, int startNode, int endNode);

    // Getters
    std::vector<int> getShortestPath();  // return vector
    std::vector<int> getVisited();
    int getVisitedCount();
    int getPathCount();
};