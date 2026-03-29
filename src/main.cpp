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
    vector<pair<int,int>> edges = parseFile("../data/roadNet-PA.txt");
    
    //Build the Graph
    //Total nodes in roadNet-PA.txt is  1,090,920
    int totalNodes = 1090920;
    Graph test(edges, totalNodes);

    //User Input for Node Searhing
    int startNode;
    int goalNode;

    cout << "Enter Starting Node (0-" << totalNodes-1 << "): ";
    cin >> startNode;
    while(startNode < 0 || startNode >= totalNodes){
        cout << "Invalid Number (0-" << totalNodes-1 << "), Enter Again: ";
        cin >> startNode;
    }

    cout << "Enter End/Goal Node (0-" << totalNodes-1 << "): ";
    cin >> goalNode;
    while(goalNode < 0 || goalNode >= totalNodes){
        cout << "Invalid Number (0-" << totalNodes-1 << "), Enter Again: ";
        cin >> goalNode;
    }

    while(goalNode == startNode){
        cout << "Start and Goal cannot be the same. Enter Again: ";
        cin >> goalNode;
    }

    //Export for Visualizer (CSV)
    test.exportCSV("../data/road_network.csv", startNode, goalNode);
    cout << "Exported relevant graph nodes surrounding start and goal." << endl;

    cout << "\nSearching for shortest path from " << startNode << " to " << goalNode << endl;

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
    vector<int> pathD = DijkExample.getShortestPath();
    if (!pathD.empty()) {
        for (size_t i = 0; i < pathD.size(); ++i) {
        cout << pathD[i] << (i == pathD.size() - 1 ? "" : " ");
        }
        cout << endl;
    } else {
        cout << "No path exists between node " << startNode << " and node " << goalNode << "." << endl;
    }

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
    cout << "\nShortest Path Length: " << endl;
    cout << "DIKSTRA: " << DijkExample.getPathCount() << endl;
    cout << "A*: " << result.path.size() << endl;

    //Export Data to CSV now for Visualization
    vector<int> visitedA(result.visited.begin(), result.visited.end());
    test.exportNodesCSV("../output/astar_explored.csv", visitedA);
    test.exportNodesCSV("../output/dijkstra_explored.csv", visitedD);
    test.exportNodesCSV("../output/astar_path.csv", result.path);
    test.exportNodesCSV("../output/dijkstra_path.csv", DijkExample.getShortestPath());

    return 0;
}