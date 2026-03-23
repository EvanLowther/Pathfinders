#include <iostream>
#include "parser.h"
#include "graph.h"
using namespace std;

int main(){
    /*
    This section is to test that the parser works
    making sure that it reads the dataset properly
    */

    //Call parser to read the dataset
    vector<pair<int,int>> edges = parseFile("data/roadNet-PA.txt");
    //Total edge count (Should be 1541898 - undirected graph)
    cout<< "Total edges: " << edges.size() << endl;
    
    //print out all Nodes and the list of its connections
    Graph test(edges, 1090920);
    test.printTestNodes(edges.size());

    //First 10 edges (functionality test)
    for(int i = 0; i < 10; i++){
        cout << edges[i].first << " -> " << edges[i].second << endl;
    }
    return 0;
}