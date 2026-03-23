#pragma once
#include <vector>
#include <string>

using namespace std;
/*
Simple parser.h file reads the text file containing the network data
Each pair<int,int> represetns and edge-edge connection x->y
filename: path to the dataset
returns: vector of edges
*/

vector<pair<int,int>> parseFile(const string& filename);