#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include "BSplineView.h"
#include <Eigen/SparseCholesky>
using namespace Eigen;
using namespace  std;
#define  EPSILON4 0.00001




CBSplineSurfaceView::CBSplineSurfaceView()
{
	parameter=NULL;
	m_pFittedMesh=NULL;
	

	

}
CBSplineSurfaceView ::~CBSplineSurfaceView()
{

}
bool CBSplineSurfaceView::solvecontrolpoint(Mesh *mesh)
{
     int  p_num=mesh->n_vertices();
	ofstream out_file( "ControlPoint.txt" );
	if (parameter==NULL)
		return false;
	int m=parameter->getm();
	int n=parameter->getn();
	int p=parameter->getp();
	int q=parameter->getq();
	double *uknot1=parameter->getuknot();//uknot1是从up到u_m+1
	double *vknot1=parameter->getvknot();
	double *uknot=new double[m+p+2];//uknot是从u0到u_m+p+1
	double *vknot=new double[n+q+2];
	//增补节点元素
	for(int i=0;i<m+p+2;i++)	
	{
		if(i<p)
			uknot[i]=0.0;
		else if(i>m+1)
			uknot[i]=1.0;
		else
			uknot[i]=uknot1[i-p];
	}
	for(int j=0;j<n+q+2;j++)
	{
		if(j<q)
			vknot[j]=0.0;
		else if(j>n+1)
			vknot[j]=1.0;
		else
			vknot[j]=vknot1[j-q];
	}

	//设置控制顶点的规模
	ControlPoint.resize(m+1);
	for (int i=0;i<=m;i++)
	{
		ControlPoint[i].resize(n+1);
	}

	Mesh::VertexIter          v_it, v_end(mesh->vertices_end());
	SparseMatrix<double>  A(p_num,(m+1)*(n+1));
	//求取控制顶点方程系数A 
	int row_index=0;
	int k=0;int l=0;
	for (v_it=mesh->vertices_begin();v_it!=v_end;++v_it,++row_index)
	{
		TexCoord   vt=mesh->texcoord2D(*v_it);
		double u=vt[0];
		double v=vt[1];
#if 0
		double sum=0.0;
		for(int i=0;i<=m;i++)
			for (int j=0;j<=n;j++)
			{
				sum+=Base(i,p+1,uknot,m+p+2,u)*Base(j,q+1,vknot,n+q+2,v);
			}
			if (abs(sum-1)>EPSILON4)
			{
				cout<<(*v_it).idx()<<endl;
				if (mesh->is_boundary(*v_it))
					cout<<"边界点之和"<<" ";
				cout<<sum<<endl;
			}
#endif
		for (int j=0;j<(m+1)*(n+1);j++)
		{
			k=j/(n+1);
			l=j%(n+1);
			if (u>=uknot[k]&&u<=uknot[k+p+1]&&v>=vknot[l]&&v<=vknot[l+q+1])
			{
				A.coeffRef(row_index,j)=Base(k,p+1,uknot,m+p+2,u)*Base(l,q+1,vknot,n+q+2,v);
			}
		}

	}
		//求解方程右端矩阵b 
		MatrixXd b(p_num,3),P;
		int h=0;
		for (v_it=mesh->vertices_begin(); v_it!=v_end; ++v_it)
		{
			b(h,0)=mesh->point(*v_it).data()[0];
			b(h,1)=mesh->point(*v_it).data()[1];
			b(h,2)=mesh->point(*v_it).data()[2];
			h++;

		}
		SimplicialLDLT<SparseMatrix<double> > solver;
		solver.compute(A.transpose()*A);
		if(solver.info()!=Success) {
			// decomposition failed
			return false;
		}
		P=solver.solve(A.transpose()*b);
		if(solver.info()!=Success) {
			// solving failed
			return false;
		}
			//将结果赋予控制点 
			if (out_file.is_open()) 
			{
				for (int i=0;i<(m+1)*(n+1);i++)
				{
					k=i/(n+1);
					l=i%(n+1);
					ControlPoint[k][l].x=P(i,0);
					ControlPoint[k][l].y=P(i,1);
					ControlPoint[k][l].z=P(i,2);

					out_file <<ControlPoint[k][l].x<<" "<<ControlPoint[k][l].y<<" "<<ControlPoint[k][l].z<<endl;

				}	
				out_file.close();
			}
			return true;
}


//根据B样条曲线的定义，计算B样条曲线上各点的坐标值，P为控制点
//控制点P的个数为n+1,输入参数knot为B样条曲线节点向量，节点向量的个数为num

Point3D  CBSplineSurfaceView::BSpline(double u,double v)
{
	Point3D ret=Point3D(0,0,0);
	int M=parameter->getm();//前提是必须赋予parameter数值
	int N=parameter->getn();
	double *uknot1=parameter->getuknot();//uknot1是从up到u_m+1
	double *vknot1=parameter->getvknot();
	int p=parameter->getp();
	int q=parameter->getq();
	double *uknot=new double[M+p+2];//uknot是从u0到u_m+p+1
	double *vknot=new double[N+q+2];
	for(int i=0;i<M+p+2;i++)	
	{
		if(i<p)
			uknot[i]=0.0;
		else if(i>M+1)
			uknot[i]=1.0;
		else
			uknot[i]=uknot1[i-p];
	}
	for(int j=0;j<N+q+2;j++)
	{
		if(j<q)
			vknot[j]=0.0;
		else if(j>N+1)
			vknot[j]=1.0;
		else
			vknot[j]=vknot1[j-q];
	}
	
	double temp1,temp2;
	for(int i=0;i<=M;i++)
	{
		temp1=Base(i,p+1,uknot,M+p+2,u);
			for(int j=0;j<=N;j++)
				{
		
				temp2=Base(j,q+1,vknot,N+q+2,v);
				
				ret+=ControlPoint[i][j]*temp1*temp2;
			}
	}
	return ret;

}
//mesh为原始网格  
bool  CBSplineSurfaceView::fitting_bspline( Mesh *mesh)
{
	if (mesh==NULL)
		return false;
    if (!solvecontrolpoint(mesh))
        return false;

	m_pFittedMesh=new Mesh;
	*m_pFittedMesh=*mesh;

	Point3D p;

	Mesh::VertexIter          v_it, v_end(m_pFittedMesh->vertices_end());
	for (v_it=m_pFittedMesh->vertices_begin(); v_it!=v_end; ++v_it)
	{
      TexCoord   vt=m_pFittedMesh->texcoord2D(*v_it);
	  double u=vt[0];
	  double v=vt[1];
      p=BSpline(u,v);
	//  void 	set_point (VertexHandle _vh, const Point &_p)
		 // Set the coordinate of a vertex. 
      m_pFittedMesh->set_point(*v_it,p.toPoint());
	}
		 m_pFittedMesh->update_normals();
		return true;

}
//k代表阶数
double CBSplineSurfaceView::Base(int i,int k,double knot[],int num,double u)//计算B样条基函数
{
	double  val1=0.;
	double  val2=0.;
	if (k==1)
	{
		if(u<knot[i]||u>knot[i+1]) return 0.0;
		else
		{
			return 1.0;

		}
	}
	else
	{
			double alpha=0.0;
			double  beta=0.0;
			double dTemp=0.0;
			dTemp=knot[i+k-1]-knot[i];
			if (dTemp==0.)
				alpha=0.;
			else 
				alpha=(u-knot[i])/dTemp;

			dTemp=knot[i+k]-knot[i+1];

			if(dTemp==0.)
				beta=0.;
			else
				beta=(knot[i+k]-u)/dTemp;

			val1=alpha*Base(i,k-1,knot,num,u);
			val2=beta*Base(i+1,k-1,knot,num,u);
			return val1+val2;

	}
	

}

//// 过滤掉小数位》0.0 000 000 0001后的数字,如123.4567，变成123.45（过滤67）
//double CBSplineSurfaceView::filter(double t)
//{
//	double f;
//	f=floor(t*1e10)/(1e10);
//	return f;
//}
void CBSplineSurfaceView::setBparameter(B_parameter *pa)
{
	parameter=pa;
	
}
Mesh* CBSplineSurfaceView::getFittingMesh()
{
	return m_pFittedMesh;
}
Array2 CBSplineSurfaceView::getControlPoint()
{
	return ControlPoint;
}