#include "graph.h"
#include <algorithm>

Graph::Graph(const vector<pair<int,int>>& edges, int n){
    nodeCount = n;
    adjacencyList.resize(nodeCount);

    /*
    This is meant for iterating through all edges and fill the adjacency list
    Edge is a pair - connection between nodes (x,y) = (FromNodeID, ToNodeID)
    Adjacency List Example:
    Say we have edges (0,1), (0,2), (1,2)
    AdjacencyList:
    
    Where Node[i] = {_,_,_,...} i, is the Node # and {} is the list of all connected nodes
    Node 0 = {1,2}
    Node 1 = {0,2}
    Node 2 = {0, 1}
    
    */
    for (auto &edgeXY : edges) {
        int x = edgeXY.first;    //Node A in the edge
        int y = edgeXY.second;   //Node B in the edge

        //Add each node to the others adjacency list (connected to eachother)
        adjacencyList[x].push_back(y); 
        adjacencyList[y].push_back(x);
    }
    //Sort neighbor lists (ascending order)
    for(int i = 0; i < nodeCount; i++){
        sort(adjacencyList[i].begin(), adjacencyList[i].end());
    }
}
    //Returns list of neighbors to a Node
    const vector<int>& Graph::neighbors(int node) const{
        return adjacencyList[node];
    }
    //Total Nodes in graph
    int Graph::size() const{
        return nodeCount;
    }
    void Graph::exportJSON(const string& filename) const {
    ofstream outFile(filename);
    
    // Header for the CSV
    outFile << "ID,Source,Target\n";

    //Amount of nodes in csv
    int limit = 100000; 
    int actualNodes = min(nodeCount, limit);
    int edgeId = 0;

    for (int i = 0; i < actualNodes; ++i) {
        for (int neighbor : adjacencyList[i]) {
            // u < v logic prevents double-counting the road (e.g., 0-1 and 1-0)
            if (i < neighbor && neighbor < actualNodes) {
                outFile << edgeId << "," << i << "," << neighbor << "\n";
                edgeId++;
            }
        }
    }
    
    outFile.close();
}