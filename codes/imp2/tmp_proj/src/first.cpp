/*
 * first.cpp
 *
 *  Created on: 21-Feb-2016
 *      Author: vibhanshu
 */


#include"first.h"

struct s
{
	int a[100];
};

int main()
{
	cout<<"Hello World"<<endl;
	int a;
	float b;
	double c;
	s ss;
	cout<<sizeof(&a)<<endl;
	cout<<sizeof(&b)<<endl;
	cout<<sizeof(&c)<<endl;
	cout<<sizeof(ss)<<endl;
	cout<<sizeof(&ss)<<endl;
	return 0;
}

