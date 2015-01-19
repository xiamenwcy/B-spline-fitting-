#include "B_parameter.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;
B_parameter::B_parameter(void)
{
	p=q=m=n=num_u=num_v=0;
	uknot=NULL;
	vknot=NULL;
	iteration_ok=false;
}

B_parameter::~B_parameter(void)
{
	delete uknot;
	delete vknot;
}

B_parameter::B_parameter(int p1,int q1,int m1,int n1)
{
	
	p=p1;
	q=q1;
	m=m1;
	n=n1;
	num_u=num_v=0;
	uknot=NULL;
	vknot=NULL;
	iteration_ok=false;
}
void B_parameter::setnum(int a,int b)
{
	num_u=a;
	num_v=b;
}
bool B_parameter::compute_knots()
{
	if (p>(m+1))
		return false;
	if (q>(n+1))
		return false;

	float du=1.0/(m+1-p);
	float dv=1.0/(n+1-q);
	uknot=new float[num_u];
	vknot=new float[num_v];
	int i,j;
	uknot[0]=0;
	vknot[0]=0;

	for(i=1;i<num_u;i++)
	{
		if (i==num_u-1)
		uknot[i]=1.0;
		else
		uknot[i]=uknot[i-1]+du;
	}
	for (j=1;j<num_v;j++)
	{
		if (j==num_v-1)
		vknot[j]=1.0;
		else
		vknot[j]=vknot[j-1]+dv;
	}
	return true;
}
bool B_parameter::configure_knots()
{//如果迭代成功，绘制的是迭代后的节点线，否则，不管是初次初始化还是迭代失败，均绘制初始化的节点线
  if(iteration_ok)
      return true;
  else
  {
	 if(compute_knots())
	     return true;
	 else
		 return false;
  }
}
float *B_parameter::getuknot()
{
	return uknot;
}
float *B_parameter::getvknot()
{
	return vknot;
}
int B_parameter::getp()
{
	return p;
}
int B_parameter::getq()
{
	return q;
}
int B_parameter::getm()
{
	return m;
}
int B_parameter::getn()
{
	return n;
}
int B_parameter::getnum_u()
{
	return num_u;
}
int B_parameter::getnum_v()
{
	return num_v;
}
void B_parameter::setp(int value)
{
	p=value;
	
}
void B_parameter::setq(int value)
{
	q=value;

}
void B_parameter::setm(int value)
{
	m=value;

}
void B_parameter::setn(int value)
{
	n=value;

}
void B_parameter::setuknots(float *uknots)
{
    uknot=uknots;
}
void B_parameter::setvknots(float *vknots)
{
    vknots=vknots;
}