/**
    Used to generate graph for further manipulation
    The graph will be stored in file  *graph.txt*
*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
    system("octave --eval \"k=int32(kronecker_generator(15,100));k=k';dlmwrite('../data/exp_graph.txt',k);\"");
    
    return 0;

}
