#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<sstream>
#include<utility>
#include<chrono>
using namespace std;

#define CON 10000


int main()
{
    auto start=chrono::high_resolution_clock::now();
    // ---------------------------------------------------------------------------
    int i;
    vector<int> a;
    for(i=0;i<CON;i++)
        a.push_back(i);
    // ---------------------------------------------------------------------------
    auto elapsed = chrono::high_resolution_clock::now() - start;
    long long dur = chrono::duration_cast<chrono::microseconds>(elapsed).count();
    cout<<endl<<endl<<"Total time : "<<dur<<endl;
    cout<<"[Done]"<<endl<<endl;
   
    start=chrono::high_resolution_clock::now();
    // ---------------------------------------------------------------------------
    int *b=new int[CON];
    for(i=0;i<CON;i++)
        b[i]=1;
    // ---------------------------------------------------------------------------
    elapsed = chrono::high_resolution_clock::now() - start;
    dur = chrono::duration_cast<chrono::microseconds>(elapsed).count();
    cout<<endl<<endl<<"Total time : "<<dur<<endl;
    cout<<"[Done]"<<endl;
    return 0;
   return 0;
}

