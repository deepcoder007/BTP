#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<sstream>
#include<utility>
#include<chrono>
#include<string>
using namespace std;


int main()
{
    string s = "This is sthe string ";
    stringstream ss(s);
    string tok;
    while( getline(ss,tok,' ') )
        cout<<tok<<endl;
   return 0;
}

