#ifndef CONFIG_GRAPH_H
#define CONFIG_GRAPH_H
#include"configNode.h"  // for the configNode data structure
#include<vector>

class configGraph
{
private:

public:
    configGraph();
    bool isGPU();
    edgeType adjacent(configNode* a,configNode* b);   // tells if a->b is a valid edge
    vector<configNode*> getNeighbors(configNode* a);   // returns the list of neighbours of a


}








#endif
