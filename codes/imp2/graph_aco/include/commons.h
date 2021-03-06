/*
    A header to define the common functions used in the project
*/
#ifndef PROJ_COMMONS_H
#define PROJ_COMMONS_H
#include<vector>
#include<string>

std::vector<std::string> split(std::string str,char delimiter);  // kind of split() statement for the string
typedef std::pair<int,int> key_ii;                     // for storing key of hashmap
int genGraph(int x,int y);
enum edgeType{NONE,INTERNAL,EXTERNAL};

#endif
