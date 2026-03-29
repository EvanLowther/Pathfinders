#include <iostream>
#include <vector>
#include <set>
#include "parser.h"
#include "graph.h"
#include "AStar.h"
#include "dijkstras.h"
using namespace std;

int main() {
    // Read/analyze the roadNet-PA.txt file
    cout << "Parsing Pennsylvania road network:" << endl;
    vector<pair<int,int>> edges = parseFile("../data/roadNet-PA.txt");
    
    // Build the Graph
    int totalNodes = 1090920;
    Graph test(edges, totalNodes);

    // User Input for Node Searching
    int startNode, goalNode;

    cout << "Enter Starting Node (0-" << totalNodes-1 << "): ";
    cin >> startNode;
    while(startNode < 0 || startNode >= totalNodes){
        cout << "Invalid Number (0-" << totalNodes-1 << "), Enter Again: ";
        cin >> startNode;
    }

    cout << "Enter End/Goal Node (0-" << totalNodes-1 << "): ";
    cin >> goalNode;
    while(goalNode < 0 || goalNode >= totalNodes || goalNode == startNode){
        cout << "Invalid goal. Enter Again: ";
        cin >> goalNode;
    }

    // Export for Visualizer (CSV)
    test.exportCSV("../data/road_network.csv", startNode, goalNode);
    cout << "Exported relevant graph nodes surrounding start and goal." << endl;

    cout << "\nSearching for shortest path from " << startNode << " to " << goalNode << endl;

    // --- A* Algorithm ---
    AStar astar;
    AStarResult result = astar.run(test, startNode, goalNode);
    vector<int> visitedA(result.visited.begin(), result.visited.end());

    // --- Dijkstra Algorithm ---
    Dijkstras DijkExample(test, startNode, goalNode);
    vector<int> visitedD = DijkExample.getVisited();
    vector<int> pathD = DijkExample.getShortestPath();

    // --- PRINT ALL EXPLORED NODES ---
    cout << "\nA* All Explored Nodes (" << visitedA.size() << "):" << endl;
    for (int node : visitedA) cout << node << " ";
    cout << endl;

    cout << "\nDijkstra All Explored Nodes (" << visitedD.size() << "):" << endl;
    for (int node : visitedD) cout << node << " ";
    cout << endl;

    // --- PRINT SHORTEST PATHS ---
    cout << "\nDijkstra Shortest Path:" << endl;
    for (size_t i = 0; i < pathD.size(); ++i) cout << pathD[i] << (i == pathD.size()-1 ? "" : " ");
    cout << endl;

    cout << "\nA* Shortest Path:" << endl;
    for (size_t i = 0; i < result.path.size(); ++i) cout << result.path[i] << (i == result.path.size()-1 ? "" : " ");
    cout << endl;

    // --- PRINT SHORTEST PATH LENGTHS ---
    cout << "\nShortest Path Lengths:" << endl;
    cout << "Dijkstra: " << pathD.size() << " Nodes" << endl;
    cout << "A*: " << result.path.size() << " Nodes" << endl;

    // Export Data to CSV for Visualization
    test.exportNodesCSV("../output/astar_explored.csv", visitedA);
    test.exportNodesCSV("../output/dijkstra_explored.csv", visitedD);
    test.exportNodesCSV("../output/astar_path.csv", result.path);
    test.exportNodesCSV("../output/dijkstra_path.csv", pathD);

    return 0;
}