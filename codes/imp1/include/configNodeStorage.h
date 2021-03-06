#ifndef CONFIG_NODE_STORAGE_H
#define CONFIG_NODE_STORAGE_H
#include"configNode.h"
#include"configNodeIterator.h"
#include"constants.h"
#include<vector>

// CAUTION: Very critical implementation
/* 
    A storage structure to hold the configuration nodes
    and also to take care of other operations like hashing
    IMPLEMENTATION:
        Implementation using hashing for performance reason
*/

// This class is just an interface
class configNodeStorage
{
public:
    configNodeStorage();
    virtual bool isGPU()=0;
    virtual configNode* getConfigNode(Graph* g,int rPos,vector<int> vPos)=0;        // returns new/old configuration node corresponding to the given config.
    virtual bool deleteConfigNode(configNode* ptr)=0;       // Deletes this configNode from the structure
    virtual configNodeIterator* getNodeByKey(keyii key)=0;
};

// The serial implementation of the configNodeStorage construct
class configNodeStorageNaive: public configNodeStorage
{
private:
    linkList* dt[HASH_KEY1_SZ][HASH_KEY2_SZ];     // A hash to store the data
public:
    configNodeStorageNaive();
    ~configNodeStorageNaive();
    bool isGPU();
    configNode* getConfigNode(Graph* g,int rPos,vector<int> vPos);    
    bool deleteConfigNode(configNode* ptr);
    configNodeIterator* getNodesByKey(keyii key); // in this case a listNodeIt.
};

// The GPU implementation of the configNodeStorage
// TODO: implement over GPU
class configNodeStorageCUDA: public configNodeStorage
{
public:
    configNodeStorageCUDA();
    bool isGPU();
    configNode* getConfigNode(Graph* g,int rPos,vector<int> vPos);   
    bool deleteConfigNode(configNode* ptr);
    configNodeIterator* getNodesByKey(keyii key);   // TODO: try to convert keyii to a GPU data type
};


#endif
