#include<map>
#include<pair>
#include<array>
#include<utility>

typedef array<int,2> CONF;     
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
