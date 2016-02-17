#ifndef CONFIG_NODE
#define CONFIG_NODE
#include"Graph.h"
#include"constants.h"

enum edgeType{NONE,INTERNAL,EXTERNAL};

class configNodeStorage;    // Class declared because used here in configNode

/* 
    Class for the configuration node
*/
class configNode 
{
private:
    int vacant_length; // length of the array vacant
    int* vacant; 
    int roboPos;
    Graph* g_ptr;      // The pointer to the original graph
public:
    configNode(Graph* g);     // initialize the confignode acc. to this graph
    int getRobotPos();        // also tells the partition of the robot
    void setRobotPos(int pos);    // set the robot at this position 
    void setVacant(int pos);      // mark the position vacant
    void unsetVacant(int pos);    // unset the vacancy 
    bool isVacant(int pos);       // returns the vacancy status
    int cntVacant();              // Returns the number of vacant nodes,also tells the layer in which the current node is  

    // Edit configuration -> returns a new configuration after this operation
    // When move is not possible , returns a NULL
    configNode* getClone();                     // returns the clone 
    configNode* robotMove(int pos1,int pos2);   // moves the robot  
    configNode* obsMove(int post1,int pos2);    // moves the obstacle
    
    // CAUTION: performance critical routine(s)
    bool unCacheMe()               // useful in case of rouge nodes
};




