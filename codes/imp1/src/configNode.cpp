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
// NOTE: passed the storage structure also where this node will init
configNodeNaive::configNodeNaive(Graph* g,int rPos,vector<int> vPos)
{
    vacant_length = g->cntNodes()/INT_BIT_SZ + 1;
    vacant = new int[vacant_length];
    vacCnt = vPos.size();
    for( i = 0 ; i<vacant_length ; i++ )    // 0 means an obstacle
        vacant[i]=0;    // mark everything occupied
    register int i,j,k;

    // The  position of the robot is also vacant 
    i = rPos/INT_BIT_SZ;
    j = rPos%INT_BIT_SZ;
    vacant[i] += (1<<j);

    for( k=0 ; k<vPos.size() ; k++ )
    {
        i = vPos[k]/INT_BIT_SZ;
        j = vPos[k]%INT_BIT_SZ;
        vacant[i] += (1<<j)
    }
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
    return key_ii(roboPos % HASH_KEY1_SZ, cntVacant % HASH_KEY2_SZ );
}

bool configNodeNaive::unCacheMe()
{

}




