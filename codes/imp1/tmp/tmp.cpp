#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<sstream>
#include<utility>
using namespace std;

class A
{
public: 
    virtual void f()
    { cout<<"function f() inside A "<<endl; }
};

class B : public A
{
public:
    void f()
    {   cout<<"function f() inside B "<<endl;  }
    void g()
    {   cout<<"function g() inside B "<<endl; }
};

int main()
{
    A* a = new A;
    a->f();
    delete a;
    a = new B;
    a->f();
    ((B*)a)->g();
}

