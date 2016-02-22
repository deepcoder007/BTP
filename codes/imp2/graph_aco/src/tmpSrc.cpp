/*
 * tmpSrc.cpp
 *
 *  Created on: 22-Feb-2016
 *      Author: vibhanshu
 */
// This source file is just used for experimental demo of the project.
/*
 * I am using this file for testing purpose until we have a clear testing
 * container like googletest or otherwise.
 */

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<string>
#include<set>
#include"commons.h"
#include"Graph.h"
#include"configNodeIterator.h"
#include"configNode.h"
#include"configNodeStorage.h"
using namespace std;

class configNodeNaive;

int main()
{
//	genGraph(2,4);
	cout<<"Starting program"<<endl;
	Graph g;
	g.readGraph("data/graph.dat");
	configNodeStorageNaive stor(&g);  // the storage struct

	int conf;   // we need only 1 int for this sample config
	conf += (1<<0);
	conf += (1<<1);
	conf += (1<<2);
	conf += (1<<3);
//	configNode* tmpNode = new configNodeNaive(&g,0,1,&conf,&stor);
	configNode* tmp2;

	tmp2 = stor.getConfigNode(&g,1,1,&conf);
	tmp2 = stor.getConfigNode(&g,1,1,&conf);
	tmp2 = stor.getConfigNode(&g,1,1,&conf);
	tmp2 = stor.getConfigNode(&g,1,1,&conf);
	tmp2 = stor.getConfigNode(&g,1,1,&conf);
	tmp2 = stor.getConfigNode(&g,1,1,&conf);
	cout<<"Number of stored : "<<stor.getCount()<<endl;

//	delete tmpNode;
	return 0;
}




