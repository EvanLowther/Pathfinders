#include <iostream>
#include "parser.h"
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

    //First 10 edges (functionality test)
    for(int i = 0; i < 10; i++){
        cout << edges[i].first << " -> " << edges[i].second << endl;
    }
    return 0;
}