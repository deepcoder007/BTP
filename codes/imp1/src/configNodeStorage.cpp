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
            delete dt[i][j];
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
    linkListIterator tmpList(dt[key.first][key.second]);  // initialize 
    configNode* tmpNode;
    bool flag;    // for testing the similarily
    while( tmpList.hasNext() )
    {
        flag = false;       // if true , then dissimilar
        tmpNode = tmpList.next();
        // now check if tmpNode is having the same conf
        if( rPos !=  tmpNode->getRobotPos() )
            flag = true;
        else if ( vPos.size() != tmpNode->cntVacant() ) 
            flag = true;
        else {
            for( i = 0 ; i<vPos.size() ; i++ )
                if ( tmpNode->isVacant(vPos[i]) == false )
                    flag = true;
        if( flag == false )    // i.e. node found
            return tmpNode;
    }

    // new Node needs to be initialized and update the hash DS
    tmpNode = (configNode*)(new configNodeNaive(g,rPos,vPos));
    dt[key.first][key.second]->insertNode(tmpNode) ;
    return tmpNode;  // return the newly initialized node

}

bool configNodeStorageNaive::deleteConfigNode(configNode* ptr)
{




