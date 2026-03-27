#include "dijkstras.h"

Dijkstras::Dijkstras(const Graph& graph, int startNode, int endNode) {
    int* distance = new int[graph.size()];
    for(int i = 0; i < graph.size(); i++){
        distance[i] = 100000; // assuming a node distance will never be more than 100k
    }
    distance[startNode] = 0; // start node -> start node distance is 0
    std::queue<int> priorityQueue;
    priorityQueue.push(startNode);
    set<int> visitedNode; //prevent looping back to visited nodes
    while(!priorityQueue.empty()){
        int top = priorityQueue.front();
        priorityQueue.pop();
    }
}
