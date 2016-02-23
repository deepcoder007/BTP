/*
 * commons.cpp
 *
 *  Created on: 21-Feb-2016
 *      Author: vibhanshu
 */

#include"commons.h"
#include<algorithm>
#include<vector>
#include<string>
#include<iostream>
#include<sstream>
using namespace std;

vector<string> split(string str, char delimiter) {
    vector<string> interval;
    stringstream ss(str);
    string tok;
    while( getline(ss,tok,delimiter) ) {
        interval.push_back(tok);
    }
    return interval;
}






