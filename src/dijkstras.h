#ifndef DIJKSTRAS_H
#define DIJKSTRAS_H
#pragma once

#include "graph.h"
#include <set>
#include <vector>
#include <queue>

class Dijkstras{
    std::string shortestPath;
public:
    Dijkstras(const Graph& graph, int startNode, int endNode);
    std::stringstream printShortestPath(int* predecessors, int endNode);

};

#endif // DIJKSTRAS_H
