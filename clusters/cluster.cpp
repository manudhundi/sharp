/*************************************************************************
 *  Compilation:  make
 *  Execution:    ./cluster
 * 
 *  Clusters a given set of points with given edge distance
 *
 *  C++ implementation
 *
 *  Implements the cluster class  
 *
 *  This is the solution to the assigment 2(part1) of Algorithms2 course
 *  on coursera by Prof.Tim Roughgarden 
 *************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm> 
#include <cstring>
using namespace std;

#include "cluster.h"

/* Compare edgeTs by edge cost */
bool edgeTCmp (edgeT edge1, edgeT edge2)
{
    return (edge1.edgeCost < edge2.edgeCost);
}

cluster::cluster (vector<edgeT> &edgesArray,  unsigned int edgeCount, 
                  unsigned int nodeCount)
{
    edges = new edgeT[edgeCount];
    int edgeSizeTemp = sizeof(edgeT);
    this->edgeCount = edgeCount;
    this->nodeCount = nodeCount;

    /* Copy all edges */
    for (unsigned int i = 0; i < edgeCount; i++) {
        memcpy(&edges[i], &edgesArray.at(i), edgeSizeTemp);
    }

    /* Create a union find obj */
    uf = new unionFind(nodeCount);
}

cluster::~cluster()
{
    delete uf;
    delete [] edges;
}

void cluster::makeClusters(unsigned int numClusters)
{
    unsigned int currClusters = nodeCount;

    /* Sort the edges w.r.t edge cost in ascending order */
    sort(edges, edges + edgeCount, edgeTCmp);
    
    if (numClusters >= nodeCount) {
        return;
    }

    /* Start from smallest edge and start forming clusters */
    for (unsigned int i = 0; i < edgeCount; i++) {
        if (currClusters == numClusters) {
            break;
        }
        if (!(uf->isConnected(edges[i].node1, edges[i].node2))) {
            uf->connect(edges[i].node1, edges[i].node2);
            currClusters--;
        } 
    }
    return;
}

int cluster::getMaxClusterDistance()
{
    /* Return the first edge in the sorted array that is not connected */
    for (unsigned int i = 0; i < edgeCount; i++) {;
        if (!uf->isConnected(edges[i].node1, edges[i].node2)) {
            return edges[i].edgeCost;
        }       
    }
    return 0;
}



