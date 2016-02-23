#ifndef CONFIGNODE_H
#define CONFIGNODE_H

#include<string>
#include"constants.h"
#include"commons.h"
using namespace std;

class configNodeStorage;
class Graph;

/*
    Abstract class for the configuration node
*/
class configNode
{
public:
    virtual ~configNode();
    virtual bool isGPU()=0;
    virtual int getRobotPos()=0;        // also tells the partition of the robot
    virtual bool isVacant(int pos)=0;       // returns the vacancy status
    virtual int cntVacant()=0;              // Returns the number of vacant nodes,also tells the layer in which the current node is
    virtual int cntNodes()=0;

    // Edit configuration -> returns a new configuration after this operation
    // When move is not possible , returns a NULL
    virtual configNode* robotMove(int pos2)=0;   // moves the robot
    virtual configNode* obsMove(int pos1,int pos2)=0;    // moves the obstacle

    // A key , the key is a 2D object
    virtual key_ii getCode()=0;             // Returns a unique string key for config
};

/* Serial implementation of the config node class */
class configNodeNaive : public configNode
{
private:
    int vacant_length; // length of the array vacant
    int* vacant;
    int roboPos;
    Graph* g_ptr;      // The pointer to the original graph
    key_ii key;         // The key of this configuration
    int vacCnt;
    configNodeStorage* storage;  // The storage struct used
public:
    configNodeNaive(Graph* g,int rPos,int vLen,int* vPos,configNodeStorage* stor);     // initialize the confignode acc. to this graph
    ~configNodeNaive();
    bool isGPU();
    int getRobotPos();        // also tells the partition of the robot
    bool isVacant(int pos);       // returns the vacancy status
    int cntVacant();              // Returns the number of vacant nodes,also tells the layer in which the current node is
    int cntNodes();    // CAUTION: Assumption that nodes in seq [1,..,n]

    configNode* robotMove(int pos2);   // moves the robot
    configNode* obsMove(int pos1,int pos2);    // moves the obstacle

    key_ii getCode();             // Returns a unique string key for config
};

// TODO: Algo design the GPU version of the configNode to make the other operations GPU-to-GPU

#endif
