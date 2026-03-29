//
// Created by maris on 3/25/2026.
//

#pragma once

#include "graph.h"
#include <set>
#include <vector>

using namespace std;

struct AStarResult {
    set<int> visited; // all nodes visited (order doesnt matter)
    vector<int> path; // optimal path found using a*
};

// open list
struct Node {
    int id;
    double f;

    bool operator<(const Node &other) const {
        if (f == other.f)
            return id < other.id;
        return f < other.f;
    }
};

class AStar {
    public:
    AStarResult run(const Graph &graph, int start, int goal);
};
