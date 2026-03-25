#include <iostream>
#include "parser.h"
#include "graph.h"
using namespace std;

int main() {
    //Read/analyze function for the roadNet-PA.txt file
    vector<pair<int,int>> edges = parseFile("data/roadNet-PA.txt");
    Graph test(edges, 1090920);

    //Export roadNet-PA.txt to JSON (readble for JS) to make visualizer
    test.exportJSON("data/road_network.json");

    return 0;
}