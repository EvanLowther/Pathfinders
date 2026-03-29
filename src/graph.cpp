#include "graph.h"
#include <algorithm>
#include <queue>
#include <set>

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

        //Add each node to the others adjacency list (connected to each other)
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

//Export up to 100k nodes surrounding startNode and goalNode
void Graph::exportCSV(const string& filename, int startNode, int goalNode) const {
    ofstream outFile(filename);

    // Header for the CSV
    outFile << "Source,Target\n";

    // Use BFS to find the most relevant nodes
    const int limit = 100000; 
    set<int> relevantNodes;
    queue<int> q;

    // Start BFS from both startNode and goalNode
    q.push(startNode);
    q.push(goalNode);
    relevantNodes.insert(startNode);
    relevantNodes.insert(goalNode);

    while(!q.empty() && relevantNodes.size() < limit){
        int curr = q.front();
        q.pop();

        for(int neighbor : adjacencyList[curr]){
            if(relevantNodes.size() >= limit) break;
            if(relevantNodes.find(neighbor) == relevantNodes.end()){
                relevantNodes.insert(neighbor);
                q.push(neighbor);
            }
        }
    }

    // Export all edges where both endpoints are in relevantNodes
    for(int node : relevantNodes){
        for(int neighbor : adjacencyList[node]){
            if(relevantNodes.find(neighbor) != relevantNodes.end()){
                outFile << node << "," << neighbor << "\n";
            }
        }
    }

    outFile.close();
}
void Graph::exportNodesCSV(const string& filename, const vector<int>& nodes) const {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return;
    }

    outFile << "node_id\n";  // header
    for (int node : nodes) {
        outFile << node << "\n";
    }

    outFile.close();
}