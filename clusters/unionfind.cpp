/*************************************************************************
 *  Compilation:  make
 *  Execution:    ./cluster
 * 
 *  Clusters a given set of points with given edge distance
 *
 *  C++ implementation
 *
 *  Implements the weighted union find class
 *
 *************************************************************************/
#include "unionFind.h"

unionFind::unionFind(int n)
{
    size = new int[n+1];
    id = new int[n+1];
    /* Initially every node is an independent cluster */
    for (int i = 1; i <= n; i++) {
        size[i] = 1;
        id[i] = i;
    }
}

unionFind::~unionFind()
{
    delete [] size;
    delete [] id;
}

bool unionFind::isConnected(int n1, int n2)
{
    return (root(n1) == root(n2));
}

void unionFind::connect(int n1, int n2)
{
    int root1 = root(n1);
    int root2 = root(n2);
    
    if (root1 == root2)
        return;
        
    /* Connect smaller cluster to a bigger cluster */
    if (size[root1] < size[root2]) {
        size[root2] += size[root1];
        id[root1] = root2;
    } else {
        size[root1] += size[root2];
        id[root2] = root1;
    }
}

