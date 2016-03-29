#include<string>
#include<vector>
#include<set>
#include"keyValueStore.h"

/*
    NOTE : Graph will have nodes starting from 1, in bitset this factor 
    should be considered to avoid wastage of space.
*/

class Graph
{
private:
    int n;          // Number of nodes in graph
    int grid[30][30];    // to store the adjacency matrix of underlying graph
    keyValueStore storage;   // to store the pheromone content

    // private functions for manipulation of underlying graph
    bool gAdjacent(int x,int y);
    vector<int> gNeighbors(int x);
    
public:
    Graph() ;
    void readFromFile(string name); // read from file in `data` directory
    set<CONF> getNeighbour(CONF conf); // neighbours of this configuration
    float getPhero(CONF conf1,CONF conf2);  // pheromone content of :q
};
