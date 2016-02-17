// Implements the configNode Structure
#include"configNode.h"
#include<cstring>

// The constructor, non-trivial 
configNode::configNode(Graph* g)
{
    vacant_length = g->cntNodes()/INT_BIT_SZ + 1;
    vacant = new int[vacant_length];
    for( i = 0 ; i<vacant_length ; i++ )    // 0 means an obstacle
        vacant[i]=0;   
    roboPos = -1;   // initially an invalid value for safety
}

// Returns the position of the robot
int configNode::getRobotPos()
{
    return roboPos;
}

// Set the position of the robot
// CAUTION: danger, use this routine with care
void configNode::setRobotPos(int pos)
{
    setVacant(pos);    // at any cost it should be vacany
    roboPos = pos;
}

// Set the node vacant
void configNode::setVacant(int pos)
{
    int i = pos/INT_BIT_SZ;
    int j = pos%INT_BIT_SZ;

    if( (vacant[i] & (1<<j) == 0 ) 
        vacant[i] = ( vacant[i] | (1<<j) );
}

// Mark the position filled
void configNode::unsetVacant(int pos)
{
    int i = pos/INT_BIT_SZ;
    int j = pos%INT_BIT_SZ;

    if( (vacant[i] & (1<<j) != 0 )
        vacant[i] = ( vacant[i] & ~(1<<j) );
}

// Check if the node is vacant
bool configNode::isVacant(int pos)
{
    return (vacant[pos/INT_BIT_SZ] & (1<<j) );
}

// Returns the number of vacant nodes excluding that occupying the robot
int configNode::cntVacant()
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
configNode* configNode::getClone()
{
    configNode* store = configNodeStorage::newConfigNode();
    store->vacant_length = vacant_length;
    store->roboPos  = roboPos;
    store->g_ptr    = g_ptr;
    memcpy( vacant , store->vacant , sizeof(int)*vacant_length );
}

// Move the robot from one pos to another
configNode* configNode::robotMove(int pos1,int pos2)
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
configNode* configNode::obsMove(int pos1,int pos2)
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





