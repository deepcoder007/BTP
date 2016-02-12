#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;

vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  
  return internal;
}


int main(int argc,char** argv)
{
    ifstream file;
    file.open("../data/graph.dat");
    string line;
    while( getline(file,line) )
    {
        cout<<line<<endl;
        vector<string> v;
        vector<string>::iterator it;
        v = split(line,',');
        for(it=v.begin();it!=v.end();it++)
            cout<<atoi((*it).c_str())<<endl;
    }

    return 0;
}
