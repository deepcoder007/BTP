/*
 * Graph.h
 *
 *  Created on: 21-Feb-2016
 *      Author: vibhanshu
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include<vector>
#include<set>
#include<map>
#include<string>
#include<cstring>
#include"commons.h"
#include"constants.h"
using namespace std;


// CAUTION : No node should have a node index of 0

/*
    A graph to store the link information of the original graph used for locomotion
*/
class Graph
{
private:
    int e ; // number of edges
    int n ; // number of nodes
    set<int> nodes;   // the list of nodes, ideally not required
    map<int,set<int> > g;   // the adjacency list of the graph
    map<int,vector<int> > gv;	// the adjancency list with vectors
    bool isGraph;      // is the data structure having a graph
public:
    Graph();
    bool isGPU();
    void readGraph(string path);    // The only way to initialize the graph
    vector<int> neighbors(int v);   // returns nodes connected from v
    int cntNodes();
    int cntEdges();
    set<int> getNodes();
    bool isConnected(int i,int j);   // if there is a path from i to j

    // The 2 routine below this line are useless
    map<int,vector<int> > getStruct();   // returns a simple copy of the graph structure
    map<int,set<int> > getStruct2();	 // it will return the g data clone
};

// TODO: Make the GPU version of this graph, this will make other computations GPU-to-GPU


#endif /* GRAPH_H_ */
