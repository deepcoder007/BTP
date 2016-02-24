/*
 * configGraph.cpp
 *
 *  Created on: 21-Feb-2016
 *      Author: vibhanshu
 */

#include<cmath>
#include"Graph.h"
#include"commons.h"
#include"constants.h"
#include"configGraph.h"
#include"configNode.h"
#include"configNodeStorage.h"
#include"configNodeIterator.h"

configGraph::configGraph(Graph* g,int rPos,int vLen,int* vPos,configNodeStorage* stor)  {
	base = stor->getConfigNode(g,rPos,vLen,vPos);
}

bool configGraph::isGPU() {
	return false;
}

edgeType configGraph::adjacent(configNode* a,configNode* b) {

	if( a->cntVacant() == b->cntVacant() )
	{
		// first check if robotPos is different
		bool flag=false; // if it becomes true then rPos is not changed
		if( a->getRobotPos() == b->getRobotPos() )
			flag = true;  // robo position not changed
		int nodeCount = a->cntNodes();
		// now verify for each node
		int p1 = -1 ,p2 = -1;  // mark the position of the nodes where they are different
		int i;
		bool v1,v2;
		for( i=1 ; i<=nodeCount ; i++ )
		{
			v1 = a->isVacant(i);
			v2 = b->isVacant(i);
			if( v1 != v2 )
				if( v1 == false )  // a has obstacle at position i
					p1 = i ;
				else if( v2 == false )  // b has obstacle at position i
					p2 = i ;
		}
		if( p1 == -1 && p2 == -1 && flag == true )   // they are same node
			return NONE;
	} else {	  // check the case if the edge is from one layer to another

		// Check if are adjacent nodes in different layer, if not no edge is possible
		// NOTE: The link will always be from node with higher vacant nodes to lower vacant nodes.
		if( a->getRobotPos() != b->getRobotPos() || (a->cntVacant()-b->cntVacant())>1 )
			return NONE;

		int cntr=0;   		// count how many pos are different
		int p1 = -1 ; 		// the location where configNode are different
		int nodeCount = a->cntNodes();
		int i;
		for( i=1 ; i<=nodeCount ; i++ ) {
			if( a->isVacant(i) != b->isVacant(i) ) {   // if position i is dissimilar in the 2 nodes
				p1 = i;		  // the node where there is a change
				cntr ++; 	  // counter for the number of changes
			}
		}
		if( cntr>1 )  // diff at more then 1 position
			return NONE;
		else
			return EXTERNAL;
	}
}

vector<configNode*> configGraph::getNeighbors(configNode* a) {
	// TODO: Write this function


}
