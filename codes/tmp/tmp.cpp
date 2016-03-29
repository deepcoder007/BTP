#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unordered_map>
#include<set>
#include<map>
#include<vector>
using namespace std;


int main() {

    //unordered_map<vector<int>,int> data ;
    map<vector<int>,double> data ;
    int  N;
    cin>>N;
    int i,j;
    for(i=0; i<N; i++) {
        vector<int> v;
        for(j=0;j<5;j++)
            v.push_back(i);
        data[v] = i*1.0;
    }
    cout<<"No. of items in container : "<<data.size()<<endl;
    return 0;
}
