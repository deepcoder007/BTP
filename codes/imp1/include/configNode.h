#ifndef CONFIG_NODE
#define CONFIG_NODE
#include<string>
#include"Graph.h"
#include"constants.h"
#include"commons.h"
#include"configNodeIterator.h"

enum edgeType{NONE,INTERNAL,EXTERNAL};

class configNodeStorage;    // Class declared because used here in configNode

// TODO: configNode should remain constant once they are initialized, otherwise things become complicated

/* 
    Abstract class for the configuration node
*/
class configNode 
{
public:
    configNode(Graph* g,int rPos,vector<int> vPos);     // initialize the confignode acc. to this graph along with the robot pos
    virtual bool isGPU()=0;
    virtual int getRobotPos()=0;        // also tells the partition of the robot
    virtual bool isVacant(int pos)=0;       // returns the vacancy status
    virtual int cntVacant()=0;              // Returns the number of vacant nodes,also tells the layer in which the current node is  

    // Edit configuration -> returns a new configuration after this operation
    // When move is not possible , returns a NULL
//    virtual configNode* getClone()=0;                     // returns the clone 
    virtual configNode* robotMove(int pos1,int pos2)=0;   // moves the robot  
    virtual configNode* obsMove(int post1,int pos2)=0;    // moves the obstacle

    // A key , the key is a 2D object
    virtual key_ii getCode()=0;             // Returns a unique string key for config
    
    // CAUTION: performance critical routine(s)
    virtual bool unCacheMe()=0;               // useful in case of rouge nodes
};

/* Serial implementation of the config node class */
// TODO: Maybe a flag can speed up the cntVacant() subroutine
class configNodeNaive : public configNode
{
private:
    int vacant_length; // length of the array vacant
    int* vacant; 
    int roboPos;
    Graph* g_ptr;      // The pointer to the original graph
    keyii key;         // The key of this configuration
public:
    configNodeNaive(Graph* g,int rPos,vector<int> vPos);     // initialize the confignode acc. to this graph
    ~configNodeNaive();
    bool isGPU();
    int getRobotPos();        // also tells the partition of the robot
    bool isVacant(int pos);       // returns the vacancy status
    int cntVacant();              // Returns the number of vacant nodes,also tells the layer in which the current node is  

    configNode* getClone();                     // returns the clone 
    configNode* robotMove(int pos1,int pos2);   // moves the robot  
    configNode* obsMove(int post1,int pos2);    // moves the obstacle

    key_ii getCode();             // Returns a unique string key for config
    bool unCacheMe()               // useful in case of rouge nodes
};

// TODO: Algo design the GPU version of the configNode to make the other operations GPU-to-GPU



