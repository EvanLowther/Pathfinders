#include <iostream>
#include <vector>
#include <set>
#include "parser.h"
#include "graph.h"
#include "AStar.h"
#include "dijkstras.h"
using namespace std;

int main() {
    //Read/analyze function for the roadNet-PA.txt file
    cout << "Parsing Pennsylvania road network:" << endl;
    vector<pair<int,int>> edges = parseFile("data/roadNet-PA.txt"); // the road network file must be in the build directory
    
    //Build the Graph
    //Total nodes in roadNet-PA.txt is  1,090,920
    int totalNodes = 1090920;
    Graph test(edges, totalNodes);

    //Export for Visualizer
    test.exportJSON("../data/road_network.json");
    cout << "Updated Exported JSON File." << endl;

    //Test parameters: feel free to change these IDs
    int startNode = 10;
    int goalNode = 500;
    cout << "Searching for shortest path from " << startNode << " to " << goalNode << endl;

    //Run A* Pathfinding
    cout << "\n--- ASTAR ALGORITHM ---" << endl;

    AStar astar;
    AStarResult result = astar.run(test, startNode, goalNode);

    //Print A* All Visited Nodes
    cout << "\nALL NODES VISITED BY A* ALGORITHM (" << result.visited.size() << " total):" << endl;
    if (result.visited.empty()) {
        cout << "None." << endl;
    } else {
        for (int node : result.visited) {
            cout << node << " ";
        }
        cout << endl;
    }

    // Dijkstras testing
    cout << "\n--- Dijkstras Algorithm ---" << endl;
    Dijkstras DijkExample(test, startNode, goalNode);

    // Print All Visited Nodes
    cout << "\nALL NODES VISITED BY DIJKSTRA ALGORITHM (" << DijkExample.getVisitedCount() << " total):" << endl;
    vector<int> visitedD = DijkExample.getVisited();
    if (visitedD.empty()) {
        cout << "None." << endl;
    } else {
        for (int node : visitedD) {
            cout << node << " ";
        }
        cout << endl;
    }

    //Print Shortest Path
    cout << "\nDIJKSTRA SHORTEST PATH:" << endl;
    cout << DijkExample.getShortestPath() << endl;

    cout << "\nA* SHORTEST PATH:" << endl;
    if (!result.path.empty()) {
    for (size_t i = 0; i < result.path.size(); ++i) {
        cout << result.path[i] << (i == result.path.size() - 1 ? "" : " ");
    }
    cout << endl;
    } else {
    cout << "No path exists between node " << startNode << " and node " << goalNode << "." << endl;
    }

    //Print Path Stats
    cout << "\nTOTAL NODES SEARCHED: " << endl;
    cout << "DIKSTRA TOTAL: " << DijkExample.getVisitedCount() <<endl;
    cout << "A* TOTAL: " << result.visited.size() << endl;

    cout << "\nShortest Path Comparison: " << endl;
    cout << "DIJKSTRA Fastest PATH: " << DijkExample.getPathCount() << " nodes" << endl;
    cout << "A* Fastest PATH: " << result.path.size() << " nodes" << endl;

    return 0;
}