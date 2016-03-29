#ifndef KEY_VALUE_STORE
#define KEY_VALUE_STORE

#include<map>
#include<array>
#include<utility>
using namespace std;


#define KEY_SZ  2   
#define INT_SZ 30

typedef array<int,KEY_SZ> CONF;     
typedef pair<CONF,CONF>  PKEY;

class keyValueStore 
{
private:
    map<PKEY,float > phero;
public:
    keyValueStore() {}
    float getValue(PKEY key);
    void setValue(PKEY key,float val);
    bool keyExist(PKEY key);

    PKEY getKey(CONF a,CONF b); // returns a config from these 2 elements
};


#endif
