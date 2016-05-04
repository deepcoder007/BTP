#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include<fstream>
#include<sstream>
#include"keyValueStore.h"
#include"Graph.h"
#include"debug.h"
using namespace std;

// TEST: Generate the graph and print the result
void test1() {
    cout<<"[START] : test1 "<<endl;
   chdir("src");
   char buf[200];
   sprintf(buf,"octave --eval \"k=int32(kronecker_generator(%d,%d));k=k';dlmwrite('../data/graph.dat',k);\"",4,5);
    system(buf);
    chdir("..");

    cout<<" Now reading and printing the graph file : "<<endl;
    ifstream infile("data/graph.dat");
    string line;
    while( getline(infile, line) ) {
        cout<<line<<endl;
    }
    infile.close();
    cout<<"[DONE] : test1"<<endl;
}


// TEST: test if graph can read the graph file
void test2()
{
    cout<<"[START]: test2"<<endl;

    Graph g;
    g.readFromFile("graph.dat");

    CONF conf;
    conf[0]=11;
    conf[1]=~0;
    cout<<"Is valid : "<<g.isValid(conf)<<endl;
    printCONF(&g,conf);

    auto neighbour = g.getNeighbour(conf);
    for( auto &x: neighbour )
        printCONF(&g,x);

    cout<<"[END] : test2 "<<endl;
}


// TEST: a long random walk across the graph and initialize the pheromone along the way
void test3()
{
    cout<<"[START]: test3"<<endl;

    Graph g;
    g.readFromFile("graph.dat");

    CONF conf;
    conf[0]=54;
    conf[1]=~0;
    conf[2]=~0;
    conf[3]=~0;

    // place obstacles on some of the nodes
    for( int i=10; i<=30 ; i++ )
        conf = g.unsVac(conf, i);

    cout<<"Is valid : "<<g.isValid(conf)<<endl;
    printCONF(&g,conf);

    set<CONF> neighbour1, neighbour2, neighbour3;
    neighbour1 = g.getNeighbour(conf);
    
    neighbour1.insert(conf);
    while(1) {
        neighbour2 = set<CONF>();
        for( auto &x: neighbour1 ) {
            neighbour3 = g.getNeighbour(x);
            neighbour2.insert(neighbour3.begin(), neighbour3.end() );  // add it to next layer 
            for( auto &y: neighbour3 ) {
     //           printCONF(&g,y);
                g.setPhero(x,y,1.0);
            }
        }
        neighbour1 = neighbour2;
        cout<<" CONTAINER SIZE : "<<g.containerSize()<<endl;
    }

    cout<<"[END] : test3 "<<endl;
}

void writeCONFtoFile(FILE* ptr, Graph* g, CONF conf) {
   int n = g->getNodeCnt(); 
   fprintf(ptr,"%d",conf[0]);
   for(register int i=1 ; i<=n ; i++ ) 
       if( g->isVacant(conf, i) )
           fprintf(ptr,",%d",i);
   fprintf(ptr,"\n");
   fflush(ptr);
}


// TEST: TEST3 + coloring of nodes with obstacles and robot
void test4()
{
    cout<<"[START]: test4"<<endl;

    Graph g;
    g.readFromFile("graph.dat");
    FILE* ptr = fopen("data/conf.dat","w");

    CONF conf;
    conf[0]=4;
    conf[1]=~0;
    conf[2]=~0;
    conf[3]=~0;

    // place obstacles on some of the nodes
    for( int i=10; i<=30 ; i++ )
        conf = g.unsVac(conf, i);

    cout<<"Is valid : "<<g.isValid(conf)<<endl;
    printCONF(&g,conf);
    writeCONFtoFile(ptr,&g,conf);

    set<CONF> neighbour1, neighbour2, neighbour3;
    neighbour1 = g.getNeighbour(conf);
    
    neighbour1.insert(conf);
    while(1) {
        neighbour2 = set<CONF>();
        for( auto &x: neighbour1 ) {
            writeCONFtoFile(ptr,&g,x);
            neighbour3 = g.getNeighbour(x);
            neighbour2.insert(neighbour3.begin(), neighbour3.end() );  
            for( auto &y: neighbour3 ) {
                g.setPhero(x,y,1.0);
            }
        }
        neighbour1 = neighbour2;
    }
    fclose(ptr);

    cout<<"[END] : test3 "<<endl;
}


int main() {
    cout<<"-----------------------------------------"<<endl;
    cout<<"     Start the regression testing        "<<endl;
    cout<<"-----------------------------------------"<<endl;

    char dir[200];
    getcwd(dir,sizeof(dir));
    cout<<"Current directory : "<<dir<<endl;

    // Sequence of test cases
//    test1();
//    test2();
//    test3();
    test4();

    cout<<"-----------------------------------------"<<endl;
    cout<<"     Done with regression testing        "<<endl;
    cout<<"-----------------------------------------"<<endl;
    return 0;
}
