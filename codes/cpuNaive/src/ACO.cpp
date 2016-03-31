#include"keyValueStore.h"
#include"Graph.h"
#include"ACO.h"
#include<cstdlib>
using namespace std;


/*
    For the iteration of the current Ant thread
*/
void Ant::iterate() {
    n = g->getNodeCnt(); 
    
    int start = rand()%n+1;   // randomly choose the ant configuration
