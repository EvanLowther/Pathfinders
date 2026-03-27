#ifndef DIJKSTRAS_H
#define DIJKSTRAS_H
#pragma once

#include "graph.h"
#include <set>
#include <vector>
#include<queue>

class Dijkstras{
public:
    Dijkstras(const Graph& graph, int startNode, int endNode);
    void PrintAdjList();
    void PrintShortestPath();

};

#endif // DIJKSTRAS_H
