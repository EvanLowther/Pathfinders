#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
/*
parser.cpp file, reads graph dataset file and returns all edges as pairs
Skips empty lines and comment lines
Each line of the dataset shound contain 2 integers(FromNodeID ToNodeID)
*/

vector<pair<int,int>> parseFile(const string& filename){
    vector<pair<int,int>> edges;        //Store all eges as pairs
    ifstream file(filename);            //Open File

    //Check file actually opens
    if(!file.is_open()){
        cerr << "Error: File Could not open or be found" << filename << endl;
        return edges;           //Return empty vector if file cant be found
    }
    string line;                //Temp variable storing each line
    
    while(getline(file,line)){
        if(line.empty()) continue;      //Skip line if empty
        if(line[0] == '#') continue;    //Skip comment lines

        stringstream ss(line);          //Line into stream (Extract integers)
        int x,y;
        /*
        This will extract the two integers from the txt file
        FromNodeID = x
        ToNodeID = y
        example line:
        x  y
        4 273
        */

        if(ss >> x >> y){
            edges.push_back({x,y}); //Add edge to vector
        }
    }
    file.close();
    return edges;       //Return vector of edges
}