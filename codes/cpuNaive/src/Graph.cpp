#include"../include/Graph.h"
#include<string>
#include<fstream>
#include<vector>
#include<sstream>

vector<string> split(string str, char delimiter) {
    vector<string> interval;
    stringstream ss(str);
    string tok;
    while( getline(ss, tok, delimiter) ) {
        interval.push_back(tok);
    }
    return interval;
}

bool Graph::gAdjacent(int x,int y) {
    if( grid[x][y]!=0 ) 
        return true;
    else
        return false;
}

vector<int> Graph::gNeighbors(int x) {
    vector<int> out;
    register int i;
    for( i=1; i<=n ; i++ )
        if( grid[x][i]!= 0 )
            out.push_back(i);
    return out;
}

void Graph::readFromFile(string name) {
   memset(grid, 0, sizeof(grid) );
   string line;
   int a,b;
   ifstream infile("../data/"+name.c_str());
   while( getline(infile, line) ) {
       vector<string> data = split(line,','); 
       a = data[0].c_str();
       b = data[1].c_str();
       if( a==b ) 
           continue;
       a++ ; b++ ;
       n = max( n, max(a,b) );
       // for unweighted directed graph;
       grid[a][b] = 1; 
   }
}

set<CONF> Graph::getNeighbour(CONF conf) {



}

float Graph::getPhero(CONF conf1,CONF conf2) {
    PKEY key = storage.getKey(conf1, conf2);
    return storage.getValue(key);
}

