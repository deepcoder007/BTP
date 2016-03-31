#ifndef ACO_H
#define ACO_H
#include"keyValueStore.h"
#include"Graph.h"
#include<vector>
#include<set>


// This class will run the ACO algorithm in its thread
class Ant
{
private:
   set<CONF> tabu_list;     // the tabu list for this ant 
   Graph* g;
public:
   void iterate();  // to execute 1 step of ACO
};

#endif
