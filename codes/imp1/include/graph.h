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
    int n ; // number of nodes
    int e ; // number of edges
    map<int,vector<int> > g;   // the adjacency list of the graph
    bool isGraph;      // is the data structure having a graph
public:
    Graph();
    void readGraph(String path);
    vector<int> getEdges(int v);   // returns nodes connected to v
    int cntNodes();              
    int cntEdges();
    bool isConnected(int i,int j);   // if there is a path from i to j
};

#endif 
