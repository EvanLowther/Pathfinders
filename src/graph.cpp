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
    int limit = 1000; //Number of nodes (out of all in the file) to use out of the data set 
    int actualNodes = min(nodeCount, limit);

    outFile << "{\n  \"nodes\": [\n";
    
    //Id each node that we are representing in the graph
    for (int i = 0; i < actualNodes; ++i) {
        outFile << "    {\"id\": " << i << "}" << (i == actualNodes - 1 ? "" : ",\n");
    }
    
    outFile << "\n  ],\n  \"links\": [\n";

    // Export the edges connected nodes
    bool first = true;
    for (int i = 0; i < actualNodes; ++i) {
        for (int neighbor : adjacencyList[i]) {
            //This exports the edge as a neighbor to the node (in the file) if its within the first n nodes (test limit ex. 1000)
            if (i < neighbor && neighbor < actualNodes) {
                if (!first) outFile << ",\n";
                outFile << "    {\"source\": " << i << ", \"target\": " << neighbor << "}";
                first = false;
            }
        }
    }
    outFile << "\n  ]\n}";
    outFile.close();
}