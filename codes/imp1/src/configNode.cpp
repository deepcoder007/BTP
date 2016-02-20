// Implements the configNode Structure
#include"configNode.h"
#include<cstring>
#include<cstdlib>

// The invalid constructor of the base class
configNode::configNode(Graph* g,int rPos,vector<int> vPos)
{
    cerr<<"[configNode] : This object should not be initialized "<<endl;
    exit(-1);
}

// The constructor, non-trivial 
// NOTE: This constructor should only be called by [configNodeStorage]
// TODO: rewrite this function
configNodeNaive::configNodeNaive(Graph* g,int rPos,vector<int> vPos)
{
    vacant_length = g->cntNodes()/INT_BIT_SZ + 1;
    vacant = new int[vacant_length];
    for( i = 0 ; i<vacant_length ; i++ )    // 0 means an obstacle
        vacant[i]=0;   
    roboPos = -1;   // initially an invalid value for safety
}

// For permanently removing the configNode
configNodeNaive::~configNodeNaive()
{
    g_ptr = 0;
    delete[] vacant;
}


// Returns the position of the robot
int configNodeNaive::getRobotPos()
{
    return roboPos;
}

// Set the node vacant
void configNodeNaive::setVacant(int pos)
{
    int i = pos/INT_BIT_SZ;
    int j = pos%INT_BIT_SZ;

    if( (vacant[i] & (1<<j) == 0 ) 
        vacant[i] = ( vacant[i] | (1<<j) );
}

// Mark the position filled
void configNodeNaive::unsetVacant(int pos)
{
    int i = pos/INT_BIT_SZ;
    int j = pos%INT_BIT_SZ;

    if( (vacant[i] & (1<<j) != 0 )
        vacant[i] = ( vacant[i] & ~(1<<j) );
}

// Check if the node is vacant
bool configNodeNaive::isVacant(int pos)
{
    return (vacant[pos/INT_BIT_SZ] & (1<<(pos%INT_BIT_SZ)) );
}

// Returns the number of vacant nodes excluding that occupying the robot
int configNodeNaive::cntVacant()
{
    int cnt = 0;
    int i,j;
    for( i=0 ; i<vacant_length ; i++ )
        for( j=0; j<INT_BIT_SZ ; j++ )
            if( (vacant[i] & (1<<j)) )
                cnt++;
    return cnt;
}

// Returns the clone of the current node-> used for movement operation
// TODO : The method is still not complete, REDO it
configNode* configNodeNaive::getClone()
{
    configNode* store = configNodeStorage::newConfigNode();
    store->vacant_length = vacant_length;
    store->roboPos  = roboPos;
    store->g_ptr    = g_ptr;
    memcpy( vacant , store->vacant , sizeof(int)*vacant_length );
}

// Move the robot from one pos to another
configNode* configNodeNaive::robotMove(int pos1,int pos2)
{
    if( g_ptr->isConnected(pos1,pos2) && isVacant(pos2) ) {
        configNode* store = getClone();   // returns the clone of curr node
        store->setRobotPos(pos2);
        return store;
    } else {
        return NULL;
    }
}

// Move the obstacle from one pos to other
configNode* configNodeNaive::obsMove(int pos1,int pos2)
{
    if( g_ptr->isConnected(pos1,pos2) && isVacant(pos2) {
        configNode* store = getClone();
        store->unsetVacant(pos2);
        store->setVacant(pos1);
        return store;
    } else {
        return NULL;
    }
}

// Returns the 2D key of the current node
key_ii configNodeNaive::getCode()
{
    return key_ii(roboPos % 10, cntVacant % 100 );
}

bool configNodeNaive::unCacheMe()
{

}




