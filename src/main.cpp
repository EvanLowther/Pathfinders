#include <iostream>
#include <vector>
#include "parser.h"
#include "graph.h"
using namespace std;

int main() {
    //Read/analyze function for the roadNet-PA.txt file
    cout << "Parsing Pennsylvania road network:" << endl;
    vector<pair<int,int>> edges = parseFile("../data/roadNet-PA.txt");
    
    //Build the graph (this is where the adjacency list is created)
    Graph test(edges, 1090920);

    // Export for visualizer 
    test.exportJSON("../data/road_network.json");
    cout << "Updated Exported JSON FIle";

    //Test to demonstrate the Adjacency List
    cout << "\n--- ADJACENCY LIST DEMO ---" << endl;
    
    //Pick a test node (e.g., node 100) and get its neighbors
    int testNode = 10; 
    
    vector<int> neighbors = test.neighbors(testNode);

    cout << "Node ID: " << testNode << endl;
    cout << "Number of outgoing roads: " << neighbors.size() << endl;
    
    if (!neighbors.empty()) {
        cout << "Connected to: ";
        for (size_t i = 0; i < neighbors.size(); ++i) {
            cout << neighbors[i] << (i == neighbors.size() - 1 ? "" : ", ");
        }
        cout << endl;
    } else {
        cout << "This node has no outgoing connections in the dataset." << endl;
    }

    //Print Graph Statistics
    cout << "\n--- GRAPH STATISTICS ---" << endl;
    cout << "Total Nodes: " << test.size() << endl;


    return 0;
}