/*
    Graph module will handle the graph operations 
*/
#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<set>
#include<map>

class Graph
{
private:
    int e ; // number of edges
    set<int> nodes;   // the list of nodes, ideally not required
    map<int,vector<int> > g;   // the adjacency list of the graph
    bool isGraph;      // is the data structure having a graph
public:
    Graph();
    void readGraph(String path);    // The only way to initialize the graph
    vector<int> neighbors(int v);   // returns nodes connected from v
    int cntNodes();              
    int cntEdges();
    set<int> getNodes();
    bool isConnected(int i,int j);   // if there is a path from i to j
    map<int,vector<int> > getStruct();   // returns the graph structure
};

#endif 
