#include "dijkstras.h"
#include <functional> // needed for std::greater
using namespace std;

Dijkstras::Dijkstras(const Graph& graph, int startNode, int endNode) {
    int* distance = new int[graph.size()];
    for(int i = 0; i < graph.size(); i++){
        distance[i] = 100000; // assuming a node distance will never be more than 100k
    }
    distance[startNode] = 0; // start node -> start node distance is 0

    // priority queue now stores (distance, node)
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<>
    > priorityQueue;

    priorityQueue.push({0, startNode});

    int* predecessor = new int[graph.size()];   // every entry node[i] holds the previous node in the shortest path

    while(!priorityQueue.empty()){
        pair<int,int> top = priorityQueue.top();
        priorityQueue.pop();

        int currNode = top.second;

        // skip outdated entries
        if(top.first > distance[currNode]){
            continue;
        }

        if(currNode == endNode){
            break;                  // if the end node has been found, do not continue
        }

        vector<int> connectedNodes = graph.neighbors(currNode);
        for(int nextNode : connectedNodes){
            // if the path through the current node is shorter than what's in the distance array
            if(distance[nextNode] > distance[currNode] + 1){
                distance[nextNode] = distance[currNode] + 1; // update new shortest distance
                priorityQueue.push({distance[nextNode], nextNode}); // add node to the priority queue
                predecessor[nextNode] = currNode;            // add the current node as the connected node's shortest predecessor
            }
        }

        visited.push_back(currNode);   // store visit order
    }

    visitedCount = visited.size(); // total visited nodes

    shortestPath = printShortestPath(predecessor, startNode, endNode);

    delete[] predecessor;
    delete[] distance;
}

string Dijkstras::printShortestPath(int* predecessor, int startNode, int endNode){
    string nodePath = to_string(endNode);
    int it = predecessor[endNode];

    pathCount = 1; // start from end node

    // safeguard: stop if it == -1 to avoid infinite loop
    while(it != startNode && it != -1){
        nodePath = to_string(it) + " " + nodePath;
        it = predecessor[it];
        pathCount++;
    }

    if(it == startNode){
        nodePath = to_string(startNode) + " " + nodePath;
        pathCount++;
    }

    return nodePath;
}

// Shortest Path 
string Dijkstras::getShortestPath(){ 
    return shortestPath;
}

// All Visited Nodes
vector<int> Dijkstras::getVisited(){
    return visited;
}

// Total Visited Nodes (Count)
int Dijkstras::getVisitedCount(){
    return visitedCount;
}

// Fastest Path Count
int Dijkstras::getPathCount(){ 
    return pathCount;
}