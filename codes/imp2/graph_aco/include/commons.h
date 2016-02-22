/*
    A header to define the common functions used in the project
*/
#ifndef PROJ_COMMONS_H
#define PROJ_COMMONS_H
#include<vector>
#include<string>
using namespace std;

vector<string> split(string str,char delimiter);  // kind of split() statement for the string
typedef pair<int,int> key_ii;                     // for storing key of hashmap


#endif