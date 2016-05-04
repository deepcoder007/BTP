#include"Graph.h"
#include<string>
#include<fstream>
#include<vector>
#include<set>
#include<sstream>
#include<cassert>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>
using namespace std;

// Function to split the string by the given delimiter
vector<string> split(string str, char delimiter=' ') {
    vector<string> interval;
    stringstream ss(str);
    string tok;
    while( getline(ss, tok, delimiter) ) {
        interval.push_back(tok);
    }
    return interval;
}

/*
    Checks if x and y are adjacent nodes in the underlying graph
*/
bool Graph::gAdjacent(int x,int y) {
    if( grid[x][y]!=0 ) 
        return true;
    else
        return false;
}

/*
    Returns a vector of neighbours of node x in the underlying graph
*/
vector<int> Graph::gNeighbors(int x) {
    vector<int> out;
    register int i;
    for( i=1; i<=n ; i++ )
        if( grid[x][i]!= 0 )
            out.push_back(i);
    return out;
}

/*
    Is position pos is vacant in key
*/
inline bool Graph::isVacant(CONF key, int pos) {
    register int i,j;
    i=pos/INT_SZ; i++;   // the array index
    j=pos%INT_SZ;        // the bitindex
    if( (key[i] & (1<<j)) == 0 )  // if not vacant 
        return false;
    else
        return true;
}

/*
    Set the position vacant in the key and return it
*/
inline CONF Graph::setVac(CONF key,int pos) {
    register int i,j;
    i = pos/INT_SZ ; i++;
    j = pos%INT_SZ;
    key[i] |= (1<<j);
    return key;
}

/*
    Mark the position as filled with obstacle in the node
*/
inline CONF Graph::unsVac(CONF key,int pos) {
    register int i,j;
    i = pos/INT_SZ ; i++;
    j = pos%INT_SZ;
    key[i] &= ~(1<<j);
    return key;
}

/*
    Returns the number of vacant nodes in the configuration 
*/
inline int Graph::cntVac(CONF key) {
#ifdef DEBUG
    assert( isValid(key) );  // checks if this is a valid node
#endif
    register int i;
    int out=0;
    for( i=1 ; i<n ; i++ ) 
        if( isVacant(key, i) )
            out++;
    return (out-1);   // account for the robot also
}

/*
    Check if this is a valid configuration
*/
inline bool Graph::isValid(CONF key) {
    if( isVacant(key, key[0]) )
        return true;
    else 
        return false;
}

/*
    Read the underlying graph from the text file
*/
void Graph::readFromFile(string name) {
   memset(grid, 0, sizeof(grid) );
   string line;
   int a,b;
   cout<<"file : "<<"data/"+name<<endl;
   ifstream infile("data/"+name);
   while( getline(infile, line) ) {
       vector<string> data = split(line,','); 
       a = atoi(data[0].c_str());
       b = atoi(data[1].c_str());
       if( a==b ) 
           continue;
       a++ ; b++ ;
       n = max( n, max(a,b) );
       // for unweighted directed graph;
       grid[a][b] = 1; 
   }

#ifdef DEBUG
    cout<<" Printing the read graph : "<<endl;
    cout<<" Number of nodes  : "<<n<<endl;
    int i,j,k;
    k=0;
    cout<<k<<" | ";
    for( j=1 ; j<=n ; j++ )
        cout<<j<<" | ";
    cout<<endl;
    for( i=1 ; i<=n ; i++ ) {
        cout<<++k<<" | ";
        for( j=1 ; j<=n ; j++ ) {
            cout<<grid[i][j]<<" | ";
        }
        cout<<endl;
    }

#endif
}

/*
    Returns the set of neighbours of the current configuration
    conf -> the configuration for which the neighbors are to be found
    TODO : optimization possible, currently it is brute force approach
*/
set<CONF> Graph::getNeighbour(CONF conf) {
    set<CONF> out;   // to be returned 

    int rPos = conf[0];
    register int i,j;
    CONF tmpConf;      // temp conf
    vector<int> nVector;     // vector to hold neighbors

    // first move the robot 
    nVector = gNeighbors(rPos);
    for( i=0 ; i<nVector.size() ; i++ )  {
        if( isVacant(conf,nVector[i]) ) {
            tmpConf = conf;
            tmpConf[0] = nVector[i];
            out.insert(tmpConf);
        }
    }

    // move the obstacles
    for( i=1 ; i<=n ; i++ ) {
        if( !isVacant(conf,i) ) {
            nVector = gNeighbors(i); 
            for( j=0 ; j<nVector.size() ; j++ ) {
                if( isVacant(conf,j) ) {
                    out.insert( setVac( unsVac(conf, j), i));
                }
            }
        }
    }
    return out;
}

/*
    is conf2 a neighbour of conf1
*/
bool Graph::isNeighbour(CONF conf1,CONF conf2) {

    int vac1 = cntVac(conf1);
    int vac2 = cntVac(conf2);

    if( vac1 != vac2 )
        return false;
    if( conf1[0] != conf2[0] )  // change in position of robot
    {
       // check if rest of the position are same and output accordingly
       bool flag = true;
       for(int i=1; i<KEY_SZ ;i++ ) 
           if( conf1[i]!=conf2[i] )
               flag = false;

       if( flag )  // if same
           return true;
       else
           return false;
    }
    
    // change due to obstacles
    int diff = 0 ;    //count the number of diff. positions
    int p1= -1 , p2=-1 ;  // p1=(source) , p2=(dest)
    bool v1 , v2;
    // check at all the positions
    for( int i=1 ; i<=n ; i++ ) {
       v1 = isVacant(conf1,i);
       v2 = isVacant(conf2,i);
       if( v1 != v2 ) {
           diff++;    // a difference found
           if( v2 ) p1 = i;
           else     p2 = i;
       }
    }

    if( diff!=2 || p1 == -1 || p2 == -1 )
        return false;
    else
        return true;
}

/*
    Returns the pheromone content of the graph
*/
float Graph::getPhero(CONF conf1,CONF conf2) {
    // lock before doing it
    lock_guard<mutex> lck(phero_mutex);
    PKEY key = storage.getKey(conf1, conf2);
    return storage.getValue(key);

}

/*
    Sets the value of pheromone in the graph
*/
bool Graph::setPhero(CONF conf1, CONF conf2, float value) {
    // lock before doing this
    lock_guard<mutex> lck(phero_mutex);
    PKEY key = storage.getKey(conf1,conf2);
    storage.setValue(key,value);
}

/*
    Returns the number of nodes in the graph
*/
int Graph::getNodeCnt() {
    return n;
}

/*
    Mark the node visited
*/
void Graph::markVisit(CONF conf) {
    lock_guard<mutex> lck(tag_mutex);
    visited.insert(conf);
}

/*
    Checks if the node is visited
*/
bool Graph::isVisit(CONF conf) {
    lock_guard<mutex> lck(tag_mutex);
    if( visited.find(conf) == visited.end() )
        return false;
    else
        return true;
}

/*
    Clear the list of visited nodes before start of next ACO iteration
*/
void Graph::clearVisit(CONF conf) {
    lock_guard<mutex> lck(tag_mutex);
    visited.clear();
}

/*
    returns the size of the underlying key-value store
*/
int Graph::containerSize() {
    return storage.getSize();
}

