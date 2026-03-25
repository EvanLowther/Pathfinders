#pragma once
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Graph{
private:
    int nodeCount;      //Total Node count in graph
    vector<vector<int>> adjacencyList; //Adjacency list to store neigbors for each node
public:
    //Takes edges and total number of nodes
    Graph(const vector<pair<int,int>>& edges, int n);
    
    //neighbors of a node
    const vector<int>& neighbors(int node) const;

    //JSON file formated to create a visual graph
    void exportJSON(const string& filename) const;

    int size() const; //Number of Nodes
};