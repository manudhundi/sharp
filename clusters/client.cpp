/*************************************************************************
 *  Compilation:  make
 *  Execution:    ./cluster
 * 
 *  Clusters a given set of points with given edge distance
 *
 *  C++ implementation
 *
 *  Points and edge lengths are read from a file in the format
 *  [number_of_nodes]
 *  [edge 1 node 1] [edge 1 node 2] [edge 1 cost]
 *  [edge 2 node 1] [edge 2 node 2] [edge 2 cost]
 *
 *  This is client file calling the job scheduling class  
 *
 *  This is the solution to the assigment 2(part1) of Algorithms2 course
 *  on coursera by Prof.Tim Roughgarden 
 *************************************************************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

#include "cluster.h"
using namespace std;
#define INPUT_FILE "clustering1.txt"

int main(void)
{
    string word;
    int numNodes = 0, numEdges = 0;
    vector<edgeT> edges;
    edgeT currEdge = {0};
    
    /* Read data from file */
    ifstream file(INPUT_FILE);
    
    if (!file.is_open()) {
        cout << "File could not be opened" << endl;
        exit(1);
    }
       
    
    if (file >> word) {
        numNodes = atoi(word.c_str());
    } 
    while (file >> word) {
        currEdge.node1 =  atoi(word.c_str());
        file >> word; /* assumes that file is always in expected format */
        currEdge.node2 =  atoi(word.c_str());
        file >> word; /* assumes that file is always in expected format */
        currEdge.edgeCost =  atoi(word.c_str());
        edges.push_back(currEdge);
    }
    
    numEdges = edges.size();
    cluster clusterObj(edges, numEdges, numNodes);
    /* Make k clusters (k is 4 below) */
    clusterObj.makeClusters(4);
    cout << clusterObj.getMaxClusterDistance() << endl;
    
    cout << "done" << endl;
    return 0;
}
