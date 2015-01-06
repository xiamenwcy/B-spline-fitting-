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


//CP���Ƶ�
//k,l�ֱ������[uk,u_k+1],[vl,v_l+1];
//p,q�ֱ����p*q������,
Point3D  CBSplineSurfaceView::deboor(Point3D CP[][N+1],int k,int l,int p,int q,double uknot[],double vknot[],double u,double v)
{

	double denom1,denom2,alpha1,alpha2;
	vector< vector<Point3D> > P(p+1);
	for(int i=0;i<p+1;i++)
		P[i].resize(q+1);//��������Ĵ�С(p+1)*(q+1)
	//��������Ժ�ʹ������һ��ʹ�����vector
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
//CP���Ƶ㣬u�ڵ�����Ϊm+p+2;v�ڵ�����Ϊn+q+2��
//�������de boor�㷨���ɵ�B���������ϵ���ɢ������pts
//�������ɢ�����Ϊ(mpoints+1)*(npoints+1)
void  CBSplineSurfaceView::solve_bspline(Point3D P[][N+1],int m,int n,int p,int q,double uknot[],double vknot[],Point3D pts[][npoints+1] )
{

	double u,v,delt1,delt2;
	int i1,i2,j1,j2;
	delt1=(uknot[m+1]-uknot[p])/(double)mpoints;//��������Ϊ[u_p,u_(m+1)],���ֳ�mpoints�ȷ�
	delt2=(vknot[n+1]-vknot[q])/(double)npoints;//��������Ϊ[v_q,v_(n+1)],���ֳ�npoints�ȷ�
	j1=p;
	u=uknot[p];
	
	
		for(i1=0;i1<=mpoints;i1++,u+=delt1)
		{
			j2=q;
             v=vknot[q];
			for (i2=0;i2<=npoints;i2++,v+=delt2)
			{
				while((j1<m)&&(u>uknot[j1+1]))j1++;//ȷ������u�Ľڵ�������[uj1,uj1+1]
				while((j2<n)&&(v>vknot[j2+1]))j2++;//ȷ������u�Ľڵ�������[vj2,vj2+1]
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
