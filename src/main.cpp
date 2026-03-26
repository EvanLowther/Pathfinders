#include <iostream>
#include <vector>
#include <set>
#include "parser.h"
#include "graph.h"
#include "AStar.h"

using namespace std;

int main() {
    //Load and Parse Data
    cout << "Parsing Pennsylvania road network..." << endl;
    vector<pair<int, int>> edges = parseFile("../data/roadNet-PA.txt");
    
    //Build the Graph
    //Total nodes in roadNet-PA.txt is  1,090,920
    int totalNodes = 1090920;
    Graph test(edges, totalNodes);

    //Export for Visualizer
    test.exportJSON("../data/road_network.json");
    cout << "Updated Exported JSON File." << endl;

    //Run A* Pathfinding
    cout << "\n--- ASTAR PATHFINDING TEST ---" << endl;
    
    //Test parameters: feel free to change these IDs
    int startNode = 10;
    int goalNode = 500; 

    cout << "Searching for shortest path from " << startNode << " to " << goalNode << endl;

    AStar astar;
    AStarResult result = astar.run(test, startNode, goalNode);

    //Print All Visited Nodes
    cout << "\nALL NODES VISITED BY ALGORITHM (" << result.visited.size() << " total):" << endl;
    if (result.visited.empty()) {
        cout << "None." << endl;
    } else {
        for (int node : result.visited) {
            cout << node << " ";
        }
        cout << endl;
    }

    //Print the Fastest Path
    cout << "\n--- FINAL RESULTS ---" << endl;
    if (!result.path.empty()) {
        cout << "FASTEST PATH FOUND (" << result.path.size() << " nodes):" << endl;
        for (size_t i = 0; i < result.path.size(); ++i) {
            cout << result.path[i] << (i == result.path.size() - 1 ? "" : " -> ");
        }
        cout << endl;
    } else {
        cout << "No path exists between node " << startNode << " and node " << goalNode << "." << endl;
    }

    //Graph Statistics
    cout << "\n--- GRAPH STATISTICS ---" << endl;
    cout << "Total Nodes in Dataset: " << test.size() << endl;

    return 0;
}