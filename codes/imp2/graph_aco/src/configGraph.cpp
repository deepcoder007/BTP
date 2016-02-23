/*
 * configGraph.cpp
 *
 *  Created on: 21-Feb-2016
 *      Author: vibhanshu
 */

#include"configGraph.h"

configGraph::configGraph(Graph* g,int rPos,int vLen,int* vPos,configNodeStorage* stor)  {
	base = stor->getConfigNode(g,rPos,vLen,vPos);
}

bool configGraph::isGPU() {
	return false;
}

edgeType configGraph::adjacent(configNode* a,configNode* b) {
	// TODO: Write this function
	// first check if robotPos is different
	bool flag=false; // if it becomes true then not rPos
	if( a->getRobotPos() == b->getRobotPos() )
		flag = true;  // robo position not changed
	int len = a->cntNodes()/INT_BIT_SZ;

	int p1,p2;  // mark the position of the nodes where they are different

}

vector<configNode*> configGraph::getNeighbors(configNode* a) {
	// TODO: Write this function


}
