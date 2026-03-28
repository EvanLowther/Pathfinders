#include "dijkstras.h"
#include <functional> // needed for std::greater

Dijkstras::Dijkstras(const Graph& graph, int startNode, int endNode) {
    int* distance = new int[graph.size()];
    for(int i = 0; i < graph.size(); i++){
        distance[i] = 100000; // assuming a node distance will never be more than 100k
    }
    distance[startNode] = 0; // start node -> start node distance is 0

    // priority queue now stores (distance, node)
    std::priority_queue<
        std::pair<int,int>,
        std::vector<std::pair<int,int>>,
        std::greater<>
    > priorityQueue;

    priorityQueue.push({0, startNode});

    int* predecessor = new int[graph.size()];   //every entry node[i] holds the previous node in the shortest path

    set<int> visitedNodes; //prevent looping back to visited nodes

    while(!priorityQueue.empty()){
        std::pair<int,int> top = priorityQueue.top();
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
            // if the connected node has not been visited and the path through
            // the current node is shorter than whats in the distance array
            if(visitedNodes.find(nextNode) == visitedNodes.end() && distance[nextNode] > distance[currNode] + 1){
                distance[nextNode] = distance[currNode] + 1; // update new shortest distance
                priorityQueue.push({distance[nextNode], nextNode}); // add node to the priority queue
                predecessor[nextNode] = currNode;            // add the current node as the connected node's shortest predecessor
            }
        }

        visitedNodes.insert(currNode);
        visited.push_back(currNode);   // store visit order
    }

    visitedCount = visited.size(); // total visited nodes

    shortestPath = printShortestPath(predecessor, startNode, endNode);

    delete[] predecessor;
    delete[] distance;
}

std::string Dijkstras::printShortestPath(int* predecessor, int startNode, int endNode){
    std::string nodePath = std::to_string(endNode);
    int it = predecessor[endNode];

    pathCount = 1; // start from end node

    while(it != startNode){
        nodePath = std::to_string(predecessor[it]) + " " + nodePath;
        it = predecessor[it];
        pathCount++;
    }

    pathCount++; // include start node
    return nodePath;
}
// Shortest Path 
std::string Dijkstras::getShortestPath(){ 
    return shortestPath;
}
// All Visited Nodes
std::vector<int> Dijkstras::getVisited(){
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