/*
    Graph module will handle the graph operations 
*/
#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<set>
#include<map>

/*
    A graph to store the link information of the original graph used for locomotion
*/
class Graph
{
private:
    int e ; // number of edges
    set<int> nodes;   // the list of nodes, ideally not required
    map<int,vector<int> > g;   // the adjacency list of the graph
    bool isGraph;      // is the data structure having a graph
public:
    Graph();
    bool isGPU();
    void readGraph(String path);    // The only way to initialize the graph
    vector<int> neighbors(int v);   // returns nodes connected from v
    int cntNodes();              
    int cntEdges();
    set<int> getNodes();
    bool isConnected(int i,int j);   // if there is a path from i to j
    map<int,vector<int> > getStruct();   // returns a simple copy of the graph structure
};

// TODO: Make the GPU version of this graph, this will make other computations GPU-to-GPU

#endif 
