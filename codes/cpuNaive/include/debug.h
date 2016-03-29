/*
    This is a header file defined for debuggging the source code
*/
#ifndef DEBUG_HEADER
#define DEBUG_HEADER

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"Graph.h"
#include"keyValueStore.h"

// prints the configuration
void printCONF(Graph* g,CONF conf);
void printPKEY(Graph* g,PKEY key);

#endif
