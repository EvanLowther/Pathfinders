#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>

using namespace std;

class Graph{
private:
    int nodeCount;      //Total Node count in graph
    vector<vector<int>> adjacencyList; //Adjacency list to store neighbors for each node
public:
    //Takes edges and total number of nodes
    Graph(const vector<pair<int,int>>& edges, int n);
    
    //neighbors of a node
    const vector<int>& neighbors(int node) const;

    //JSON/CSV file formatted to create a visual graph
    //Exports up to 100k nodes surrounding startNode and goalNode
    void exportCSV(const string& filename, int startNode, int goalNode) const;

    int size() const; //Number of Nodes
};