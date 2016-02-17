#ifndef CONFIG_NODE_STORAGE_H
#define CONFIG_NODE_STORAGE_H
#include"configNode.h"

// A link list data structure for storing configNode
class configLinkList
{


}

// CAUTION: Very critical implementation
/* 
    A storage structure to hold the configuration nodes
    and also to take care of other operations like hashing
    IMPLEMENTATION:
        Implementation using hashing for performance reason
*/
class configNodeStorage
{
private:
    configLinkList list[CONFIG_NODE_BUCKETS];
public:
    configNodeStorage();
    static configNode* newConfigNode();   // returns space for new config 


};

#endif
