#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>

/*
parser.cpp file, reads graph dataset file and returns all edges as pairs
Skips empty lines and comment lines
Each line of the dataset shound contain 2 integers(FromNodeID ToNodeID)
*/

vector<pair<int,int>> parseFile(const string& filename){
    set<pair<int,int>> edges;           //Store all egdes as pairs
    ifstream file(filename);            //Open File

    //Check file actually opens
    if(!file.is_open()){
        cerr << "Error: File Could not open or be found" << filename << endl;
        return vector<pair<int,int>>();           //Return empty vector if file cant be found
    }
    string line;                //Temp variable storing each line
    
    while(getline(file, line)){
        if(line.empty()) continue;      //Skip line if empty
        if(line[0] == '#') continue;    //Skip comment lines

        stringstream ss(line);          //Line into stream (Extract integers)
        int x, y;
        /*
        This will extract the two integers from the txt file
        FromNodeID = x
        ToNodeID = y
        example line:
        x  y
        4 273
        */

        if(ss >> x >> y){
            if(x > y) swap(x,y); //Gets rid of duplicates
            edges.insert({x,y}); //Insert into set(now ignores duplicates)
        }
    }
    file.close();
    return vector<pair<int,int>>(edges.begin(),edges.end());       //Return vector of edges
}