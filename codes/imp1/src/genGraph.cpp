/**
    Used to generate graph for further manipulation
    The graph will be stored in file  *graph.txt*
*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main(int argc,char** argv)
{
    if( argc < 3 )    // i.e. not enough arguments 
    {
       cout<<" Not enough arguments found"<<endl;
       cout<<" There should be exactly 2 arguments i.e. ( log(No. of nodes) , degree of each node ) "<<endl;
       exit(-1);
    }
    char buf[100];
    sprintf(buf,"octave --eval \"k=int32(kronecker_generator(%d,%d));k=k';dlmwrite('../data/graph.dat',k);\"",atoi(argv[1]),atoi(argv[2]));

#ifdef DEBUG
    cout<<"[DEBUG]: Graph build "<<endl;
    cout<<"       : No. of nodes = 2^"<<atoi(argv[1])<<endl;
    cout<<"       : Degree of each node =  "<<atoi(argv[2])<<endl;
#endif

    system(buf);
    return 0;
}
