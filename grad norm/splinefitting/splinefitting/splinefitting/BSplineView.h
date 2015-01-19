#ifndef BSplineView
#define BSplineView
#include <Eigen/Eigen>
#include "B_parameter.h"
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <vector>
using std::vector;
using namespace Eigen;

typedef OpenMesh::TriMesh_ArrayKernelT<>                    Mesh;
typedef Mesh::TexCoord2D                                    TexCoord;//����д��TexCoord2D 

class Point3D//��ά�ռ��Point3D��
{
public:
	float x,y,z;
	Point3D(){x=0;y=0;z=0;};
	Point3D(float _x,float _y,float _z){x=_x;y=_y;z=_z;};
	Point3D(float s){x=s;y=s;z=s;};
	Point3D operator =(Point3D p1){x=p1.x;y=p1.y;z=p1.z;return (*this);};
	Point3D operator +=(Point3D p1){x+=p1.x;y+=p1.y;z+=p1.z;return(*this);};
	Point3D operator -=(Point3D p1){x-=p1.x;y-=p1.y;z-=p1.z;return(*this);};
	Point3D operator *=(float s){x*=s;y*=s;z*=s;return(*this);};
	Point3D operator /=(float s){x/=s;y/=s;z/=s;return(*this);};
	Point3D operator +(Point3D p1){Point3D t;t.x=x+p1.x;t.y=y+p1.y;t.z=z+p1.z;return(t);};
	Point3D operator -(Point3D p1){Point3D t;t.x=x-p1.x;t.y=y-p1.y;t.z=z-p1.z;return(t);};
	Point3D operator *(float s){Point3D t;t.x=x*s;t.y=y*s;t.z=z*s;return(t);};
	Point3D operator /(float s){Point3D t;t.x=x/s;t.y=y/s;t.z=z/s;return(t);};
	friend Point3D operator *(float s,Point3D p1){Point3D t;t.x=p1.x*s;t.y=p1.y*s;t.z=p1.z*s;return(t);};
	/*double  operator[](int l)
	{
		if (l==0)
	    return x;
	else if(l==1)
	    return y;
	else if (l==2)
	    return z;
	else
		return 0;
	};*/
	Mesh::Point toPoint(){return(Mesh::Point(x,y,z));};

};

typedef vector<vector<Point3D> >                            Array2;

class CBSplineSurfaceView 
{
public:
	CBSplineSurfaceView();

private:
     Array2  ControlPoint;//����ǵ����Ϣ����
	 B_parameter *parameter;
	 Mesh  *m_pFittedMesh;
public:
	bool fitting_bspline( Mesh *mesh);//meshΪԭʼ����,�ȼ�����ƶ��㣬�ټ����������m_pFittedMesh
	Mesh* getFittingMesh(); 
	bool solvecontrolpoint( Mesh *mesh);
	Array2 getControlPoint();

public:
	Point3D BSpline(float u,float v);//����ֱ�ӻ�ͼ��
	float Base(int i,int k,float knot[],int num,float u);//����B����������k=p+1      
	//double  filter(double t);//���˵�0.0000001���������
	void  setBparameter(B_parameter *pa);
	


public:
	virtual ~CBSplineSurfaceView();
};
#endif