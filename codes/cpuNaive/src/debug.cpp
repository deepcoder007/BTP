#include"debug.h"

void printCONF(Graph* g,CONF conf) {
    int n = g->getNodeCnt();    
    cout<<" CONF :: ";
    cout<<" Robot : "<<conf[0]<<" :: ";
    cout<<" Vacant: ";
    register int i;
    for( i = 1 ; i<=n ; i++ ) 
        if( g->isVacant(conf, i ) ) 
            cout<<i<<",";
    cout<<endl;
}


void printPKEY(Graph* g,PKEY key) {
    cout<<"PKEY : "<<endl;
    cout<<"START : ";
    printCONF(g,key.first);
    cout<<"END   : ";
    printCONF(g,key.second);
}



