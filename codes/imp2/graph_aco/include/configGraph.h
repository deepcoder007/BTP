/*
 * configGraph.h
 *
 *  Created on: 21-Feb-2016
 *      Author: vibhanshu
 */

#ifndef CONFIGGRAPH_H_
#define CONFIGGRAPH_H_

#include"configNode.h"  // for the configNode data structure
#include"commons.h"
#include"constants.h"
#include<vector>
#include<set>

class configGraph
{
public:
    configGraph();
    bool isGPU();
    edgeType adjacent(configNode* a,configNode* b);   // tells if a->b is a valid edge
    set<configNode*> getNeighbors(configNode* a);   // returns the list of neighbours of a
};


#endif /* CONFIGGRAPH_H_ */
