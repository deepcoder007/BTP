#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;

class A
{
private:
    int a;
public:
    void printA()
    {
        cout<<"A is : "<<a<<endl;
    }
    void setA(int i)
    {
        a = i;
    }
    A getClone()
    {
        A b ;
        b.a = a;
        return b;
    }
};

int main()
{
    A a;
    a.setA(100);
    A b = a.getClone();
    a.printA();
    b.printA();
    return 0;
}

