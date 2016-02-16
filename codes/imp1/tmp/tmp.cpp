#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;



int main(int argc,char** argv)
{
    int i=0,j=0,k=0;
    for(i=0;i<32;i++)
    {
        j=(1<<i);
        cout<<j<<endl;
    }
    return 0;
}
