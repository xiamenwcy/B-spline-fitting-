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
#include <math.h>
#include <iostream>

//cgal
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Triangle_2_Iso_rectangle_2_intersection.h>
#include <CGAL/Segment_2_Triangle_2_intersection.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>

using namespace std;

const double  EPSILON = 10e-16;

typedef CGAL::Cartesian<double>                           Kernel;
typedef CGAL::Point_2<Kernel>                          Point_2; 
typedef CGAL::Segment_2<Kernel>                        Segment_2;
typedef  CGAL::Triangle_2<Kernel>                      Triangle_2;
typedef  CGAL::Iso_rectangle_2<Kernel>                 Iso_rectangle_2;
typedef CGAL::Polygon_2<Kernel>                           Polygon_2;
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
	bool fitting_completed();
	bool curvature_error_completed();
	void set_fitting_completed(bool state);
	void set_curvature_loadingstate(bool state);
	bool compute_curvature(QStringList files);
//	double *get_error();
//	void add_knots(vector<Point_2> &vp);
//	Point_3 *get_control_vertices();
//	Point_3 *get_adjusted_control_vertices();
//	Polyhedron *get_domain_mesh();


	 bool interection_st( Triangle_2 tri,Segment_2 seg);//三角形与边相交
	 bool  intersection_rt(Triangle_2 tri,Iso_rectangle_2 rec,double *Area);//求三角形与矩形的交集

	void  update_curvature_color();
	void  update_knots(int k);
	 bool  knots_iteration();
    double *uknots;
	double *vknots;
	int unum;
	int vnum;
	static int iter_num;
	 double curaverage;//曲率积分平均值
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
	 bool   fitting_completed_;
	 bool    curvature_error;
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
