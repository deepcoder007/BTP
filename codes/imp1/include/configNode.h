#ifndef CONFIG_NODE
#define CONFIG_NODE

/* 
    A class for operations on the higher order graph
*/
class configNode 
{
private:
    long key;  // generated key of this config node
    int k;     // the number of vacant spots
    int v;     // the node with the robot, also to find the partition
    int n;     // the number of total nodes in the connfiguration
    int* vacant;  // an bitset array to hold the vacancy of the robots
public:
    configNode(int ky); 
    int getRobotPos();
    void setRobotPos(int pos);    // set the robot at this position 
    void setTotalNodes(int cnt);
    void setVacant(int pos);       // mark the position vacant
    void unsetVacant(int pos);      // unset the vacancy 
}


class configNodeFactory
{
private:
    int n;          // the number of nodes
    int nxtKey=0;
public:
    configNodeFactory(int cnt);
    int getNxtKey();
    int* getNextStorage();
    configNode* get




