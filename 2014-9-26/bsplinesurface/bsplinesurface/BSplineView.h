#ifndef BSplineView
#define BSplineView
const int M=4;//˫�Ĵ�bezier����
const int N=4;
const int p=4;
const int q=4;
const int mpoints=20,npoints=20;//��(mpoints+1)*(npoints+1)���㹹�ɵ�����ƽ�bezier����
class Point3D//��ά�ռ��Point3D��
{
public:
	double x,y,z;
	Point3D(){x=0;y=0;z=0;};
	Point3D(double _x,double _y,double _z){x=_x;y=_y;z=_z;};
	Point3D(double s){x=s;y=s;z=s;};
	Point3D operator =(Point3D p1){x=p1.x;y=p1.y;z=p1.z;return (*this);};
	Point3D operator +=(Point3D p1){x+=p1.x;y+=p1.y;z+=p1.z;return(*this);};
	Point3D operator -=(Point3D p1){x-=p1.x;y-=p1.y;z-=p1.z;return(*this);};
	Point3D operator *=(double s){x*=s;y*=s;z*=s;return(*this);};
	Point3D operator /=(double s){x/=s;y/=s;z/=s;return(*this);};
	Point3D operator +(Point3D p1){Point3D t;t.x=x+p1.x;t.y=y+p1.y;t.z=z+p1.z;return(t);};
	Point3D operator -(Point3D p1){Point3D t;t.x=x-p1.x;t.y=y-p1.y;t.z=z-p1.z;return(t);};
	Point3D operator *(double s){Point3D t;t.x=x*s;t.y=y*s;t.z=z*s;return(t);};
	Point3D operator /(double s){Point3D t;t.x=x/s;t.y=y/s;t.z=z/s;return(t);};
	friend Point3D operator *(double s,Point3D p1){Point3D t;t.x=p1.x*s;t.y=p1.y*s;t.z=p1.z*s;return(t);};
};
class CBSplineSurfaceView 
{
	public:
	CBSplineSurfaceView();

public:
     Point3D ControlPoint[M+1][N+1];//����ǵ����Ϣ����
	 double* uknots;
	 double* vknots;
	 Point3D ptPts[mpoints+1][npoints+1];
public:
	void solve_bspline(Point3D P[][N+1],int m,int n,int p,int q,double uknot[],double vknot[],Point3D pts[][npoints+1]);//����B���������ϵĸ�������pts
	
public:
	 
	Point3D  deboor(Point3D CP[][N+1],int k,int l,int p,int q,double uknot[],double vknot[],double u,double v);
	void  GenerateKnots(int type);

public:
	virtual ~CBSplineSurfaceView();
};
#endif