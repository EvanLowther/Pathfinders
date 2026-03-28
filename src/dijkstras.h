#pragma once

#include "graph.h"
#include <set>
#include <vector>
#include <queue>

class Dijkstras{
    std::string shortestPath;

    std::vector<int> visited;   // store all visited nodes
    int visitedCount = 0;       // total visited nodes
    int pathCount = 0;          // number of nodes in shortest path

public:
    Dijkstras(const Graph& graph, int startNode, int endNode);
    std::string printShortestPath(int* predecessors, int startNode, int endNode);
    std::string getShortestPath();

    std::vector<int> getVisited();
    int getVisitedCount();
    int getPathCount();
};