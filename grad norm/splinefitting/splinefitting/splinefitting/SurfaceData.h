#pragma once

#include <CGAL/Bbox_2.h>
#include <CGAL/Bbox_3.h>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QObject>
#include "BSplineView.h"
#include "B_parameter.h"
#include "data_types.h"
#include <vector>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
using namespace std;
#define  EPSILON 10e-16
#define  EPSILON2  0.00000001
#define  EPSILON3  0.001

typedef OpenMesh::PolyMesh_ArrayKernelT<>                   MyMesh;
typedef CGAL::Bbox_2                                        Bbox_2;
typedef CGAL::Bbox_3                                        Bbox_3;


class CSurfaceData :
	public  QObject
{
	Q_OBJECT
public:
	CSurfaceData(void);
	~CSurfaceData(void);
	bool read_mesh(const QString &fileName);
//  bool write_mesh(QString &fileName);
//	bool write_mesh(QString &fileName, Polyhedron *mesh);
//	void surface_sampling(int index);
//	void clear_data();
	int get_mesh_vertex_num();
	int get_mesh_face_num();
//	void set_nseed(int &n);
//	int &get_nknots();
//	int &get_nseed();
//	void set_degree(int &n);
	QString get_mesh_name();
	Mesh *get_original_mesh();
	void setparameter(B_parameter *parameter_2);
	void   set_max_curvature(double curvature);
	double get_max_meancurvature();
    double get_min_meancurvature();
	B_parameter *getparameter();
	Mesh *get_fitted_mesh();
//	Polyhedron *get_density_mesh();
	bool mesh_fitting();
    CBSplineSurfaceView* getbspline();
//	void surface_fitting();
//	void set_boundary_condition(bool b);
//	void set_triangulation_type(Triangulation_type t);
	//Point_2 &get_knots();
//	vector<Knot> &get_centroid();
	vector<TexCoord>  get_domain();
//	vector<CentroidTriangulation> &get_centroid_points();
//	vector<vector<unsigned>> &get_centroidtrianglesk_1();
//	vector<vector<unsigned>> &get_centroidtrianglesk_2();
	Bbox_2 &get_box();
	Bbox_3 get_original_box();
	Bbox_3 get_fitting_box();
    Bbox_3 get_error_box();
	void   set_original_box(Bbox_3 box);
    void   set_fitting_box(Bbox_3 box);
//	Polyhedron *get_basis_sum_polyhedron();
//	Polyhedron *get_basis_polyhedron(int &index);
//	int get_basis_size();
//	void set_row_col(int nR, int nC);
	bool mesh_parameterization();
//	void knots_generation();
	void compute_error();
	bool curvature_loading();
	void set_curvature_loadingstate(bool state);
	bool compute_curvature(QStringList files);
//	double *get_error();
//	void add_knots(vector<Point_2> &vp);
//	Point_3 *get_control_vertices();
//	Point_3 *get_adjusted_control_vertices();
//	Polyhedron *get_domain_mesh();
	void  update_curvature_color();
	void  update_knots(int k);
	void  reorder_knots(vector<TexCoord> *polygon);
	float  area(vector<TexCoord> polygon);
	int   intersection_u(TexCoord A,TexCoord B,float u,TexCoord *intersection); //返回交点个数 
    int   intersection_v(TexCoord A,TexCoord B,float v,TexCoord *intersection); //返回交点个数
	bool  intersection_check(TexCoord a,TexCoord b,TexCoord A,TexCoord B,TexCoord C);//求线段ab与三角形ABC是否相交
	bool  intersection_line_check(TexCoord a,TexCoord b,TexCoord A,TexCoord B);//求解线段ab与线段AB是否相交
	int  intersection_uhull_check(float u,vector<TexCoord> polygon,vector<TexCoord> *intersection,bool *right);//求解u线与凸多边形的交点,
	int  intersection_vhull_check(float v,vector<TexCoord> polygon,vector<TexCoord> *intersection,bool *upper);//求解u线与凸多边形的交点,
	bool  knots_iteration();
	//bool is_triangle_vertex(TexCoord a,TexCoord b,TexCoord c,TexCoord d);
	//bool is_polygon_vertex(vector<TexCoord> polygon,TexCoord d);
   static bool check_func(TexCoord i, TexCoord j);//检测两个顶点是否相等,用在uique,必须加上static,否则没法以成员函数为回调函数。
	float *uknots;
	float *vknots;

	int unum;
	int vnum;
	float curaverage;//曲率积分平均值
	vector<float> error_sum;//每一次迭代的误差和
//	void update_domain_color(int index);
//	double **get_controlvertices_color();
	void set_max_error(double &err);
	void  set_knots_iteration_times(int n);
//	void set_max_density(double &ratio);
//	Polyhedron *get_control_mesh();
//	Polyhedron *get_simplified_mesh();
//	vector<Edge> &get_control_edges_auxiliary();
//	int check_selected(Point_3 &pt, double dist);
//	void update_mesh(int index, Point_3 &npt);
//	Polyhedron *get_adjusted_mesh();
//	vector<SplineBasis> &get_basis_collection();
//	int triangular_test(vector<pair<unsigned, unsigned>> &samePairs);
	double &get_mean_error();
	Max_Error &get_max_error();
	double  get_max_knotcurerror();
	double  get_min_knotcurerror();
//	Polyhedron *get_basis_mesh()
//	{
//		return m_pBasisMesh;
//	}
//	vector<Point_2> &get_basis_convex_hull(int &index);
//	vector<SplineBasis> &get_spline_basis();
//	void get_basis_knots(vector<Point_2> &pts, int &index);
	Mesh *get_error_fitted_mesh();
	void update_polymesh();
	MyMesh get_polymesh();
	void color_polymesh();
//	void get_configsk(vector<BoundaryInteriorConfigs> &configsk);
//	bool write_para(QString &fileName);
//
//	void add_knots(int num);
//
//	vector<BoundaryInteriorConfigs> &get_configs0();
//	void set_output(bool bo);
//	vector<vector<Point_2>> &get_feature_hulls();
//	vector<Point_2> &get_feature_hull();
//	void triangulation();
//	vector<Edge> &get_edges();
//	void set_sa_type(SimulatedAnnealing sa);
//	void set_ann(bool av);
//	vector<vector<unsigned>> &get_vertices_triangles_plane();
//	vector<vector<unsigned>> &get_vertices_triangles_space();
//	vector<Edge> &get_control_edges();
//	int &get_iterator_num()
//	{
//		return iter_num;
//	}
//	list<double> &get_global_costs()
//	{
//		return cdt_knotstri.get_global_costs();
//	}
//	void save_global_costs();
//	void set_domain_color(int flag);
//	void compute_basis_function(vector<Point_3>& ps, int index, vector<vector<unsigned>> &faces)
//	{
//		cdt_knotstri.compute_basis_function(ps, index, faces);
//	}
//	vector<Insert_Knot> &get_error_triangles()
//	{
//		return cdt_knotstri.get_error_triangles();
//	}
//	vector<Knot_Data> &get_multiple_knots()
//	{
//		return cdt_knotstri.get_multiple_knots();
//	}
//	vector<vector<unsigned>> &get_thin_triangles(double threshold)
//	{
//		return cdt_knotstri.get_thin_triangles(threshold);
//	}
//	vector<vector<unsigned>> &get_thin_triangles_angle(double threshold)
//	{
//		return cdt_knotstri.get_thin_triangles_angle(threshold);
//	}
//	vector<vector<unsigned>> &get_thin_triangles()
//	{
//		return cdt_knotstri.get_thin_triangles();
//	}
//	vector<vector<unsigned>> &get_thin_triangles_angle()
//	{
//		return cdt_knotstri.get_thin_triangles_angle();
//	}
//	void set_knots_input(bool ki);
//	void write_knots(QString &fileName);
//	vector<vector<Point_3>> &getSparseCurves();
//
//	void getBasisInfo(vector<vector<Point_2>> &boundaries, vector<Point_2> &interior, SplineBasis &basis, int &index);
//	bool getBasis(SplineBasis &basis, int &index);
signals:
	void mesh_changed();
//
private:
//	bool bknots_input;
//	double simplified_time;
//	double fitting_time;
	Mesh *m_pOriginalMesh;
	int iter_times;
    B_parameter *parameter1;
	CBSplineSurfaceView *bsurface;
//	Polyhedron *m_pSimplifiedMesh;
	Mesh  *m_pFittedMesh;
//	Polyhedron *m_pDensityMesh;
	Mesh *m_pErrorMesh;
	MyMesh polymesh;
//	Polyhedron *m_pAdjustedMesh;
//	Polyhedron *m_pDomainMesh;
//	Polyhedron *m_pControlMesh;
//	Polyhedron *m_pBasisMesh;
//	Polyhedron *m_pBasissumMesh;
//
//	CKnotsTriangulation cdt_knotstri;
//	Quadrics q;
//	int iter_num;
	QString fileName;
//	vector<Knot> knots;
//	vector<Knot> centroid;

	/*********** typedef Vec2f 	TexCoord2D and The default 2D texture coordinate type is OpenMesh::Vec2f.     ***********************************/

	vector<TexCoord> domain;
   
	/*********** vector_type & 	maximize (const vector_type &_rhs)
	maximize values: same as *this = max(*this, _rhs), but faster                  ***********************************/

//	double *domain_z;
//	vector<unsigned> pos_added_indices;
//
//	Point_3 *adjusted_control_vertices;
	Bbox_2 box;
	Bbox_3 originalbox;
	Bbox_3 fittingbox;
	Bbox_3 errorbox;
//	bool isBoundary;
//	int nCol;
//	int nRow;
	int sample_num;
//	int nseed;//the number of the centroid
//	int nknots;//the number of the knots
//	int degree;
//	int basis_index;
//	double **controlvertices_color;
//	double *error;
	double err_threshold;
    Max_Error max_err;
	double max_meancurvature;
	double min_meancurvature;
	double max_curerror;
	double min_curerror;
	double mean_err;
	double mean_e;
     bool   Curvature_loading;
//	Triangulation_type type;
//	void assemble_points();
//	void knots_triangulation();
//	vector<unsigned> get_convex_hull(Point_2 *knots, int num, vector<Point_2>&out);
	void compute_box();
//
//	void compute_density();
//	void save_domain();
//	bool read_centroid(QString &fileName);
//
//	void save_boundary_edges();
//	double compute_min_size();
//	void knots_offset(double e);
//
//	bool bmaxdens_changed;
//	bool bmaxerr_changed;
//	bool binput;
//
//	void get_configsk_1(vector<BoundaryInteriorConfigs> &configsk);
//	void get_configsk_2(vector<BoundaryInteriorConfigs> &configsk);
//	double min_distance_to_edges();
//	void random_knots(int num);
//	void clear_prev_data();
//	void update_density_color();
//
//	vector<Point_2> basis_convex_hull;
//	bool boutput;
//
//	void add_knot_max();
	//void write_mesh();
//	void read_knots();
};
