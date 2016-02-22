/*
 * configNode.cpp
 *
 *  Created on: 21-Feb-2016
 *      Author: vibhanshu
 */
// Implements the configNode Structure
#include"configNode.h"
#include"configNodeStorage.h"
#include"configNodeIterator.h"
#include"Graph.h"
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

/*
 * The constructor for the abstract class
 * Initializing this will throw an error
 */
/*
configNode::configNode(Graph* g,int rPos,int vLen,int* vPos,configNodeStorage* stor)
{
//    cout<<"[configNode] : This object should not be initialized "<<std::endl;
//    exit(-1);
}
*/

configNode::~configNode()
{
	// TODO : Trivial code
}

/*
 * Constructor for configNodeNaive which is CPU version
 * ARGUMENTS:
 * 		1. g		: The underlying graph
 * 		2. rPos		: The position of the robot
 * 		3. vLen		: The length of vPos array
 * 		4. vPos		: The BITset to store the vacant positions
 */
configNodeNaive::configNodeNaive(Graph* g,int rPos,int vLen,int* vPos,configNodeStorage* stor)
{
    vacant_length = vLen;
    vacant = new int[vacant_length];
    roboPos = rPos;
    g_ptr = g;
    storage = stor;
    memcpy(vacant,vPos,sizeof(int)*vacant_length);

    key.first= rPos % HASH_KEY1_SZ;
    key.second = 0;
    vacCnt = 0;
    // simply copy the array
    int i,j;
    for(  i = 0 ; i<vacant_length ; i++ )    // 0 means an obstacle
    	for( j=0 ; j<INT_BIT_SZ; j++ )
    		if( (vacant[i] & (1<<j)) != 0  ) {
    			vacCnt++;
    			key.second += (i*INT_BIT_SZ+j) ;
    		}
    key.second %= HASH_KEY2_SZ;
}

// For permanently removing the configNode
configNodeNaive::~configNodeNaive()
{
    g_ptr = NULL;
    delete[] vacant;
    storage = NULL;
}

bool configNodeNaive::isGPU() {
	return false;
}

// Returns the position of the robot
int configNodeNaive::getRobotPos()
{
    return roboPos;
}

// Check if the node is vacant
bool configNodeNaive::isVacant(int pos)
{
    return (vacant[pos/INT_BIT_SZ] & (1<<(pos%INT_BIT_SZ)) );
}

// Returns the number of vacant nodes excluding that occupying the robot
int configNodeNaive::cntVacant()
{
    return vacCnt;
}

// Returns the number of nodes in the underlying graph
int configNodeNaive::cntNodes() {
	return g_ptr->cntNodes();
}

/*
 * Move the robot from 'roboPos' to new position 'pos2'
 * If this new position is not possible return NULL
 * The allocation of space for configNode structure is done
 * internally.
 */
configNode* configNodeNaive::robotMove(int pos2)
{
    if( g_ptr->isConnected(roboPos,pos2) && isVacant(pos2) ) {
    	int* tmpArr=new int[vacant_length];
    	memcpy(tmpArr,vacant,sizeof(int)*vacant_length);
    	configNode* tmpNode = storage->getConfigNode(g_ptr,pos2,vacant_length,vacant);
		delete[] tmpArr;
    	return tmpNode;
    } else {
        return NULL;
    }
}

/*
 * Return obstacle on 'pos1' to 'pos2'
 * if this is not possible then return NULL
 */
configNode* configNodeNaive::obsMove(int pos1,int pos2)
{
	// check if (pos1->pos2) , if pos2 is vacant and pos1
	// is filled simultaneously
    if( g_ptr->isConnected(pos1,pos2) &&
    		isVacant(pos2) && !isVacant(pos1) )
    {
    	int* tmpArr=new int[vacant_length];
    	memcpy(tmpArr,vacant,sizeof(int)*vacant_length);
    	int i,j;
    	i = pos1 / INT_BIT_SZ;
    	j = pos1 % INT_BIT_SZ;
    	tmpArr[i] = (tmpArr[i] & ~(1<<j));
    	i = pos2 / INT_BIT_SZ;
    	j = pos2 % INT_BIT_SZ;
    	tmpArr[i] = (tmpArr[i] | (1<<j));
    	configNode* tmpNode = storage->getConfigNode(g_ptr,roboPos,vacant_length,tmpArr);
    	delete[] tmpArr;
    	return tmpNode;
    } else {
        return NULL;
    }
}

// Returns the 2D key of the current node
key_ii configNodeNaive::getCode()
{
	return this->key;
}