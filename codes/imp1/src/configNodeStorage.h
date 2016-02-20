/*
    Implementation of the configuration node storage structures
*/
#include"configNodeStorage.h"

/*
    The function that should not be invoked
*/
configNodeStorage::configNodeStorage()
{
    cout<<"[configNodeStorage]: This class should not be initialized"<<endl;
    exit(-1);
}

configNodeStorageNaive::configNodeStorageNaive()
{
    int i,j;
    for( i=0 ; i<HASH_KEY1_SZ ; i++ )
        for( j=0 ; j<HASH_KEY2_SZ ; j++ )
            dt[i][j]=new linkList;
}

configNodeStorageNaive::~configNodeStorageNaive()
{
    int i,j;
    for( i=0 ; i<HASH_KEY1_SZ ; i++ )
        for( j=0 ; j<HASH_KEY2_SZ ; j++ )
            delete[i][j];
}

bool configNodeStorageNaive::isGPU()
{
    return false;
}

configNode* configNodeStorageNaive::getConfigNode(Graph* g,int rPos,vector<int> vPos)
{
    int vPosSum = 0;
    int i,sz=vPos.size();
    for( i=0 ; i<sz ; i++ )
        vPosSum += vPos[i];
    keyii key(rPos%HASH_KEY1_SZ,vPosSum%HASH_KEY2_SZ);
    linkList* tmpLst = dt[key.first][key.second];

}




