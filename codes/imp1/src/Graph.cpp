#include"Graph.h"
#include"commons.h"
#include<algorithm>

// Init
Graph::Graph()
{
   isGraph=false;
   n=0;
   e=0;
}

// Reads and initializes the graph
void Graph::readGraph(String path)
{
    isGraph = true;
    e = 0;
    ifstream file;
    file.open(path);
    string line;
    register int a,b; 
    while( getline(file,line) )  // for all the lines in the file
    {
        vector<string> v = split(line,',');
        a = atoi(v[0]);
        b = atoi(v[1]);
        n = max( n, max(a,b)+1 );
        e++;
        if( g.find[a] == g.end() )
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
    if( isGraph == false || g.find(i)==g.end() || g[i].find(j)==g[i].end() )
        return false;
    else
        return true;
}

// Returns the structure of the graph
map<int,vector<int> > Graph::getStruct()
{
    return g;
}
