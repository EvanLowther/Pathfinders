//
// Created by maris on 3/25/2026.
//

#include "Astar.h"
#include <set>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;

// estimated cost from node to goal (the heuristic)
// it is estimated because we cant be sure of the actual distance until we find the actual path
// because there may be obstacles in the way that are currently undetected
double heuristicValue(int node, int goal) {
    return abs(node - goal);
}

AStarResult AStar::run(const Graph& graph, int start, int goal) {
    int n = graph.size();

    // distanceTravelled represents the distance from the start to now
    vector<double> distanceTravelled(n, numeric_limits<double>::max());
    vector<int> parent(n, -1);

    // using pseudocode steps from geeksforgeeks:
    // 1. initialize open list
    set<Node> open;

    // 2. initialize closed list
    set<int> visited;

    // putting start node in open list
    distanceTravelled[start] = 0;
    open.insert({start, heuristicValue(start, goal)});

    // 3. while open list not empty
    while (!open.empty()) {
        // a. find node w smallest f:
        // f(n) = g(n) + h(n), where g = distanceTravelled, h = heuristicValue
        Node q = *open.begin();

        // b. remove from open list
        open.erase(open.begin());
        int current = q.id;

        // add to visited set
        visited.insert(current);

        // d(i) if goal reached -> stop
        if (current == goal) {
            vector<int> path;
            int temp = goal;
            // build path backwards
            while (temp != -1) {
                path.push_back(temp);
                temp = parent[temp];
            }
            reverse(path.begin(), path.end());
            return {visited, path};
        }
        // c. generate neighbors/successors
        vector<int> neighbors = graph.neighbors(current);

        // d. for each successor:
        for (int i = 0; i < neighbors.size(); i++) {
            int next = neighbors[i];
            // skip if visited
            if (visited.count(next)) {
                continue;
            }
            // d(ii) compute g, h, f
            double g = distanceTravelled[current] + 1; // all edges weight = 1
            double h = heuristicValue(next, goal);
            double f = g + h;

            // skip if worse path
            if (g >= distanceTravelled[next]) {
                continue;
            }
            // update values
            distanceTravelled[next] = g;
            parent[next] = current;

            // add to open list
            open.insert({next, f});
        }
    }

    // if no path found
    return {visited, {}};
}