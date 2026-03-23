#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Graph{
private:
    int nodeCount;      //Total Node count in graph
    vector<vector<int>> adjacencyList; //Adjacency list to store neigbors for each node
public:
    //Takes edges and total number of nodes
    Graph(const vector<pair<int,int>>& edges, int n);

    //Test to print the neighbors of the first 10 nodes
    void printTestNodes(int n) const;
    //neighbors of a node
    const vector<int>& neighbors(int node) const;

    int size() const; //Number of Nodes
};