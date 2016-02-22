/*
 * Graph.cpp
 *
 *  Created on: 21-Feb-2016
 *      Author: vibhanshu
 */

#include<algorithm>
#include<fstream>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include"commons.h"
#include"Graph.h"
using namespace std;

// Init
Graph::Graph()
{
   isGraph=false;
   e=0;
   n=0;
}

bool Graph::isGPU()
{
	return false;
}

// Reads and initializes the graph
void Graph::readGraph(std::string path) {
    isGraph = true;
    e = 0;
    ifstream file;
    file.open(path.c_str());
    string line;
    int a,b;
    while( getline(file,line) )  // for all the lines in the file
    {
        vector<string> v = split(line,',');
        a = atoi(v[0].c_str());
        b = atoi(v[1].c_str());
        a++ ; b++ ;   // very important line to remove 0 nodes
        n = max( n, max(a,b) );
        e++;
        if( g.find(a) == g.end() )
            g[a] = vector<int>();
        g[a].push_back(b);
        nodes.insert(a);
        nodes.insert(b);
    }
}

// Returns the list of  edges for the particular graph
vector<int> Graph::neighbors(int v)
{
    if( isGraph == true && g.find(v)!=g.end() )
        return g[v];
    else
        return vector<int>();
}

// Returns the number of nodes in the graph
int Graph::cntNodes()
{
    if( isGraph == true )
        return nodes.size();
    else
        return -1;   // Invalid count
}

// Return the number of edges in the graph
int Graph::cntEdges()
{
    if( isGraph == true )
        return e;
    else
        return -1;      // Invalid count
}

// Get the list of all the nodes , ideally not required
set<int> Graph::getNodes()
{
    return nodes;
}

// If there is a directed path from i to j
bool Graph::isConnected(int i,int j)
{
    if( isGraph == false || g.find(i)==g.end() ||
			find(g[i].begin(),g[i].end(),j)==g[i].end() )
        return false;
    else
        return true;
}

// Returns the structure of the graph
map<int,vector<int> > Graph::getStruct()
{
    return g;
}


