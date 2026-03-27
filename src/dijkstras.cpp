#include "dijkstras.h"

Dijkstras::Dijkstras(const Graph& graph, int startNode, int endNode) {
    int* distance = new int[graph.size()];
    for(int i = 0; i < graph.size(); i++){
        distance[i] = 100000; // assuming a node distance will never be more than 100k
    }
    distance[startNode] = 0; // start node -> start node distance is 0

    std::queue<int> priorityQueue;
    priorityQueue.push(startNode);

    int* predecessor = new int[graph.size()];   //every entry node[i] holds the previous node in the shortest path

    set<int> visitedNodes; //prevent looping back to visited nodes

    while(!priorityQueue.empty()){
        int currNode = priorityQueue.front();
        priorityQueue.pop();
        if(currNode = endNode){
            break;                  // if the end node has been found, do not continue
        }
        vector<int> connectedNodes = graph.neighbors(currNode);
        for(int nextNode : connectedNodes){
            // if the connected node has not been visited and the path through
            // the current node is shorter than whats in the distance array
            if(visitedNodes.find(currNode) != visitedNodes.end() && distance[nextNode] > distance[currNode] + 1){
                distance[nextNode] = distance[currNode] + 1; // update new shortest distance
                priorityQueue.push(nextNode);                // add node to the priority queue
                predecessor[nextNode] = currNode;            // add the current node as the connected node's shortest predecessor
            }
        }
        visitedNodes.insert(currNode);
    }
    shortestPath = printShortestPath(predecessor, endNode);
}

std::string Dijkstras::printShortestPath(int* predecessors, int endNode){

}
