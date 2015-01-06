#include <iostream>
using namespace std;
#include <vector>
#include <math.h>
#include "BSplineView.h"




CBSplineSurfaceView::CBSplineSurfaceView()
{
	ControlPoint[0][0]=Point3D(-3.5, -2.5, 4.0);
	ControlPoint[0][1]=Point3D(-4.0, 1.5, 4.0);
	ControlPoint[0][2]=Point3D(0.0, 1.5, 4.0);
	ControlPoint[0][3]=Point3D(4.5, 1.5, 4.0);
	ControlPoint[0][4]=Point3D(3.5, -2.5, 4.0);
	ControlPoint[1][0]=Point3D(-4.5, -3.5, 2.0);
	ControlPoint[1][1]=Point3D(-3.0, 2.0, 2.0);
	ControlPoint[1][2]=Point3D(0.0, 4.0, 2.0);
	ControlPoint[1][3]=Point3D(3.0, 2.0, 2.0);
	ControlPoint[1][4]=Point3D(4.5, -3.5, 2.0);
	ControlPoint[2][0]=Point3D(-3.5, -3.5, 0.0);
	ControlPoint[2][1]=Point3D(-2.0, 0.0, 0.0);
	ControlPoint[2][2]=Point3D(0.0,-1.5, 0.0);
	ControlPoint[2][3]=Point3D(2.0, 0.0, 0.0);
	ControlPoint[2][4]=Point3D(3.5, -3.5, 0.0);
	ControlPoint[3][0]=Point3D(-4.0, -4.0,-2.0);
	ControlPoint[3][1]=Point3D(-3.0, 0.0,-2.0);
	ControlPoint[3][2]=Point3D(0.0, 2.5,-2.0);
	ControlPoint[3][3]=Point3D(3.0, 0.0,-2.0);
	ControlPoint[3][4]=Point3D(4.0, -4.0,-2.0);
	ControlPoint[4][0]=Point3D(-3.5, -3.0,-4.0);
	ControlPoint[4][1]=Point3D(-2.5, 3.0,-4.0);
	ControlPoint[4][2]=Point3D(0.0, 4.0,-4.0);
	ControlPoint[4][3]=Point3D(2.5, 3.0,-4.0);
	ControlPoint[4][4]=Point3D(3.5, -3.0,-4.0);
 uknots=NULL;
 vknots=NULL;
	
	

}
CBSplineSurfaceView ::~CBSplineSurfaceView()
{
	 delete []uknots;
     delete []vknots;

}


//CP控制点
//k,l分别代表求[uk,u_k+1],[vl,v_l+1];
//p,q分别代表p*q次曲线,
Point3D  CBSplineSurfaceView::deboor(Point3D CP[][N+1],int k,int l,int p,int q,double uknot[],double vknot[],double u,double v)
{

	double denom1,denom2,alpha1,alpha2;
	vector< vector<Point3D> > P(p+1);
	for(int i=0;i<p+1;i++)
		P[i].resize(q+1);//设置数组的大小(p+1)*(q+1)
	//现在你可以和使用数组一样使用这个vector
	for(int i=0;i<p+1;i++)
		for(int j=0;j<q+1;j++)
			P[i][j]=CP[k-p+i][l-q+j];

	const double epsilon=0.0005;

	
	for (int r=1;r<p+1;r++)
	{
		for (int s=1;s<q+1;s++)
		{
		
		    for (int i=p;i>=r;i--)
				for(int j=q;j>=s;j--)
		          {
			         denom1=uknot[i-r+k+1]-uknot[i-p+k];
					 denom2=vknot[j-s+l+1]-vknot[j-q+l];
			              if(fabs(denom1)<epsilon)
				             alpha1=0;
			               else
				             alpha1=(u-uknot[i-p+k])/denom1;
						  if(fabs(denom2)<epsilon)
							  alpha2=0;
						  else
							  alpha2=(v-vknot[j-q+l])/denom2;
			               P[i][j]=(1-alpha1)*(1-alpha2)*P[i-1][j-1]+(1-alpha1)*alpha2*P[i-1][j]+alpha1*(1-alpha2)*P[i][j-1]+alpha1*alpha2*P[i][j];
		          }
		}
	}
	return P[p][q];

}
//CP控制点，u节点向量为m+p+2;v节点向量为n+q+2个
//输出采用de boor算法生成的B样条曲面上的离散点序列pts
//曲面的离散点个数为(mpoints+1)*(npoints+1)
void  CBSplineSurfaceView::solve_bspline(Point3D P[][N+1],int m,int n,int p,int q,double uknot[],double vknot[],Point3D pts[][npoints+1] )
{

	double u,v,delt1,delt2;
	int i1,i2,j1,j2;
	delt1=(uknot[m+1]-uknot[p])/(double)mpoints;//定义区间为[u_p,u_(m+1)],均分成mpoints等分
	delt2=(vknot[n+1]-vknot[q])/(double)npoints;//定义区间为[v_q,v_(n+1)],均分成npoints等分
	j1=p;
	u=uknot[p];
	
	
		for(i1=0;i1<=mpoints;i1++,u+=delt1)
		{
			j2=q;
             v=vknot[q];
			for (i2=0;i2<=npoints;i2++,v+=delt2)
			{
				while((j1<m)&&(u>uknot[j1+1]))j1++;//确保参数u的节点区间在[uj1,uj1+1]
				while((j2<n)&&(v>vknot[j2+1]))j2++;//确保参数u的节点区间在[vj2,vj2+1]
				pts[i1][i2]=deboor(P,j1,j2,p,q,uknot,vknot,u,v);
			}
		}

}
void CBSplineSurfaceView::GenerateKnots(int type)
{
	int i,j,ulen=M+p+2,vlen=N+q+2;
	uknots=new double[ulen];
	vknots=new double[vlen];
	switch (type)
	{
	case 0:
		for(i=0;i<ulen;i++)
			uknots[i]=i;
		for(j=0;j<vlen;j++)
			uknots[j]=j;
		break;
	case 1:
		for(i=0;i<ulen;i++)
			if(i<=p)
				uknots[i]=0;
			else if(i>=M+1)
				uknots[i]=M-p+1;
			else
				uknots[i]=i-p;
		for(j=0;j<vlen;j++)
				if(j<=q)
					vknots[j]=0;
				else if(j>=N+1)
					vknots[j]=N-q+1;
				else
					vknots[j]=j-q;
				break;
	}
}
