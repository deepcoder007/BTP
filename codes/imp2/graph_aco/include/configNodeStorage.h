/*
 * configNodeStorage.h
 *
 *  Created on: 21-Feb-2016
 *      Author: vibhanshu
 */

#ifndef CONFIGNODESTORAGE_H_
#define CONFIGNODESTORAGE_H_

#include"constants.h"
#include"commons.h"
#include<vector>
#include"Graph.h"

// CAUTION: Very critical implementation
/*
    A storage structure to hold the configuration nodes
    and also to take care of other operations like hashing
    IMPLEMENTATION:
        Implementation using hashing for performance reason
*/

class configNode;
class configNodeIterator;
class linkList;

// This class is just an interface
class configNodeStorage
{
public:
//    configNodeStorage(Graph* g);
    virtual ~configNodeStorage();
    virtual bool isGPU()=0;
    virtual configNode* getConfigNode(Graph* g,int rPos,int len,int* vPos)=0;
    virtual bool deleteConfigNode(configNode* ptr)=0;       // Deletes this configNode from the structure
    virtual configNodeIterator* getNodeByKey(key_ii key)=0;
};

// The serial implementation of the configNodeStorage construct
class configNodeStorageNaive: public configNodeStorage
{
private:
	Graph* graph;			// handle of the Graph
    linkList* dt[HASH_KEY1_SZ][HASH_KEY2_SZ];     // A hash to store the data
public:
    configNodeStorageNaive(Graph* g);
    ~configNodeStorageNaive();
    bool isGPU();
    configNode* getConfigNode(Graph* g,int rPos,int len,int* vPos); // preferably use this function
    bool deleteConfigNode(configNode* ptr);
    configNodeIterator* getNodesByKey(key_ii key); // in this case a listNodeIt.
};

// The GPU implementation of the configNodeStorage
// TODO: implement over GPU
/*
class configNodeStorageCUDA: public configNodeStorage
{
public:
    configNodeStorageCUDA();
    bool isGPU();
    configNode* getConfigNode(Graph* g,int rPos,vector<int> vPos);
    bool deleteConfigNode(configNode* ptr);
    configNodeIterator* getNodesByKey(key_ii key);   // TODO: try to convert keyii to a GPU data type
};
*/

#endif /* CONFIGNODESTORAGE_H_ */
