#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unordered_map>
#include<map>
#include<algorithm>
#include<array>
#include<utility>
#include<thread>
#include<chrono>
#include<unistd.h>
//#include"keyValueStore.h"
using namespace std;

map<pair<array<int,2>,array<int,2> >, float> phero;   // the pheromone content

void f() {
    register int rt1,rt2;
    while(1)  {
        usleep(10000);
        rt2=phero.size();
        cout<<"Size : "<<rt2<<endl;
        if( rt1 == rt2 )
            break;
        rt1 = rt2;
    }
}


int main() {

    //unordered_map<pair<array<int,2>,array<int,2> >, float> phero;   // the pheromone content

    int N = 5;
    cout<<"Enter the value of N: ";
    cin>>N;
    register int i,j;
    thread t1(f);
    for( i=0 ; i<N ; i++ )
        for( j=0 ; j<N ; j++ )
            phero[make_pair(array<int,2>{{i,i}},array<int,2>{{j,j}})] = i*j;

    cout<<" No. of items : "<<phero.size()<<" -> base : "<<N*N<<endl;
    t1.join();
    int tt;
    cin>>tt;
    return 0;
}


