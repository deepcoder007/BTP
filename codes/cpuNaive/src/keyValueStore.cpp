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
#include"keyValueStore.h"
#define THD 4
//#include"keyValueStore.h"
using namespace std;


// TODO: check if the case of no key can be changed
float keyValueStore::getValue(PKEY key) {
    if( phero.find(key) !=phero.end() ) {
        return phero[key];
    } else {
        return -1.0;    // node node initialized -> in MMAS it is MAX_VALUE
    }
}

void keyValueStore::setValue(PKEY key,float val) {
    phero[key]=val;
}

bool keyValueStore::keyExist(PKEY key) {
    if( phero.find(key) != phero.end() ) {
        return true;
    } else {
        return false;
    }
}

PKEY keyValueStore::getKey(CONF a,CONF b) {
    return make_pair(a,b);
}

int keyValueStore::getSize() {
    return phero.size();
}
