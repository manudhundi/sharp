/*************************************************************************
 *  Compilation:  make
 *  Execution:    ./cluster
 * 
 *  Clusters a given set of points with given edge distance
 *
 *  C++ implementation
 *
 *  API of the cluster class  
 *************************************************************************/
#include "unionFind.h"
#include <vector>
using namespace std;

typedef struct edge {
    unsigned int node1;
    unsigned int node2;
    unsigned int edgeCost;
} edgeT;

class cluster {
public:
    cluster (vector<edgeT> &edges, unsigned int edgeCount,
             unsigned int nodeCount);
    ~cluster();
    void makeClusters(unsigned int numClusters);
    int getMaxClusterDistance();
private:
    edgeT* edges; /* array of edges in the graph */
    unsigned int edgeCount;
    unsigned int nodeCount;
    unionFind* uf;
};
