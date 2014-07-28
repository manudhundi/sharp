/*************************************************************************
 *  Compilation:  make
 *  Execution:    ./cluster
 * 
 *  Clusters a given set of points with given edge distance
 *
 *  C++ implementation
 *
 *  API to weighted union find class
 *
 *************************************************************************/
#ifndef __UNIONFIND__
#define __UNIONFIND__
class unionFind {
public:
    unionFind (int n);
    ~unionFind();
    /* Check if 2 nodes are connected */
    bool isConnected (int n1, int n2);
    /* Connect 2 nodes */
    void connect (int n1, int n2);
private:    
    int root(int n)
    {
        while (n != id[n]) {
            n = id[n];
        }
        return n;
    }
    int *size;
    int *id;
};
#endif
