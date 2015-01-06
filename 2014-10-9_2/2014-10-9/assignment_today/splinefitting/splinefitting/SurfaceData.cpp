#include <OpenMesh/Core/IO/MeshIO.hh>//必须放在首行
#include "SurfaceData.h"
#include <QtGui/QtGui>
//#include "surfacefitting.h"
//#include "builder_polyhedron.h"
#include <algorithm>
#include <QtGui/QInputDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include<ctime>
#include <QtCore/QDir>

#define _READ_ 1

using namespace std;

//typedef CGAL::Polygon_2<K>                                 Polygon_2;
//typedef Enriched_polyhedron<Kernel3, Enriched_items>::HalfedgeDS HalfedgeDS;
//typedef Builder_Polyhedron<HalfedgeDS> Builder;

CSurfaceData::CSurfaceData(void)
{
	m_pOriginalMesh = NULL;
	/*m_pSimplifiedMesh = NULL;
	m_pFittedMesh = NULL;
	m_pDensityMesh = NULL;
	m_pDomainMesh = NULL;
	m_pControlMesh = NULL;
	m_pAdjustedMesh = NULL;
	m_pBasisMesh = NULL;
	m_pBasissumMesh = NULL;
	m_pErrorMesh = NULL;
	domain  = NULL;
	domain_z = NULL;
	error = NULL;
	
	adjusted_control_vertices = NULL;
	nCol = 0;
	nRow = 0;
	sample_num = 0;
	type = DDT_Mean_Error;
	isBoundary = true;
	controlvertices_color = NULL;
	err_threshold = 1;
	basis_index = -1;
	bmaxdens_changed = true;
	bmaxerr_changed = true;
	nseed = 0;
	iter_num = 0;
	simplified_time = 0;
	fitting_time = 0;
	bknots_input = false;*/
}


CSurfaceData::~CSurfaceData(void)
{
	/*clear_data();*/
}


//void CSurfaceData::clear_data()
//{
//	if(m_pOriginalMesh!=NULL)
//	{
//		delete m_pOriginalMesh;
//		m_pOriginalMesh = NULL;
//	}
//	if(m_pSimplifiedMesh!=NULL)
//	{
//		delete m_pSimplifiedMesh;
//		m_pSimplifiedMesh = NULL;
//	}
//	if(m_pFittedMesh!=NULL)
//	{
//		delete m_pFittedMesh;
//		m_pFittedMesh = NULL;
//	}
//
//	if(m_pDensityMesh!=NULL)
//	{
//		delete m_pDensityMesh;
//		m_pDensityMesh = NULL;
//	}
//	
//	if(m_pDomainMesh!=NULL)
//	{
//		delete m_pDomainMesh;
//		m_pDomainMesh = NULL;
//	}
//	if(m_pControlMesh != NULL)
//	{
//		delete m_pControlMesh;
//		m_pControlMesh = NULL;
//	}
//	if(m_pAdjustedMesh!=NULL)
//	{
//		delete m_pAdjustedMesh;
//		m_pAdjustedMesh = NULL;
//	}
//	if(m_pBasisMesh!=NULL)
//	{
//		delete m_pBasisMesh;
//		m_pBasisMesh = NULL;
//	}
//	if(!m_pBasissumMesh)
//	{
//		delete m_pBasissumMesh;
//		m_pBasissumMesh = NULL;
//	}
//	if(!m_pErrorMesh)
//	{
//		delete m_pErrorMesh;
//		m_pErrorMesh = NULL;
//	}
//	pos_added_indices.clear();
//	knots.clear();
//	centroid.clear();
//	if(domain!=NULL)
//	{
//		delete []domain;
//		domain = NULL;
//	}
//	if(domain_z != NULL)
//	{
//		delete []domain_z;
//		domain_z = NULL;
//	}
//	if(error!=NULL)
//	{
//		delete []error;
//		error = NULL;
//	}
//	
//	if(adjusted_control_vertices!=NULL)
//	{
//		delete []adjusted_control_vertices;
//		adjusted_control_vertices = NULL;
//	}
//
//	if(controlvertices_color!=NULL)
//	{
//		int sz = cdt_knotstri.get_basis_size();
//		for(int i=0; i<sz; i++)
//		{
//			delete []controlvertices_color[i];
//		}
//		delete []controlvertices_color;
//		controlvertices_color = NULL;
//	}
//	basis_index = -1;
//	nCol = 0;
//	nRow = 0;
//	sample_num = 0;
//	nseed = 0;
//	nknots = 0;
	//fileName.clear();
//	
//	isBoundary = true;
//	err_threshold = 1;
//	bmaxdens_changed = true;
//	bmaxerr_changed = true;
//	cdt_knotstri.clear_data();
//	boutput = true;
//	iter_num = 0;
//	emit mesh_changed();
//	simplified_time = 0;
//	fitting_time = 0;
//}

bool CSurfaceData::read_mesh(const QString &name)
{
	fileName = name;
	if(m_pOriginalMesh == NULL)
	{
		m_pOriginalMesh = new Mesh;
	}
	else
	{
		m_pOriginalMesh->clear();//Reset the whole mesh.This will remove all elements from the mesh but keeps the properties

	}
	if(fileName.isEmpty())
	{ 
		QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files.")); 
		return false;
	}
    m_pOriginalMesh->request_vertex_texcoords2D();
	m_pOriginalMesh->request_face_normals();
	m_pOriginalMesh->request_vertex_normals();
	OpenMesh::IO::Options opt;
	opt+=OpenMesh::IO::Options::VertexTexCoord;
	opt+=OpenMesh::IO::Options::VertexNormal;
	QString extension = fileName.right(4);
	if(extension == ".off")
	{
		if(!OpenMesh::IO::read_mesh(*m_pOriginalMesh, fileName.toStdString(),opt))
		{
			QMessageBox::critical(NULL, "Failed to open", "Unable to open file", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			return false;
		}
		
	}
	else if(extension == ".obj")
	{
       
		if(!OpenMesh::IO::read_mesh(*m_pOriginalMesh, fileName.toStdString(),opt))
		{
			QMessageBox::critical(NULL, "Failed to open", "Unable to open file", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			return false;
		}
		
		
	}
	else if(extension == ".stl")
	{
		if(!OpenMesh::IO::read_mesh(*m_pOriginalMesh, fileName.toStdString(),opt))
		{
			QMessageBox::critical(NULL, "Failed to open", "Unable to open file", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			return false;
		}
		
	}
	else
	{
		QMessageBox::critical(NULL, "Unknown extension", "Unknown extension", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return false;
	}
	
	if(opt.check( OpenMesh::IO::Options::VertexTexCoord))
	{
		int sz = m_pOriginalMesh->n_vertices();
		domain.reserve(sz);
		domain.clear();
		Mesh::VertexIter       v_it, v_end(m_pOriginalMesh->vertices_end());

		for (v_it=m_pOriginalMesh->vertices_begin(); v_it!=v_end; ++v_it)
		{
			domain.push_back(m_pOriginalMesh->texcoord2D(*v_it));
			
		}
	}
	//emit mesh_changed();

	/*m_pOriginalMesh->compute_type();
	m_pOriginalMesh->compute_normals();
	m_pOriginalMesh->compute_index();
	m_pOriginalMesh->identify_feature_edges();*/
	if ( !opt.check( OpenMesh::IO::Options::VertexNormal ) &&
		m_pOriginalMesh->has_face_normals() && m_pOriginalMesh->has_vertex_normals() )
	{
		// let the mesh update the normals
		m_pOriginalMesh->update_normals();
	}
	sample_num = m_pOriginalMesh->n_vertices();
	return true;
}

//bool CSurfaceData::write_para(QString &fileName)
//{
//	m_pOriginalMesh->write_para_obj(fileName, domain);
//	return true;
//}
//
//void CSurfaceData::set_boundary_condition(bool b)
//{
//	isBoundary = b;
//}
//
//void CSurfaceData::set_triangulation_type(Triangulation_type t)
//{
//	type = t;
//}
//
//void CSurfaceData::set_sa_type(SimulatedAnnealing sa)
//{
//	cdt_knotstri.set_sa_type(sa);
//}
//
//bool CSurfaceData::write_mesh(QString &fileName, Polyhedron *mesh)
//{
//	if (!fileName.isNull())  
//	{  
//		QFile file( fileName);
//		if ( file.open(QIODevice::WriteOnly)) 
//		{
//			QTextStream stream( &file );
//			if(fileName.right(4) == ".obj")
//			{
//				stream << "# OBJ file format with ext .obj" << endl;
//				QString text = "# vertex count = ";
//				text.append(QString::number(mesh->size_of_vertices(), 'g', 10));
//				stream << text << endl;
//				text = "# face count = ";
//				text.append(QString::number(mesh->size_of_facets(), 10));
//				stream << text << endl;
//				Polyhedron::Vertex_const_iterator v_it = mesh->vertices_begin(), v_end = mesh->vertices_end();
//				for(; v_it!=v_end; v_it++)
//				{
//					stream << "v " << v_it->point().x() << " " << v_it->point().y() << " " << v_it->point().z() << endl;
//				}
//				
//				Polyhedron::Facet_iterator pFacet = mesh->facets_begin(), pFacet_end = mesh->facets_end();
//				for(;pFacet != pFacet_end; pFacet++)
//				{
//					Polyhedron::Halfedge_around_facet_circulator pHalfedge = pFacet->facet_begin();
//					stream << "f ";
//					int i = 0;
//					do
//					{
//						int index = distance(mesh->vertices_begin(), pHalfedge->vertex()) + 1;
//						if(mesh->is_pure_triangle())
//						{	
//							if(i==2)
//								stream << index << endl;
//							else
//								stream << index << " ";
//						}
//						else
//						{
//							if(i==3)
//								stream << index << endl;
//							else
//								stream << index << " ";
//						}
//						i++;
//					}
//					while(++pHalfedge != pFacet->facet_begin());
//				}
//			}
//			else
//			{
//				if(fileName.right(4) == ".off")
//				{
//					stream << "OFF" << endl;
//					stream << mesh->size_of_vertices() << " ";
//					stream << mesh->size_of_facets() << " ";
//					stream << "0" << endl;
//					Polyhedron::Vertex_const_iterator v_it = mesh->vertices_begin(), v_end = mesh->vertices_end();
//					for(; v_it!=v_end; v_it++)
//					{
//						stream << v_it->point().x() << " " << v_it->point().y() << " " << v_it->point().z() << endl;
//					}
//				
//					Polyhedron::Facet_iterator pFacet = mesh->facets_begin(), pFacet_end = mesh->facets_end();
//					if(mesh->is_pure_triangle())
//					{
//						for(;pFacet != pFacet_end; pFacet++)
//						{
//							Polyhedron::Halfedge_around_facet_circulator pHalfedge = pFacet->facet_begin();
//							int i = 0;
//							stream << "3 ";
//							do
//							{
//								int index = distance(mesh->vertices_begin(), pHalfedge->vertex());
//								if(i==2)
//									stream << index << endl;
//								else
//									stream << index << " ";
//								i++;
//							}while(++pHalfedge != pFacet->facet_begin());
//						}
//					}
//					else
//					{
//						if(mesh->is_pure_quad())
//						{
//							for(;pFacet != pFacet_end; pFacet++)
//							{
//								Polyhedron::Halfedge_around_facet_circulator pHalfedge = pFacet->facet_begin();
//								int i = 0;
//								stream << "4 ";
//								do
//								{
//									int index = distance(mesh->vertices_begin(), pHalfedge->vertex());
//									if(i==2)
//										stream << index << endl;
//									else
//										stream << index << " ";
//									i++;
//								}while(++pHalfedge != pFacet->facet_begin());
//							}
//						}
//					}
//				}
//			}
//			file.close();
//		}
//	}
//	return true;
//}
//
//bool CSurfaceData::write_mesh(QString &fileName)
//{
//	if (!fileName.isNull())  
//	{  
//		QFile file( fileName);
//		if ( file.open(QIODevice::WriteOnly)) 
//		{
//			QTextStream stream( &file );
//			if(fileName.right(4) == ".obj")
//			{
//				stream << "# OBJ file format with ext .obj" << endl;
//				QString text = "# vertex count = ";
//				text.append(QString::number(m_pFittedMesh->size_of_vertices(), 'g', 10));
//				stream << text << endl;
//				text = "# face count = ";
//				text.append(QString::number(m_pFittedMesh->size_of_facets(), 10));
//				stream << text << endl;
//				Polyhedron::Vertex_const_iterator v_it = m_pFittedMesh->vertices_begin(), v_end = m_pFittedMesh->vertices_end();
//				for(; v_it!=v_end; v_it++)
//				{
//					stream << "v " << v_it->point().x() << " " << v_it->point().y() << " " << v_it->point().z() << endl;
//				}
//				
//				Polyhedron::Facet_iterator pFacet = m_pFittedMesh->facets_begin(), pFacet_end = m_pFittedMesh->facets_end();
//				for(;pFacet != pFacet_end; pFacet++)
//				{
//					Polyhedron::Halfedge_around_facet_circulator pHalfedge = pFacet->facet_begin();
//					stream << "f ";
//					int i = 0;
//					do
//					{
//						int index = distance(m_pFittedMesh->vertices_begin(), pHalfedge->vertex()) + 1;
//						if(m_pFittedMesh->is_pure_triangle())
//						{	
//							if(i==2)
//								stream << index << endl;
//							else
//								stream << index << " ";
//						}
//						else
//						{
//							if(i==3)
//								stream << index << endl;
//							else
//								stream << index << " ";
//						}
//						i++;
//					}
//					while(++pHalfedge != pFacet->facet_begin());
//				}
//			}
//			else
//			{
//				if(fileName.right(4) == ".off")
//				{
//					stream << "OFF" << endl;
//					stream << m_pFittedMesh->size_of_vertices() << " ";
//					stream << m_pFittedMesh->size_of_facets() << " ";
//					stream << "0" << endl;
//					Polyhedron::Vertex_const_iterator v_it = m_pFittedMesh->vertices_begin(), v_end = m_pFittedMesh->vertices_end();
//					for(; v_it!=v_end; v_it++)
//					{
//						stream << v_it->point().x() << " " << v_it->point().y() << " " << v_it->point().z() << endl;
//					}
//				
//					Polyhedron::Facet_iterator pFacet = m_pFittedMesh->facets_begin(), pFacet_end = m_pFittedMesh->facets_end();
//					if(m_pFittedMesh->is_pure_triangle())
//					{
//						for(;pFacet != pFacet_end; pFacet++)
//						{
//							Polyhedron::Halfedge_around_facet_circulator pHalfedge = pFacet->facet_begin();
//							int i = 0;
//							stream << "3 ";
//							do
//							{
//								int index = distance(m_pFittedMesh->vertices_begin(), pHalfedge->vertex());
//								if(i==2)
//									stream << index << endl;
//								else
//									stream << index << " ";
//								i++;
//							}while(++pHalfedge != pFacet->facet_begin());
//						}
//					}
//					else
//					{
//						if(m_pFittedMesh->is_pure_quad())
//						{
//							for(;pFacet != pFacet_end; pFacet++)
//							{
//								Polyhedron::Halfedge_around_facet_circulator pHalfedge = pFacet->facet_begin();
//								int i = 0;
//								stream << "4 ";
//								do
//								{
//									int index = distance(m_pFittedMesh->vertices_begin(), pHalfedge->vertex());
//									if(i==2)
//										stream << index << endl;
//									else
//										stream << index << " ";
//									i++;
//								}while(++pHalfedge != pFacet->facet_begin());
//							}
//						}
//					}
//				}
//			}
//			file.close();
//		}
//	}
//	return true;
//}
//
//void CSurfaceData::add_knots(vector<Point_2> &vp)
//{
//	//if(knots.empty())
//	//{
//	//	nknots = vp.size();
//	//	nseed = nknots;
//	//	for(int i=0; i<nknots; i++)
//	//	{
//	//		knots.push_back(vp[i]);
//	//	}
//	//}
//	
//}
//
//void CSurfaceData::surface_sampling(int index)
//{
//	double x0 = 0, xn = 1;
//	double y0 = 0, yn = 1;
//	if(domain == NULL)
//	{
//		domain = new Point_2[sample_num];
//	}
//	double *samples = new double[3*sample_num];
//	double rstep = (xn-x0)/(nRow-1);
//	double cstep = (yn-y0)/(nCol-1);
//	int k=0;
//	for(int i=0; i<nRow; i++)
//	{
//		double y = y0+i*rstep;
//		for(int j=0; j<nCol; j++)
//		{
//			double x = x0+j*cstep;
//			samples[3*(i*nCol+j)] = x;
//			samples[3*(i*nCol+j)+1] = y;
//			domain[k] = Point_2(x, y);
//			k++;
//		}
//	}
//
//	if(index == 1)
//	{
//		for(int i=0; i<nRow; i++)
//		{
//			double y = y0+i*rstep;
//			for(int j=0; j<nCol; j++)
//			{
//				double x = x0 + j*cstep;
//				samples[3*(i*nCol+j)+2] = 1;/*0.0833*x*x*x-0.2833*y*y*y+0.35*x*x*y-0.15*x*y*y-0.0604*x*x-0.0471*x*y+
//					0.0396*y*y+0.0167*x-0.0167*y+0.4727;*/
//			}
//		}
//	}
//	else
//	{
//		if(index == 2)
//		{
//			for(int i=0; i<nRow; i++)
//			{
//				double y = y0+i*rstep;
//				for(int j=0; j<nCol; j++)
//				{
//					double x = x0+j*cstep;
//					samples[3*(i*nCol+j)+2] = 1-x*x-y*y;
//				}
//			}
//			
//		}
//		else
//		{
//			for(int i=0; i<nRow; i++)
//			{
//				double y = y0+i*rstep;
//				for(int j=0; j<nCol; j++)
//				{
//					double x = x0+j*cstep;
//					//samples[3*(i*nCol+j)+2] = sqrt(x*x+y*y);
//					if(x<=0.3)
//						//samples[3*(i*nCol+j)+2] = 0.3 + sqrt(0.09 +1e-3 -(x+0.7)*(x+0.7));
//						samples[3*(i*nCol+j)+2] = -13.3333*x*x + 4*x+0.3;
//					else if(x<=0.35)
//						samples[3*(i*nCol+j)+2] = -6*x + 2.1;
//					else if(x<=0.65)
//						samples[3*(i*nCol+j)+2] = 0;
//					else if(x<=0.7)
//						samples[3*(i*nCol+j)+2] = 6*x-3.9;
//					else
//						//samples[3*(i*nCol+j)+2] = 0.3 + sqrt(0.09 +1e-3 -(x-0.85)*(x-0.85));
//						samples[3*(i*nCol+j)+2] = -13.3333*x*x +22.6667*x-9.0333;
//				}
//			}
//		}
//	}
//	if(m_pOriginalMesh==NULL)
//	{
//		m_pOriginalMesh = new Polyhedron;
//	}
//	Builder builder(m_pOriginalMesh, samples, nCol, nRow, IS_QUAD);
//	m_pOriginalMesh->delegate(builder);
//	m_pOriginalMesh->compute_type();
//	m_pOriginalMesh->compute_normals();
//	m_pOriginalMesh->compute_index();
//	compute_box();
//	compute_density();
//	if(boutput)
//	{
//		save_domain();
//		save_boundary_edges();
//	}
//	delete []samples;
//}
//
//Polyhedron *CSurfaceData::get_domain_mesh()
//{
//	if(m_pDomainMesh==NULL)
//	{
//		m_pDomainMesh = new Polyhedron;
//		*m_pDomainMesh = *m_pOriginalMesh; 
//
//		Polyhedron::Vertex_iterator vit = m_pDomainMesh->vertices_begin();
//		int i=0;
//		for(; vit!=m_pDomainMesh->vertices_end(); vit++)
//		{
//			vit->point() = Polyhedron::Point_3(domain[i].x(), domain[i].y(), 0);
//			i++;
//		}
//		m_pDomainMesh->compute_index();
//	}
//
//	return m_pDomainMesh;
//}
//
//void CSurfaceData::set_row_col(int nR, int nC)
//{
//	nCol = nC;
//	nRow = nR;
//	sample_num = nR*nC;
//}
//
bool CSurfaceData::mesh_parameterization()
{
	if(domain.empty())
	{
		
		//如果空的话，需要根据原始网格计算domain，这里先不计算domain,所以我们的网格一定要带有参数化坐标
	}
	compute_box();
	/*compute_density();
	update_curvature_color();
	Polyhedron::Vertex_iterator vit = m_pOriginalMesh->vertices_begin();
	int i=0;
	for(; vit!=m_pOriginalMesh->vertices_end(); vit++)
	{
		vit->selected(false);
		vit->vtx = domain[i].x();
		vit->vty = domain[i].y();
		i++;
	}
	m_pOriginalMesh->compute_vertex_areas();
	if(boutput)
	{
		save_domain();
		save_boundary_edges();
	}
	m_pOriginalMesh->computeFeatures();*/
	return true;
}

//Polyhedron *CSurfaceData::get_simplified_mesh()
//{
//	return m_pSimplifiedMesh;
//}
//
vector<TexCoord> CSurfaceData::get_domain()
{
	return domain;
}

//vector<Knot> &CSurfaceData::get_centroid()
//{
//	return centroid;
//}
//
//vector<TexCoord> &CSurfaceData::get_knots()
//{
//	return  domain;
//}

int CSurfaceData::get_mesh_vertex_num()
{
	if(m_pOriginalMesh!=NULL)
	{
		return m_pOriginalMesh->n_vertices();
	}
	return -1;
}

int CSurfaceData::get_mesh_face_num()
{
	if(m_pOriginalMesh!=NULL)
	{
		return m_pOriginalMesh->n_faces();
	}
	return -1;
}

QString CSurfaceData::get_mesh_name()
{
	return fileName;
}

Mesh *CSurfaceData::get_original_mesh()
{
	return m_pOriginalMesh;
}

//Polyhedron *CSurfaceData::get_fitted_mesh()
//{
//	return m_pFittedMesh;
//}
//
//Polyhedron *CSurfaceData::get_density_mesh()
//{
//	return m_pDensityMesh;
//}
//
//void CSurfaceData::get_configsk(vector<BoundaryInteriorConfigs> &configsk)
//{
//	configsk = cdt_knotstri.get_configsk();
//}
//
//void CSurfaceData::get_configsk_1(vector<BoundaryInteriorConfigs> &configsk)
//{
//	configsk = cdt_knotstri.get_configsk_1();
//}
//
//void CSurfaceData::get_configsk_2(vector<BoundaryInteriorConfigs> &configsk)
//{
//	configsk = cdt_knotstri.get_configsk_2();
//}
//
//void CSurfaceData::surface_fitting()
//{
//	/*QString str = "The maximal density of the original surface is ";
//			
//	QMessageBox::information(NULL, "Error of Fitted Surface", str, QMessageBox::Yes, QMessageBox::Yes);*/
//	/*m_pFittedMesh = new Polyhedron;
//	SurfaceFitting fitting(m_pOriginalMesh, m_pFittedMesh);
//	fitting.set_knots(knots);
//	vector<SplineBasis> basisCollection = cdt_knotstri.get_basis_collection();
//	vector<PointNormal> vpn = cdt_knotstri.get_vpn();
//	vector<vector<unsigned>> basisCombination = cdt_knotstri.get_basiscombination();
//	fitting.set_basis_collection(basisCollection);
//	fitting.set_combination(basisCombination);
//	fitting.set_vpn(vpn);
//	fitting.set_sample_num(sample_num);
//	control_vertices = new Point_3[basisCollection.size()];
//	fitting.set_control_vertices(control_vertices);
//
//	fitting.surface_fitting(nRow, nCol);*/
//}
//
//bool CSurfaceData::read_centroid(QString &fileName)
//{
//	const double tol = 1e-3;
//	QFile file(fileName.toAscii());
//	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
//	{	
//		QTextStream in(&file);
//		QString line = in.readLine();
//		if(line.isNull())
//			return false;
//
//		int num = line.toInt();
//		Point_2 *temp = new Point_2[num];
//		line = in.readLine();
//		int i = 0;
//		while (!line.isNull()) 
//		{
//			QStringList list = line.split(" ");
//			double x = list.at(0).toDouble();
//			double y = list.at(1).toDouble();
//			//if((x-box.xmin()>-EPSILON && box.xmax()-x>-EPSILON) || (y-box.ymin()>-EPSILON && box.ymax()-y>-EPSILON))
//			if((x>box.xmin()-tol && x < box.xmax()+tol) && (y>box.ymin()-tol && y < box.ymax()+tol))
//			{
//				temp[i] = Point_2(x, y);
//				i++;
//			}
//
//			line = in.readLine();
//		}
//		file.close();
//
//	    nseed += num;
//		for(int j=0; j<num; j++)
//		{
//			Knot knot;
//			knot.pt = temp[j];
//			centroid.push_back(knot);
//		}
//		delete []temp;
//	 }
//	 else
//	 {
//		 return false;
//	 }
//	 return true;
//}
//
//double CSurfaceData::min_distance_to_edges()
//{
//	return 0;
//}
//
//void CSurfaceData::mesh_fitting()
//{
//	clock_t start = clock(), finish;
//	triangulation();
//	if(m_pFittedMesh==NULL)
//	{
//		m_pFittedMesh = new Polyhedron;
//		*m_pFittedMesh = *m_pOriginalMesh;
//	}
//	vector<Point_2> pts;
//	for(int i=0; i<knots.size(); i++)
//	{
//		pts.push_back(knots[i].pt);
//	}
//
//	//QMessageBox::information(NULL, "begin Fitted Surface", "ok", QMessageBox::Yes, QMessageBox::Yes);
//	cdt_knotstri.mesh_fitting(pts, m_pFittedMesh);
//	finish = clock();
//
//	m_pFittedMesh->compute_normals();
//	compute_error();
//	cdt_knotstri.compute_error_trianles(error);
//	double elapsedtime = (double(finish-start))/CLOCKS_PER_SEC;
//	fitting_time = elapsedtime - simplified_time;
//	fitting_time = elapsedtime - simplified_time;
//	QString timefileName = "./time";
//	QDir dir(timefileName);
//	timefileName.append("/");
//	QStringList list = fileName.split("/").last().split(".");
//	timefileName.append(list.at(0));
//	bool suc = false;
//	if(dir.exists(list.at(0)))
//	{
//		suc = true;
//	}
//	else
//	{
//		suc = dir.mkdir(list.at(0));
//	}
//
//	if(suc)
//	{
//		if(type==Delaunay)
//		{
//			timefileName.append("/Delaunay_");
//		}
//		else
//		{
//			timefileName.append("/DDT_");
//		}
//		timefileName.append(QString::number(iter_num, 10));
//		timefileName.append(".txt");
//		QFile file( timefileName);
//		if ( file.open(QIODevice::WriteOnly)) 
//		{
//			QTextStream out( &file );
//			out << elapsedtime << "s" << endl;
//			out << "Simplified time: " << simplified_time << endl;
//			out << "Fitting time: " << fitting_time << endl;
//			out << "The size of knots: " << get_knots().size() << endl;
//			out << "The degree of the surface is: " << degree << endl;
//			out << "The size of control points: " << get_basis_size() << endl;
//			out << "The maximal error is: " << max_err.error << endl;
//			out << "The rmse is: " << mean_err << endl;
//			file.close();
//		}
//	}
//	write_mesh();
//	iter_num++;
//}
//
//void CSurfaceData::clear_prev_data()
//{
//	simplified_time = 0;
//	fitting_time = 0;
//
//	knots.clear();
//	
//	//bInfo.clear();
//	cdt_knotstri.clear_data();
//	if(m_pSimplifiedMesh!=NULL)
//	{
//		delete m_pSimplifiedMesh;
//		m_pSimplifiedMesh = NULL;
//	}
//		
//	if(m_pControlMesh != NULL)
//	{
//		delete m_pControlMesh;
//		m_pControlMesh = NULL;
//	}
//	if(m_pAdjustedMesh!=NULL)
//	{
//		delete m_pAdjustedMesh;
//		m_pAdjustedMesh = NULL;
//	}
//	if(m_pBasisMesh!=NULL)
//	{
//		delete m_pBasisMesh;
//		m_pBasisMesh = NULL;
//	}
//	if(m_pBasissumMesh!=NULL)
//	{
//		delete m_pBasissumMesh;
//		m_pBasissumMesh = NULL;
//	}
//	
//	if(adjusted_control_vertices!=NULL)
//	{
//		delete []adjusted_control_vertices;
//		adjusted_control_vertices = NULL;
//	}
//
//	if(controlvertices_color!=NULL)
//	{
//		int sz = cdt_knotstri.get_basis_size();
//		for(int i=0; i<sz; i++)
//		{
//			delete []controlvertices_color[i];
//		}
//		delete []controlvertices_color;
//		controlvertices_color = NULL;
//	}
//}
//
//void CSurfaceData::knots_offset(double e)
//{
//	vector<Point_2> out;
//	get_convex_hull(domain, sample_num, out);
//	double dist = 0;
//	const double tol = 1e-20;
//	for(int i=0; i<centroid.size(); i++)
//	{
//		double x = centroid[i].pt.x();
//		double y = centroid[i].pt.y();
//		bool bxAdjust = false;
//		bool byAdjust = false;
//
//		dist = abs(x-box.xmax());
//		if(dist<e && dist>tol)
//		{
//			bxAdjust = true;
//			x = box.xmax();
//		}
//		dist = abs(x-box.xmin());
//		if(dist<e && dist>tol)
//		{
//			bxAdjust = true;
//			x = box.xmin();
//		}
//		dist = abs(y-box.ymax());
//		if(dist<e && dist>tol && !bxAdjust)
//		{
//			byAdjust = true;
//			y = box.ymax();
//		}
//		dist = abs(y-box.ymin());
//		if(dist<e && dist>tol && !bxAdjust)
//		{
//			byAdjust = true;
//			y = box.ymin();
//		}
//
//		if((bxAdjust || byAdjust) &&(!bxAdjust || !byAdjust))
//		{
//			centroid[i].pt = Point_2(x, y);
//		}
//		/*if(bxAdjust || byAdjust &&(!bxAdjust || !byAdjust))
//			knots.push_back(Point_2(x, y));*/
//	}
//	nknots = knots.size();
//}
//
//void CSurfaceData::compute_density()
//{
//	m_pOriginalMesh->compute_principal_curvature();
//	double *density = new double[sample_num];
//	for(int i=0; i<sample_num; i++)
//	{
//		density[i] = 0;
//	}
//	QStringList list = fileName.split(".");
//	QString fileName1 = list.at(0);
//	QString fileName2 = list.at(0);
//	fileName1.append("_k1.txt");
//	fileName2.append("_k2.txt");
//	vector<double> ks1, ks2;
//	QFile file(fileName1.toAscii());
//	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
//	{	
//		QTextStream in(&file);
//		QString line = in.readLine();
//		int i = 0;
//		Polyhedron::Vertex_iterator v_it = m_pOriginalMesh->vertices_begin();
//		while (!line.isNull()) 
//		{
//			density[i] = abs(line.toDouble());
//			v_it->mean_curvature() = line.toDouble();
//			ks1.push_back(line.toDouble());
//			line = in.readLine();
//			i++;
//			v_it++;
//		}
//		file.close();
//	}
//
//	QFile file1(fileName2.toAscii());
//	if (file1.open(QIODevice::ReadOnly | QIODevice::Text))
//	{	
//		QTextStream in(&file1);
//		QString line = in.readLine();
//		int i = 0;
//		Polyhedron::Vertex_iterator v_it = m_pOriginalMesh->vertices_begin();
//		while (!line.isNull()) 
//		{
//			density[i] += abs(line.toDouble());
//			//density[i] = sqrt(density[i]);
//			v_it->mean_curvature() += line.toDouble();
//			ks2.push_back(line.toDouble());
//			v_it->mean_curvature() /= 2;
//			line = in.readLine();
//			i++;
//			v_it++;
//		}
//		file1.close();
//	}
//
//	Polyhedron::Vertex_iterator v_it = m_pOriginalMesh->vertices_begin();
//	for (int i=0; i<ks1.size(); i++)
//	{
//		v_it->set_principal_curvature(ks1[i], ks2[i]);
//		v_it++;
//	}
//	
//
//	double maxdens = 0;
//	double mindens = 1e200;
//	double meandens = 0;
//	
//	for(int i=0; i<sample_num; i++)
//	{
//		meandens += density[i];
//		if(maxdens<density[i])
//			maxdens = density[i];
//		if(mindens>density[i])
//			mindens = density[i];
//	}
//
//	v_it = m_pOriginalMesh->vertices_begin();
//	int j = 0;
//	for(; v_it!=m_pOriginalMesh->vertices_end(); v_it++)
//	{
//		v_it->vertex_density() = density[j];
//		j++;
//	}
//	m_pOriginalMesh->setDensity(maxdens, mindens);
//	meandens /= m_pOriginalMesh->size_of_vertices();
//	m_pOriginalMesh->setMeanDensity(meandens);
//	delete []density;
//}
//
//void CSurfaceData::save_boundary_edges()
//{
//	QString fileName = "./domain/domain.fea";
//	m_pOriginalMesh->save_boundary_edges(fileName);
//}
//
//void CSurfaceData::save_domain()
//{
//	QFile file("./domain/domain.obj");
//	if(file.open(QFile::WriteOnly))
//	{
//		QTextStream out(&file);
//		//out.setRealNumberPrecision(10);
//		QString text;
//		out << "# OBJ file format with ext .obj" << endl;
//		text = "# vertex count = ";
//		text.append(QString::number(sample_num, 'g', 10));
//		out << text << endl;
//		text = "# face count = ";
//		text.append(QString::number(m_pOriginalMesh->size_of_facets(), 10));
//		out << text << endl;
//
//		vector<Point_2> convex_hull;
//		get_convex_hull(domain, sample_num, convex_hull);
//		Vector_2 center(0, 0);
//		for(int i=0; i<convex_hull.size(); i++)
//		{
//			center = Vector_2(center.x()+convex_hull[i].x(), center.y()+convex_hull[i].y());
//		}
//		center = center/convex_hull.size();
//		double radius = 0;
//		for(int i=0; i<convex_hull.size(); i++)
//		{
//			Vector_2 dir(convex_hull[i].x() - center.x(), convex_hull[i].y() - center.y());
//			if (radius<dir.squared_length())
//				radius=dir.squared_length();
//		}
//		radius = sqrt(radius);
//		if(!domain_z)
//			domain_z = new double[sample_num];
//		for(int i=0; i<sample_num; i++)
//		{
//			double z;
//			if(sample_num>5000)
//			{
//				//z = double(rand() % 11)/sample_num*40;
//				domain_z[i] = -5*radius+sqrt(36*radius*radius-(domain[i].x()-center.x())*(domain[i].x()-center.x())-(domain[i].y()-center.y())*(domain[i].y()-center.y()));
//			}
//			else
//			{
//				//z = double(rand() % 11)/100;
//				domain_z[i] = -5*radius+sqrt(36*radius*radius-(domain[i].x()-center.x())*(domain[i].x()-center.x())-(domain[i].y()-center.y())*(domain[i].y()-center.y()));
//			}
//			/*QString str = "Radius is ";
//			str.append(QString::number(radius));
//			str.append("Center is");
//			str.append(QString::number(center.x()));
//			str.append(QString::number(center.y()));
//			str.append("Z is ");
//			str.append(QString::number(domain_z[i]));
//
//			QMessageBox::information(NULL, "Error of Fitted Surface", str, QMessageBox::Yes, QMessageBox::Yes);*/
//
//			out << "v " << domain[i].x() << " " << domain[i].y() << " " << domain_z[i] << endl;
//		}
//		Polyhedron::Facet_iterator pFacet = m_pOriginalMesh->facets_begin(), pFacet_end = m_pOriginalMesh->facets_end();
//		for(;pFacet != pFacet_end;pFacet++)
//		{
//			Polyhedron::Halfedge_around_facet_circulator pHalfedge = pFacet->facet_begin();
//			out << "f ";
//			int i = 0;
//			do
//			{
//				int index = distance(m_pOriginalMesh->vertices_begin(), pHalfedge->vertex()) + 1;
//				if(m_pOriginalMesh->is_pure_triangle())
//				{
//					if(i==2)
//						out << index << endl;
//					else
//						out << index << " ";
//				}
//				else
//				{
//					if(i==3)
//						out << index << endl;
//					else
//						out << index << " ";
//				}
//				i++;
//			}
//			while(++pHalfedge != pFacet->facet_begin());
//		}
//		file.close();
//	}
//}
//
//void CSurfaceData::knots_generation()
//{
//	QFile file("./domain/domain.bat");
//	if(file.open(QFile::WriteOnly))
//	{
//		QTextStream out(&file);
//		//out.setRealNumberPrecision(10);
//		QString text = "gx_ccvt.exe domain.obj -gamma 3 -nb_pts ";
//		text.append(QString::number(nknots, 10));
//		text.append(" -nb_iter 50");
//		out << text ;
//		file.close();
//	}
//}
//
//void CSurfaceData::add_knot_max()
//{
//	if(!error)
//		compute_error();
//
//	/*if(iter_num==1)
//	{
//		for(int j=0; j<bInfo.size(); j++)
//		{
//			pos_added_indices.push_back(bInfo[j].mesh_ind);
//		}
//	}*/
//
//	/*vector<double> errors;
//
//	for(int i=0; i<sample_num; i++)
//	{
//		errors.push_back(error[i]);
//	}
//
//	std::sort(errors.begin(), errors.end(), greater<double>());
//	vector<unsigned> indices;
//	for(int i=0; i<sample_num; i++)
//	{
//		for(int j=0; j<sample_num; j++)
//		{
//			if(abs(errors[i]-error[j])<1e-100)
//			{
//				indices.push_back(j);
//				break;
//			}
//		}
//	}
//
//	bool badd = true;
//	for(int i=0; i<sample_num; i++)
//	{
//		for(int j=0; j<pos_added_indices.size(); j++)
//		{
//			if(indices[i]==pos_added_indices[j])
//			{
//				badd = false;
//				break;
//			}
//		}
//		
//		if(badd)
//		{
//			pos_added_indices.push_back(indices[i]);
//			knots.push_back(domain[indices[i]]);
//			nknots++;
//			break;
//		}
//	}*/
//}
//
//void CSurfaceData::add_knots(int num)
//{
//	nseed += num;
//}
//
//void CSurfaceData::random_knots(int num)
//{
//	vector<Index_Density> vec;
//	Polyhedron::Vertex_iterator vit = m_pOriginalMesh->vertices_begin();
//	for(int i=0; i<sample_num; i++)
//	{
//		Index_Density id;
//		id.index = i;
//		id.density = vit->vertex_density();
//		vec.push_back(id);
//		vit++;
//	}
//	ID_Vec idv;
//	idv.vec = vec;
//	idv.sort();
//	vec = idv.vec;
//
//	vector<Point_2> convex_hull;
//	get_convex_hull(domain, sample_num, convex_hull);
//	Vector_2 center;
//	for(int i=0; i<convex_hull.size(); i++)
//	{
//		center = Vector_2(center.x()+convex_hull[i].x(), center.y()+convex_hull[i].y());
//	}
//	center = center/convex_hull.size();
//	
//	CGAL::Random_points_in_square_2<Point_2> g(abs(center.x()-convex_hull[0].x()));
//	double radius = 0;
//	for(int i=0; i<convex_hull.size(); i++)
//	{
//		Vector_2 dir(convex_hull[i].x() - center.x(), convex_hull[i].y() - center.y());
//		if (radius<dir.squared_length())
//			radius=dir.squared_length();
//	}
//	radius = sqrt(radius);
//
//	QFile file("./domain/initial.pts");
//	int index = 0;
//	if(file.open(QFile::WriteOnly))
//	{
//		QTextStream out(&file);
//		out << num << endl;
//		double x, y, z;
//		
//		for(int i=0; i<num/2; )
//		{
//			index = rand() % sample_num;
//			if(vec[index].density>1e-10)
//			{
//				x = domain[vec[index].index].x();
//				if(x <center.x())
//				{
//				y = domain[vec[index].index].y();
//				z = -5*radius+sqrt(36*radius*radius-(x-center.x())*(x-center.x())-(y-center.y())*(y-center.y()));
//				out << x << " " <<  y << " " << z <<endl;
//				i++;
//				}
//			}
//		}
//		for(int i=0; i<num/2; )
//		{
//			index = rand() % sample_num;
//			if(vec[index].density>1e-10)
//			{
//				x = domain[vec[index].index].x();
//				if(x >center.x())
//				{
//				y = domain[vec[index].index].y();
//				z = -5*radius+sqrt(36*radius*radius-(x-center.x())*(x-center.x())-(y-center.y())*(y-center.y()));
//				out << x << " " <<  y << " " << z <<endl;
//				i++;
//				}
//			}
//		}
//		file.close();
//	}
//}
//
void CSurfaceData::compute_box()
{
	Mesh::TexCoord2D   bbMin, bbMax;

	bbMin = bbMax = domain[0];
	for (int i=1;i!=sample_num; ++i)
	{
		bbMin.minimize(domain[i]);
		bbMax.maximize(domain[i]);
	}
	Bbox_2 box_(bbMin[0],bbMin[1],bbMax[0],bbMax[1]);
    box=box_;
}

//void CSurfaceData::compute_error()
//{
//	max_err.error = 0;
//	max_err.index = -1;
//	mean_err = 0;
//	double min_error = 1e16;
//	if(!error)
//		error = new double[sample_num];
//
//	Iso_cuboid cube = m_pOriginalMesh->bbox();
//	double max_length = 0;
//	max_length = max(cube.xmax()-cube.xmin(), cube.ymax()-cube.ymin());
//	max_length = max(max_length, cube.zmax()-cube.zmin());
//
//	Polyhedron::Vertex_iterator v_it1 = m_pOriginalMesh->vertices_begin(), v_end1 = m_pOriginalMesh->vertices_end();
//	Polyhedron::Vertex_iterator v_it2 = m_pFittedMesh->vertices_begin(), v_end2 = m_pFittedMesh->vertices_end();
//	int i = 0;
//	for (; v_it1!=v_end1 && v_it2!=v_end2; v_it1++, v_it2++)
//	{
//		Point_3 p1 = Point_3(v_it1->point().x(), v_it1->point().y(), v_it1->point().z());
//		Point_3 p2 =  Point_3(v_it2->point().x(), v_it2->point().y(), v_it2->point().z());
//		Vector_3 vec = p1 - p2;
//		error[i] = vec.squared_length();
//		mean_err += error[i];
//		error[i] = sqrt(error[i]);
//		i++;
//	}
//	v_it1 = m_pOriginalMesh->vertices_begin();
//	for(int i=0; i<sample_num; i++)
//	{
//		error[i] /= max_length;
//		v_it1->set_error(error[i]);
//		v_it1++;
//	}
//
//	for(int i=0; i<sample_num; i++)
//	{
//		if(max_err.error<error[i])
//		{
//			max_err.error = error[i];
//			max_err.index = i;
//		}
//	}
//	
//	mean_err /= sample_num;
//	mean_err = sqrt(mean_err);
//	mean_e = mean_err;
//	mean_err /= max_length;
//}
//
//void CSurfaceData::update_domain_color(int index)
//{
//	double vcolor[3];
//	int h1, s1, v1;
//	int h2, s2, v2;
//	if(index==0)
//	{
//		{
//			int color[3];
//			color[0] = 127;
//			color[1] = 0;
//			color[2] = 0;
//			QColor d_light(color[0], color[1], color[2]);
//
//			color[0] = 0;
//			color[1] = 0;
//			color[2] = 127;
//			QColor d_dark(color[0], color[1], color[2]);
//			d_light.getHsv( &h1, &s1, &v1 );
//			d_dark.getHsv( &h2, &s2, &v2 );
//		}
//		Polyhedron::Vertex_iterator dit = m_pDomainMesh->vertices_begin();
//		int i=0;
//		for(; dit!=m_pDomainMesh->vertices_end(); dit++)
//		{
//			double ratio = error[i]/(max_err.error+1e-10);
//			QColor c;
//			c.setHsv( h2 + qRound( ratio * ( h1 - h2 ) ),
//			s2 + qRound( ratio * ( s1 - s2 ) ),
//			v2 + qRound( ratio * ( v1 - v2 ) ) );
//
//			int color[3];
//			c.getRgb(&color[0], &color[1], &color[2]);
//			vcolor[0] = color[0]/255.0;
//			vcolor[1] = color[1]/255.0;
//			vcolor[2] = color[2]/255.0;
//			dit->set_color(vcolor);
//			i++;
//		}
//	}
//	else
//	{
//		{
//			int color[3];
//			color[0] = 250;
//			color[1] = 0;
//			color[2] = 250;
//			QColor d_light(color[0], color[1], color[2]);
//
//			color[0] = 0;
//			color[1] = 127;
//			color[2] = 0;
//			QColor d_dark(color[0], color[1], color[2]);
//			d_light.getHsv( &h1, &s1, &v1 );
//			d_dark.getHsv( &h2, &s2, &v2 );
//		}
//		
//		int i=0;
//		Polyhedron::Vertex_iterator vit = m_pDomainMesh->vertices_begin();
//		Polyhedron::Vertex_iterator vit1 = m_pOriginalMesh->vertices_begin();
//		for(; vit!=m_pDomainMesh->vertices_end(); vit++)
//		{
//			double ratio = vit1->vertex_density()/(m_pOriginalMesh->getTruncateMaxDensity()-m_pOriginalMesh->getMinDensity());
//			if(ratio>1)
//				ratio=1;
//			QColor c;
//			c.setHsv( h2 + qRound( ratio * ( h1 - h2 ) ),
//			s2 + qRound( ratio * ( s1 - s2 ) ),
//			v2 + qRound( ratio * ( v1 - v2 ) ) );
//
//			int color[3];
//			c.getRgb(&color[0], &color[1], &color[2]);
//			vcolor[0] = color[0]/255.0;
//			vcolor[1] = color[1]/255.0;
//			vcolor[2] = color[2]/255.0;
//			vit->set_color(vcolor);
//			i++;
//			vit1++;
//		}
//	}
//}
//
//double *CSurfaceData::get_error()
//{
//	return error;
//}
//
//double &CSurfaceData::get_mean_error()
//{
//	return mean_err;
//}
//
//Max_Error &CSurfaceData::get_max_error()
//{
//	return max_err;
//}
//
//void CSurfaceData::triangulation()
//{
//	cdt_knotstri.set_knots_input(bknots_input);
//	if(!bknots_input)
//	{
//		if(iter_num==0)
//		{
//			clock_t start = clock(), finish;
//			q.parse(m_pOriginalMesh);
//			q.set_domain(domain);
//			q.initial_quadrics();
//			q.construct_n_contract(nseed);
//			finish = clock();
//			simplified_time = (double(finish-start))/CLOCKS_PER_SEC; 
//			q.simplified_mesh();
//			centroid = q.get_knots();
//			knots_triangulation();
//		}
//		/*else
//		{
//			clear_prev_data();
//			q.progressive_mesh(error, 1e-3);
//			simplified_time = 0;
//		}*/
//		else
//		{
//			simplified_time = 0;
//			clear_prev_data();
//			cdt_knotstri.link_triangulation_procedure(degree, isBoundary);
//			cdt_knotstri.compute_all_basis();
//		}
//	}
//	else
//	{
//		knots.clear();
//		clear_prev_data();
//		read_knots();
//		nknots = knots.size();
//
//		vector<Knot> pts;
//		for(int i=0; i<nknots; i++)
//		{
//			pts.push_back(knots[i]);
//		}
//	
//		cdt_knotstri.set_points(pts);
//		cdt_knotstri.set_mesh(m_pOriginalMesh);
//		get_domain_mesh();
//		cdt_knotstri.set_domain_mesh(m_pDomainMesh);
//		cdt_knotstri.set_domain(domain);
//		cdt_knotstri.set_type(type);
//		cdt_knotstri.link_triangulation_procedure(degree, isBoundary);
//		cdt_knotstri.compute_all_basis();
//	}	
//}
//
//void CSurfaceData::knots_triangulation()
//{
//	int r = sample_num;
//	
//	assemble_points();
//
//	srand(10);
//	double tol = 1/(3*1e5);
//	int n;
//	for(int i=0; i<knots.size(); i++)
//	{
//		if((abs(knots[i].pt.x()-1)<tol || abs(knots[i].pt.x())<tol) && !(abs(knots[i].pt.y()-1)<tol || abs(knots[i].pt.y())<tol))
//		{
//			knots[i].pt = Point_2(knots[i].pt.x(), knots[i].pt.y()+tol);
//		}
//		else
//		{
//			if((abs(knots[i].pt.y()-1)<tol || abs(knots[i].pt.y())<tol) && !(abs(knots[i].pt.x()-1)<tol || abs(knots[i].pt.x())<tol))
//			{
//				knots[i].pt = Point_2(knots[i].pt.x()+tol, knots[i].pt.y());
//			}
//			else
//			{
//				if(knots[i].pt.x()>0 && knots[i].pt.x()<1 && knots[i].pt.y()>0 && knots[i].pt.y()<1)
//				{
//					
//					n = rand()%1000+2;
//					double x = tol/n;
//					knots[i].pt = Point_2(knots[i].pt.x()+x, knots[i].pt.y()+x);
//				}
//			}
//		}
//	}
//
//	for(vector<Knot>::iterator it = knots.begin(); it!=knots.end(); it++)
//	{
//		vector<Knot>::iterator in_it = it;
//		in_it++;
//		for(; in_it!=knots.end();)
//		{
//			Vector_2 vec = in_it->pt - it->pt;
//			if(vec.squared_length()<1e-100)
//			{
//				in_it = knots.erase(in_it);
//			}
//			else
//			{
//				in_it++;
//			}
//		}
//	}
//
//	nknots = knots.size();
//
//	vector<Knot> pts;
//	for(int i=0; i<nknots; i++)
//	{
//		pts.push_back(knots[i]);
//	}
//	
//	cdt_knotstri.set_points(pts);
//	cdt_knotstri.set_mesh(m_pOriginalMesh);
//	get_domain_mesh();
//	cdt_knotstri.set_domain_mesh(m_pDomainMesh);
//	cdt_knotstri.set_domain(domain);
//	cdt_knotstri.set_type(type);
//	cdt_knotstri.link_triangulation_procedure(degree, isBoundary);
//	cdt_knotstri.compute_all_basis();
//}
//
//void CSurfaceData::assemble_points()
//{
//	vector<Point_2> out;
//	vector<unsigned> indices = get_convex_hull(domain, sample_num, out);
//	int n = out.size();
//	double tol = 1e-100;
//
//	for(int i=0; i<centroid.size(); i++)
//	{
//		bool badd = true;
//		if(abs(centroid[i].pt.x())<tol)
//		{
//			if(abs(centroid[i].pt.y())<tol || abs(centroid[i].pt.y()-1)<tol)
//				badd = false;
//		}
//		else
//		{
//			if(abs(centroid[i].pt.x()-1)<tol)
//			{
//				if(abs(centroid[i].pt.y())<tol || abs(centroid[i].pt.y()-1)<tol)
//					badd = false;
//			}
//		}
//		if(badd)
//			knots.push_back(centroid[i]);
//	}
//
//#if 1
//	int sz = knots.size();
//	nknots = sz;
//	Polyhedron::Vertex_iterator start = m_pOriginalMesh->vertices_begin(), vit;
//	if(isBoundary)
//	{
//		for(int i=0; i<n; i++)
//		{
//			double x = out[i].x();
//			double y = out[i].y();
//			bool badd = true;
//			for(int j=0; j<knots.size(); j++)
//			{
//				Vector_2 vec = out[i] - knots[j].pt;
//				if(vec.squared_length()<1e-100)
//				{
//					knots[j].pt = out[i];
//					badd = false;
//					break;
//				}
//			}
//			if(badd)
//			{
//				Knot knot;
//				knot.pt = out[i];
//				knot.is_border = true;
//				for(int j=0; j<sample_num; j++)
//				{
//					Vector_2 vec = out[i]-domain[j];
//					if(vec.squared_length()<1e-100)
//					{
//						vit = start;
//						advance(vit, j);
//						knot.vertex = Point_3(vit->point().x(), vit->point().y(), vit->point().z());
//						break;
//					}
//				}
//				knots.push_back(knot);
//				nknots++;
//			}
//		}
//	}
//	else
//	{
//		nknots = nseed;
//	}
//#endif
//}
//
//vector<unsigned> CSurfaceData::get_convex_hull(Point_2 *knots, int num, vector<Point_2>&out)
//{
//	vector<Point_2> vp;
//	/*for(int i=0; i<num; i++)
//	{
//		Point_2 pt(knots[i].x(), knots[i].y());
//		vp.push_back(pt);
//	}*/
//	//CGAL::convex_hull_points_2(vp.begin(), vp.end(), back_inserter(out));
//	//CGAL::convex_hull_2( vp.begin(), vp.end(),back_inserter(out) );
//	CGAL::convex_hull_2( knots, knots+num, back_inserter(out) );
//	vector<unsigned> indices;
//	for(int i=0; i<out.size(); i++)
//	{
//		for(int j=0; j<sample_num; j++)
//		{
//			Vector_2 v = knots[j] - out[i];
//			if(v.squared_length()<1e-100)
//			{
//				indices.push_back(j);
//				break;
//			}
//		}
//	}
//	return indices;
//}
//
//int &CSurfaceData::get_nseed()
//{
//	return nseed;
//}
//
//int &CSurfaceData::get_nknots()
//{
//	return nknots;
//}
//
//void CSurfaceData::set_nseed(int &n)
//{
//	nknots = n;
//	nseed = n;
//}
//
//void CSurfaceData::set_degree(int &n)
//{
//	degree = n;
//}
//
//vector<CentroidTriangulation> &CSurfaceData::get_centroid_points()
//{
//	return cdt_knotstri.get_centroid_points();
//}
//
//vector<vector<unsigned>> &CSurfaceData::get_centroidtrianglesk_1()
//{
//	return cdt_knotstri.get_centroidtrianglesk_1();
//}
//
//vector<vector<unsigned>> &CSurfaceData::get_centroidtrianglesk_2()
//{
//	return cdt_knotstri.get_centroidtrianglesk_2();
//}
//
Bbox_2 &CSurfaceData::get_box()
{
	return box;
}

//Polyhedron *CSurfaceData::get_basis_sum_polyhedron()
//{
//	if(sample_num == 0)
//	{
//		return false;
//	}
//	if(!m_pBasissumMesh)
//	{
//		m_pBasissumMesh = new Polyhedron;
//		*m_pBasissumMesh = *m_pOriginalMesh;
//	}
//	else
//	{
//		return m_pBasissumMesh;
//	}
//	double *basis_sum = new double[sample_num];
//	for(int i=0; i<sample_num; i++)
//	{
//		basis_sum[i] = 0;
//	}
//
//	vector<SplineBasis> basisCollection = cdt_knotstri.get_basis_collection();
//	for(int i=0; i<basisCollection.size(); i++)
//	{
//		int index_sz = basisCollection[i].indices.size();
//		for(int j=0; j<index_sz; j++)
//		{
//			basis_sum[basisCollection[i].indices[j]] += basisCollection[i].basis[j];
//		}
//	}
//	
//	Polyhedron::Vertex_iterator vit = m_pBasissumMesh->vertices_begin();
//	int i=0;
//	double vcolor[3];
//	int h1, s1, v1;
//    int h2, s2, v2;
//	{
//		int color[3];
//		color[0] = 127;
//		color[1] = 0;
//		color[2] = 0;
//		QColor d_light(color[0], color[1], color[2]);
//
//		color[0] = 0;
//		color[1] = 0;
//		color[2] = 127;
//		QColor d_dark(color[0], color[1], color[2]);
//		d_light.getHsv( &h1, &s1, &v1 );
//		d_dark.getHsv( &h2, &s2, &v2 );
//	}
//	for(; vit!=m_pBasissumMesh->vertices_end(); vit++)
//	{
//		//vit->vertex_color
//		vit->point() = Polyhedron::Point_3(domain[i].x(), domain[i].y(), basis_sum[i]);
//		QColor c;
//		c.setHsv( h2 + qRound( basis_sum[i] * ( h1 - h2 ) ),
//            s2 + qRound( basis_sum[i] * ( s1 - s2 ) ),
//            v2 + qRound( basis_sum[i] * ( v1 - v2 ) ) );
//
//		int color[3];
//		c.getRgb(&color[0], &color[1], &color[2]);
//		vcolor[0] = color[0]/255.0;
//		vcolor[1] = color[1]/255.0;
//		vcolor[2] = color[2]/255.0;
//		vit->set_color(vcolor);
//		i++;
//	}
//	m_pBasissumMesh->compute_bounding_box();
//	delete []basis_sum;
//	return m_pBasissumMesh;
//}
//
//Point_3 *CSurfaceData::get_control_vertices()
//{
//	return cdt_knotstri.get_control_vertices();
//}
//
//Point_3 *CSurfaceData::get_adjusted_control_vertices()
//{
//	if(!adjusted_control_vertices)
//	{
//		int sz = cdt_knotstri.get_basis_size();
//		adjusted_control_vertices = new Point_3[sz];
//		Point_3 *control_vertices = cdt_knotstri.get_control_vertices();
//		for(int i=0; i<sz; i++)
//		{
//			adjusted_control_vertices[i] = control_vertices[i];
//		}
//	}
//	return adjusted_control_vertices;
//}
//
//int CSurfaceData::get_basis_size()
//{
//	return cdt_knotstri.get_basis_size();
//}
//
//Polyhedron *CSurfaceData::get_basis_polyhedron(int &index)
//{
//	if(sample_num == 0)
//	{
//		return NULL;
//	}
//	if(m_pBasisMesh==NULL)
//	{
//		m_pBasisMesh = new Polyhedron;
//		*m_pBasisMesh = *m_pOriginalMesh;
//
//		double *basis_mesh = new double[3*sample_num];
//	
//		for(int i=0; i<sample_num; i++)
//		{
//			basis_mesh[3*i] = domain[i].x();
//			basis_mesh[3*i+1] = domain[i].y();
//			basis_mesh[3*i+2] = 0;//basisCollection[index].basis[i];
//		}
//
//		vector<SplineBasis> basisCollection = cdt_knotstri.get_basis_collection();
//		int sz = basisCollection[index].indices.size();
//		for(int i=0; i<sz; i++)
//		{
//			basis_mesh[3*basisCollection[index].indices[i]+2] = basisCollection[index].basis[i];
//		}
//
//		Polyhedron::Vertex_iterator vit = m_pBasisMesh->vertices_begin();
//		int i=0;
//		double vcolor[3];
//		int h1, s1, v1;
//		int h2, s2, v2;
//		{
//			int color[3];
//			color[0] = 127;
//			color[1] = 0;
//			color[2] = 0;
//			QColor d_light(color[0], color[1], color[2]);
//
//			color[0] = 0;
//			color[1] = 0;
//			color[2] = 127;
//			QColor d_dark(color[0], color[1], color[2]);
//			d_light.getHsv( &h1, &s1, &v1 );
//			d_dark.getHsv( &h2, &s2, &v2 );
//		}
//		for(; vit!=m_pBasisMesh->vertices_end(); vit++)
//		{
//			vit->point() = Polyhedron::Point_3(basis_mesh[3*i], basis_mesh[3*i+1], basis_mesh[3*i+2]);
//			QColor c;
//			c.setHsv( h2 + qRound( basis_mesh[3*i+2] * ( h1 - h2 ) ),
//            s2 + qRound( basis_mesh[3*i+2] * ( s1 - s2 ) ),
//            v2 + qRound( basis_mesh[3*i+2] * ( v1 - v2 ) ) );
//
//			int color[3];
//			c.getRgb(&color[0], &color[1], &color[2]);
//			vcolor[0] = color[0]/255.0;
//			vcolor[1] = color[1]/255.0;
//			vcolor[2] = color[2]/255.0;
//			vit->set_color(vcolor);
//			i++;
//		}
//		m_pBasisMesh->compute_bounding_box();
//		delete []basis_mesh;
//		basis_index = index;
//	}
//	else
//	{
//		if(basis_index!=index)
//		{
//			double *zBasis = new double[sample_num];
//			for(int j=0; j<sample_num; j++)
//			{
//				zBasis[j] = 0;
//			}
//			vector<SplineBasis> basisCollection = cdt_knotstri.get_basis_collection();
//			for(int j=0; j<basisCollection[index].indices.size(); j++)
//			{
//				zBasis[basisCollection[index].indices[j]] = basisCollection[index].basis[j];
//			}
//			int i = 0;
//			Polyhedron::Vertex_iterator vit = m_pBasisMesh->vertices_begin();
//			for(; vit!=m_pBasisMesh->vertices_end(); vit++)
//			{
//				vit->point() = Polyhedron::Point_3(domain[i].x(), domain[i].y(), zBasis[i]);
//				i++;
//			}
//			basis_index = index;
//			delete []zBasis;
//		}
//	}
//
//	return m_pBasisMesh;
//}
//
//void CSurfaceData::set_domain_color(int flag)
//{
//	Polyhedron::Vertex_iterator dit = m_pDomainMesh->vertices_begin();
//	if(flag==0)//density
//	{
//		double vcolor[3];
//		int h1, s1, v1;
//		int h2, s2, v2;
//		{
//			int color[3];
//			color[0] = 250;
//			color[1] = 0;
//			color[2] = 250;
//			QColor d_light(color[0], color[1], color[2]);
//
//			color[0] = 0;
//			color[1] = 127;
//			color[2] = 0;
//			QColor d_dark(color[0], color[1], color[2]);
//			d_light.getHsv( &h1, &s1, &v1 );
//			d_dark.getHsv( &h2, &s2, &v2 );
//		}
//		
//		int i=0;
//		Polyhedron::Vertex_iterator vit = m_pDomainMesh->vertices_begin();
//		Polyhedron::Vertex_iterator vit1 = m_pOriginalMesh->vertices_begin();
//		for(; vit!=m_pDomainMesh->vertices_end(); vit++)
//		{
//			double ratio = vit1->vertex_density()/(m_pOriginalMesh->getTruncateMaxDensity()-m_pOriginalMesh->getMinDensity());
//			if(ratio>1)
//				ratio=1;
//			QColor c;
//			c.setHsv( h2 + qRound( ratio * ( h1 - h2 ) ),
//			s2 + qRound( ratio * ( s1 - s2 ) ),
//			v2 + qRound( ratio * ( v1 - v2 ) ) );
//
//			int color[3];
//			c.getRgb(&color[0], &color[1], &color[2]);
//			vcolor[0] = color[0]/255.0;
//			vcolor[1] = color[1]/255.0;
//			vcolor[2] = color[2]/255.0;
//			vit->set_color(vcolor);
//			i++;
//			vit1++;
//		}
//	}
//	else
//	{
//		if(flag==1)//curvature
//		{
//			double vcolor[3];
//			int h1, s1, v1;
//			int h2, s2, v2;
//			{
//				int color[3];
//				color[0] = 250;
//				color[1] = 0;
//				color[2] = 250;
//				QColor d_light(color[0], color[1], color[2]);
//
//				color[0] = 127;
//				color[1] = 0;
//				color[2] = 0;
//				QColor d_dark(color[0], color[1], color[2]);
//				d_light.getHsv( &h1, &s1, &v1 );
//				d_dark.getHsv( &h2, &s2, &v2 );
//			}
//		
//			double max_meancurvature = -1e100;
//			double min_meancurvature = 1e100;
//
//			Polyhedron::Vertex_iterator vit = m_pOriginalMesh->vertices_begin();
//			for(; vit!=m_pOriginalMesh->vertices_end(); vit++)
//			{
//				if(max_meancurvature<vit->mean_curvature())
//					max_meancurvature = vit->mean_curvature();
//				if(min_meancurvature>vit->mean_curvature())
//					min_meancurvature = vit->mean_curvature();
//			}
//
//			vit = m_pOriginalMesh->vertices_begin();
//			for(; vit!=m_pOriginalMesh->vertices_end(); vit++)
//			{
//				double ratio = (vit->mean_curvature()-min_meancurvature)/(max_meancurvature-min_meancurvature);
//				QColor c;
//
//				c.setHsv( h2 + qRound( ratio * ( h1 - h2 ) ),
//					s2 + qRound( ratio * ( s1 - s2 ) ),
//					v2 + qRound( ratio * ( v1 - v2 ) ) );
//
//				int color[3];
//				c.getRgb(&color[0], &color[1], &color[2]);
//				vcolor[0] = color[0]/255.0;
//				vcolor[1] = color[1]/255.0;
//				vcolor[2] = color[2]/255.0;
//				dit->set_color(vcolor);
//				dit++;
//			}
//		}
//		else
//		{
//			if(error==NULL)
//				return;
//			double vcolor[3];
//			int h1, s1, v1;
//			int h2, s2, v2;
//			{
//				int color[3];
//				color[0] = 127;
//				color[1] = 0;
//				color[2] = 0;
//				QColor d_light(color[0], color[1], color[2]);
//
//				color[0] = 0;
//				color[1] = 0;
//				color[2] = 127;
//				QColor d_dark(color[0], color[1], color[2]);
//				d_light.getHsv( &h1, &s1, &v1 );
//				d_dark.getHsv( &h2, &s2, &v2 );
//			}
//			Polyhedron::Vertex_iterator dit = m_pDomainMesh->vertices_begin();
//			int i=0;
//			for(; dit!=m_pDomainMesh->vertices_end(); dit++)
//			{
//				double ratio = error[i]/(max_err.error+1e-10);
//				QColor c;
//				c.setHsv( h2 + qRound( ratio * ( h1 - h2 ) ),
//				s2 + qRound( ratio * ( s1 - s2 ) ),
//				v2 + qRound( ratio * ( v1 - v2 ) ) );
//
//				int color[3];
//				c.getRgb(&color[0], &color[1], &color[2]);
//				vcolor[0] = color[0]/255.0;
//				vcolor[1] = color[1]/255.0;
//				vcolor[2] = color[2]/255.0;
//				dit->set_color(vcolor);
//				i++;
//			}
//		}
//	}
//}
//
//void CSurfaceData::update_density_color()
//{
//	if(!m_pDensityMesh)
//	{
//		m_pDensityMesh = new Polyhedron;
//		*m_pDensityMesh = *m_pOriginalMesh;
//	}
//	if(bmaxdens_changed)
//	{
//		double vcolor[3];
//		int h1, s1, v1;
//		int h2, s2, v2;
//		{
//			int color[3];
//			color[0] = 250;
//			color[1] = 0;
//			color[2] = 250;
//			QColor d_light(color[0], color[1], color[2]);
//
//			color[0] = 0;
//			color[1] = 127;
//			color[2] = 0;
//			QColor d_dark(color[0], color[1], color[2]);
//			d_light.getHsv( &h1, &s1, &v1 );
//			d_dark.getHsv( &h2, &s2, &v2 );
//		}
//		
//		int i=0;
//		Polyhedron::Vertex_iterator vit = m_pDensityMesh->vertices_begin();
//		for(; vit!=m_pDensityMesh->vertices_end(); vit++)
//		{
//			double ratio = vit->vertex_density()/(m_pOriginalMesh->getTruncateMaxDensity()-m_pOriginalMesh->getMinDensity());
//			if(ratio>1)
//				ratio=1;
//			QColor c;
//			c.setHsv( h2 + qRound( ratio * ( h1 - h2 ) ),
//			s2 + qRound( ratio * ( s1 - s2 ) ),
//			v2 + qRound( ratio * ( v1 - v2 ) ) );
//
//			int color[3];
//			c.getRgb(&color[0], &color[1], &color[2]);
//			vcolor[0] = color[0]/255.0;
//			vcolor[1] = color[1]/255.0;
//			vcolor[2] = color[2]/255.0;
//			vit->set_color(vcolor);
//			i++;
//		}
//	}
//}
//
//void CSurfaceData::update_curvature_color()
//{
//	double vcolor[3];
//	int h1, s1, v1;
//	int h2, s2, v2;
//	{
//		int color[3];
//		color[0] = 250;
//		color[1] = 0;
//		color[2] = 250;
//		QColor d_light(color[0], color[1], color[2]);
//
//		color[0] = 127;
//		color[1] = 0;
//		color[2] = 0;
//		QColor d_dark(color[0], color[1], color[2]);
//		d_light.getHsv( &h1, &s1, &v1 );
//		d_dark.getHsv( &h2, &s2, &v2 );
//	}
//		
//	double max_meancurvature = -1e100;
//	double min_meancurvature = 1e100;
//
//	Polyhedron::Vertex_iterator vit = m_pOriginalMesh->vertices_begin();
//	for(; vit!=m_pOriginalMesh->vertices_end(); vit++)
//	{
//		if(max_meancurvature<vit->mean_curvature())
//			max_meancurvature = vit->mean_curvature();
//		if(min_meancurvature>vit->mean_curvature())
//			min_meancurvature = vit->mean_curvature();
//	}
//
//	int i=0;
//	vit = m_pOriginalMesh->vertices_begin();
//	/*Polyhedron::Vertex_iterator dit = m_pDomainMesh->vertices_begin();*/
//	for(; vit!=m_pOriginalMesh->vertices_end(); vit++)
//	{
//		double ratio = (vit->mean_curvature()-min_meancurvature)/(max_meancurvature-min_meancurvature);
//		QColor c;
//		/*c.setHsv( h1 + qRound( ratio * ( h2 - h1 ) ),
//        s1 + qRound( ratio * ( s2 - s1 ) ),
//        v1 + qRound( ratio * ( v2 - v1 ) ) );*/
//
//		c.setHsv( h2 + qRound( ratio * ( h1 - h2 ) ),
//            s2 + qRound( ratio * ( s1 - s2 ) ),
//            v2 + qRound( ratio * ( v1 - v2 ) ) );
//
//		int color[3];
//		c.getRgb(&color[0], &color[1], &color[2]);
//		vcolor[0] = color[0]/255.0;
//		vcolor[1] = color[1]/255.0;
//		vcolor[2] = color[2]/255.0;
//		vit->set_color(vcolor);
//		/*dit->set_color(vcolor);
//		dit++;*/
//		i++;
//	}
//}
//
//double **CSurfaceData::get_controlvertices_color()
//{
//	if(!controlvertices_color)
//	{
//		int basis_size = cdt_knotstri.get_basis_size();
//		controlvertices_color = new double*[basis_size];
//		for(int i=0; i<basis_size; i++)
//		{
//			controlvertices_color[i] = new double[3];
//			controlvertices_color[i][0] = 0.0;
//			controlvertices_color[i][1] = 0.0;
//			controlvertices_color[i][2] = 1.0;
//		}
//	}
//	return controlvertices_color;
//}
//
//void CSurfaceData::set_max_error(double &err)
//{
//	if(err_threshold!=err)
//	{
//		err_threshold = err;
//		if(!error)
//			return;
//		if(!m_pFittedMesh)
//		{
//			*m_pErrorMesh = *m_pFittedMesh;
//			return;
//		}
//		else
//		{
//			if(!m_pErrorMesh)
//			{
//				m_pErrorMesh = new Polyhedron;
//				*m_pErrorMesh = *m_pFittedMesh;
//				m_pErrorMesh->compute_type();
//			}
//		}
//		Polyhedron::Vertex_iterator vit = m_pErrorMesh->vertices_begin();
//		int i=0;
//		double vcolor[3];
//		int h1, s1, v1;
//		int h2, s2, v2;
//		{
//			int color[3];
//			color[0] = 127;
//			color[1] = 0;
//			color[2] = 0;
//			QColor d_light(color[0], color[1], color[2]);
//
//			color[0] = 0;
//			color[1] = 0;
//			color[2] = 127;
//			QColor d_dark(color[0], color[1], color[2]);
//			d_light.getHsv( &h1, &s1, &v1 );
//			d_dark.getHsv( &h2, &s2, &v2 );
//		}
//		for(; vit!=m_pErrorMesh->vertices_end(); vit++)
//		{
//			QColor c;
//			double ratio = error[i]/err_threshold;
//			ratio = ratio>1?1:ratio;
//			c.setHsv( h2 + qRound( ratio * ( h1 - h2 ) ),
//            s2 + qRound( ratio * ( s1 - s2 ) ),
//            v2 + qRound( ratio * ( v1 - v2 ) ) );
//
//			int color[3];
//			c.getRgb(&color[0], &color[1], &color[2]);
//			vcolor[0] = color[0]/255.0;
//			vcolor[1] = color[1]/255.0;
//			vcolor[2] = color[2]/255.0;
//			vit->set_color(vcolor);
//			i++;
//		}
//	}
//}
//
//void CSurfaceData::set_max_density(double &ratio)
//{
//	m_pOriginalMesh->setTruncateMaxDensity(ratio);
//	update_density_color();
//}
//
//vector<Edge> &CSurfaceData::get_control_edges()
//{
//	return cdt_knotstri.get_control_edges();
//}
//
//vector<Edge> &CSurfaceData::get_control_edges_auxiliary()
//{
//	return cdt_knotstri.get_auxiliary_edges();
//}
//
//Polyhedron *CSurfaceData::get_control_mesh()
//{
//	if(m_pControlMesh==NULL)
//	{
//		Point_3 *control_vertices = cdt_knotstri.get_control_vertices();
//		if(!control_vertices)
//			return NULL;
//		
//		vector<vector<unsigned>> &vertices_triangles = cdt_knotstri.get_vertices_triangles_space();
//		if(vertices_triangles.empty())
//			return NULL;
//		m_pControlMesh = new Polyhedron;
//		int basis_num = cdt_knotstri.get_basis_size();
//		Builder builder(control_vertices, vertices_triangles, basis_num);
//		m_pControlMesh->delegate(builder);
//		m_pControlMesh->compute_type();
//	}
//
//	return m_pControlMesh;
//}
//
//double  CSurfaceData::compute_min_size()
//{
//	double min_length = 1e100;
//	int sz = cdt_knotstri.get_basis_size();
//	for(int i=0; i<sz; i++)
//	{
//		for(int j=i+1; j<sz; j++)
//		{
//			Vector_3 vec = adjusted_control_vertices[i]-adjusted_control_vertices[j];
//			double length = vec.squared_length();
//			if(length<1e-16)
//			{
//				cout << i << " " << j << endl;
//			}
//			if(length<min_length && length>1e-10)
//				min_length = length;
//		}
//	}
//	//min_length = sqrt(min_length);
//	return min_length;
//}
//
//int CSurfaceData::check_selected(Point_3 &pt, double dist)
//{
//	double min_length = 1e100;;
//
//	int sz = cdt_knotstri.get_basis_size();
//	int ret = -1;
//	for(int i=0; i<sz; i++)
//	{
//		Vector_3 vec = adjusted_control_vertices[i] - pt;
//		if(vec.squared_length()<min_length)
//		{
//			ret = i;
//			min_length =  vec.squared_length();
//		}
//	}
//	if(min_length>dist)
//		ret = -1;
//	return ret;
//}
//
//void CSurfaceData::update_mesh(int index, Point_3 &npt)
//{
//	adjusted_control_vertices[index] = npt;
//	int ncol = cdt_knotstri.get_basis_size();
//	vector<SplineBasis> basisCollection = cdt_knotstri.get_basis_collection();
//	if(!m_pAdjustedMesh)
//	{
//		m_pAdjustedMesh = new Polyhedron;
//		*m_pAdjustedMesh = *m_pFittedMesh;
//		/*m_pAdjustedMesh->compute_index();
//		return;*/
//	}
//	
//	double *pts = new double[3*sample_num];
//	for(int i=0; i<3*sample_num; i++)
//	{
//		pts[i] = 0;
//	}
//	for(int j=0; j<ncol; j++)
//	{
//		int sz = basisCollection[j].indices.size();
//		for(int i=0; i<sz; i++)
//		{
//			int index = basisCollection[j].indices[i];
//			pts[3*index] += adjusted_control_vertices[j].x()*basisCollection[j].basis[i];
//			pts[3*index+1] += adjusted_control_vertices[j].y()*basisCollection[j].basis[i];
//			pts[3*index+2] += adjusted_control_vertices[j].z()*basisCollection[j].basis[i];
//		}
//	}
//	int i = 0;
//	Polyhedron::Vertex_iterator vit = m_pAdjustedMesh->vertices_begin();
//	for(; vit!=m_pAdjustedMesh->vertices_end(); vit++)
//	{
//		vit->point() = Polyhedron::Point_3(pts[3*i], pts[3*i+1], pts[3*i+2]);
//		i++;
//	}
//	delete []pts;
//	pts = NULL;
//}
//
//Polyhedron *CSurfaceData::get_adjusted_mesh()
//{
//	if(!m_pAdjustedMesh)
//	{
//		m_pAdjustedMesh = new Polyhedron;
//		if(m_pFittedMesh)
//			*m_pAdjustedMesh = *m_pFittedMesh;
//	}
//	return m_pAdjustedMesh;
//}
//
//vector<SplineBasis> &CSurfaceData::get_basis_collection()
//{
//	return cdt_knotstri.get_basis_collection();;
//}
//
//int CSurfaceData::triangular_test(vector<pair<unsigned, unsigned>> &samePairs)
//{
//	int count = 0;
//	vector<SplineBasis> basisCollection = cdt_knotstri.get_basis_collection();
//	vector<vector<unsigned>> vindices;
//	for(int i=0; i<basisCollection.size(); i++)
//	{
//		vector<unsigned> indices;
//		for (int j=0; j<basisCollection[i].boundaries.size(); j++)
//		{
//			bool hasMultiple = false;
//			for (int k=0; k<3; k++)
//			{
//				if(basisCollection[i].boundaries[j][k]==basisCollection[i].boundaries[j][(k+1)%3])
//				{
//					hasMultiple = true;
//					break;
//				}
//			}
//			if(!hasMultiple)
//			for (int k=0; k<3; k++)
//			{
//				indices.push_back(basisCollection[i].boundaries[j][k]);
//			}
//		}
//		for (int j=0; j<basisCollection[i].interior.size(); j++)
//		{
//			indices.push_back(basisCollection[i].interior[j]);
//		}
//		sort(indices.begin(), indices.end());
//		vindices.push_back(indices);
//	}
//	for (int i=0; i<vindices.size()-1; i++)
//	{
//		for (int j=i+1; j<vindices.size(); j++)
//		{
//			if (vindices[i].size()==vindices[j].size())
//			{
//				bool isSame = true;
//				for (int k=0; k<vindices[i].size(); k++)
//				{
//					if (vindices[i][k]!=vindices[j][k])
//					{
//						isSame = false;
//						break;
//					}
//				}
//				if (isSame && basisCollection[i].indices.size()==basisCollection[j].indices.size())
//				{
//					samePairs.push_back(make_pair(i, j));
//					count++;
//				}
//			}
//		}
//	}
//	return count;
//}
//
//bool CSurfaceData::getBasis(SplineBasis &basis, int &index)
//{
//	vector<SplineBasis> basisCollection = cdt_knotstri.get_basis_collection();
//	if (basisCollection.empty())
//	{
//		return false;
//	}
//	
//	basis = basisCollection[index];
//	return true;
//}
//
//void CSurfaceData::getBasisInfo(vector<vector<Point_2>> &boundaries, vector<Point_2> &interior, SplineBasis &basis, int &index)
//{
//	vector<SplineBasis> basisCollection = cdt_knotstri.get_basis_collection();
//	vector<Knot_Data> points = cdt_knotstri.get_knots();
//	if(index>=0 && index<basisCollection.size())
//	{
//		basis = basisCollection[index];
//		
//		for (int i=0; i<basis.boundaries.size(); i++)
//		{
//			vector<Point_2> boundary;
//			for (int j=0; j<3; j++)
//			{
//				boundary.push_back(points[basis.boundaries[i][j]].pt);
//			}
//			boundaries.push_back(boundary);
//		}
//
//		for (int i=0; i<basis.interior.size(); i++)
//		{
//			interior.push_back(points[basis.interior[i]].pt);
//		}
//	}
//}
//
//vector<Point_2> &CSurfaceData::get_basis_convex_hull(int &index)
//{
//	basis_convex_hull.clear();
//	vector<SplineBasis> basisCollection = cdt_knotstri.get_basis_collection();
//	vector<Knot_Data> points = cdt_knotstri.get_knots();
//	if(index>=0 && index<basisCollection.size())
//	{
//		vector<Point_2> pts;
//		for(int i=0; i<degree; i++)
//		{
//			pts.push_back(points[basisCollection[index].interior[i]].pt);
//		}
//		vector<vector<unsigned>>::iterator it =  basisCollection[index].boundaries.begin();
//		for(; it!=basisCollection[index].boundaries.end(); it++)
//		{
//			for(int i=0; i<3; i++)
//			{
//				pts.push_back(points[it->at(i)].pt);
//			}
//		}
//		CGAL::convex_hull_2(pts.begin(), pts.end(), std::back_inserter(basis_convex_hull));
//	}
//	return basis_convex_hull;
//}
//
//vector<SplineBasis> &CSurfaceData::get_spline_basis()
//{
//	return 	cdt_knotstri.get_basis_collection();;
//}
//
//void CSurfaceData::get_basis_knots(vector<Point_2> &pts, int &index)
//{
//	vector<SplineBasis> basisCollection = cdt_knotstri.get_basis_collection();
//	for(int i=0; i<degree; i++)
//	{
//		pts.push_back(knots[basisCollection[index].interior[i]].pt);
//	}
//	vector<vector<unsigned>>::iterator it =  basisCollection[index].boundaries.begin();
//	for(; it!=basisCollection[index].boundaries.end(); it++)
//	{
//		for(int i=0; i<3; i++)
//		{
//			pts.push_back(knots[it->at(i)].pt);
//		}
//	}
//}
//
//Polyhedron *CSurfaceData::get_error_fitted_mesh()
//{
//	if(!m_pFittedMesh)
//		return NULL;
//
//	return m_pErrorMesh;
//}
//
//vector<vector<Point_3>> &CSurfaceData::getSparseCurves()
//{
//	return cdt_knotstri.getSparseCurves();
//}
//
//vector<BoundaryInteriorConfigs> &CSurfaceData::get_configs0()
//{
//	return cdt_knotstri.get_configs0();
//}
//
//void CSurfaceData::set_output(bool bo)
//{
//	boutput = bo;
//}
//
//vector<Edge> &CSurfaceData::get_edges()
//{
//	return cdt_knotstri.get_edges();
//}
//
//void CSurfaceData::set_ann(bool av)
//{
//	cdt_knotstri.set_ann(av);
//}
//
//vector<vector<unsigned>> &CSurfaceData::get_vertices_triangles_plane()
//{
//	return cdt_knotstri.get_vertices_triangles_plane();
//}
//
//vector<vector<unsigned>> &CSurfaceData::get_vertices_triangles_space()
//{
//	return cdt_knotstri.get_vertices_triangles_space();
//}
//
//void CSurfaceData::write_mesh()
//{
//	Polyhedron *mesh = NULL;
//	{
//		QString timefileName = "./time";
//		QDir dir(timefileName);
//		timefileName.append("/");
//		QStringList list = fileName.split("/").last().split(".");
//		timefileName.append(list.at(0));
//		bool suc = false;
//		if(dir.exists(list.at(0)))
//		{
//			suc = true;
//		}
//		else
//		{
//			suc = dir.mkdir(list.at(0));
//		}
//
//		if(suc)
//		{
//			if(type==Delaunay)
//			{
//				timefileName.append("/Delaunay_");
//			}
//			else
//			{
//				timefileName.append("/DDT_");
//			}
//			timefileName.append("Fitted_");
//			timefileName.append(QString::number(iter_num, 10));
//			timefileName.append(".obj");
//			mesh = get_fitted_mesh();
//			if(mesh)
//			{
//				mesh->write_obj(timefileName, false);
//			}
//		}
//	}
//
//	{
//		QString timefileName = "./time";
//		QDir dir(timefileName);
//		timefileName.append("/");
//		QStringList list = fileName.split("/").last().split(".");
//		timefileName.append(list.at(0));
//		bool suc = false;
//		if(dir.exists(list.at(0)))
//		{
//			suc = true;
//		}
//		else
//		{
//			suc = dir.mkdir(list.at(0));
//		}
//
//		if(suc)
//		{
//			if(type==Delaunay)
//			{
//				timefileName.append("/Delaunay_");
//			}
//			else
//			{
//				timefileName.append("/DDT_");
//			}
//			timefileName.append("Error_");
//			timefileName.append(QString::number(iter_num, 10));
//			timefileName.append(".obj");
//			set_max_error(max_err.error);
//			mesh = get_error_fitted_mesh();
//			if(mesh)
//			{
//				mesh->write_obj(timefileName, true);
//			}
//		}
//	}
//
//	{
//		QString timefileName = "./time";
//		QDir dir(timefileName);
//		timefileName.append("/");
//		QStringList list = fileName.split("/").last().split(".");
//		timefileName.append(list.at(0));
//		bool suc = false;
//		if(dir.exists(list.at(0)))
//		{
//			suc = true;
//		}
//		else
//		{
//			suc = dir.mkdir(list.at(0));
//		}
//
//		if(suc)
//		{
//			if(type==Delaunay)
//			{
//				timefileName.append("/Delaunay_");
//			}
//			else
//			{
//				timefileName.append("/DDT_");
//			}
//			timefileName.append("CV_");
//			timefileName.append(QString::number(iter_num, 10));
//			timefileName.append(".obj");
//			Point_3 *control_vertices = get_control_vertices();
//			if(!control_vertices)
//				return;
//			QFile file( timefileName);
//			if ( file.open(QIODevice::WriteOnly)) 
//			{
//				QTextStream out( &file );
//				int basis_size = get_basis_size();
//				out << "g object" << endl;
//				for(int i=0; i<basis_size; i++)
//				{
//					out << "v " <<control_vertices[i].x() << " " << control_vertices[i].y() << " " << control_vertices[i].z() << endl;
//				}
//			}
//		}
//	}
//
//	{
//		QString timefileName = "./time";
//		QDir dir(timefileName);
//		timefileName.append("/");
//		QStringList list = fileName.split("/").last().split(".");
//		timefileName.append(list.at(0));
//		bool suc = false;
//		if(dir.exists(list.at(0)))
//		{
//			suc = true;
//		}
//		else
//		{
//			suc = dir.mkdir(list.at(0));
//		}
//
//		if(suc)
//		{
//			if(type==Delaunay)
//			{
//				timefileName.append("/Delaunay_");
//			}
//			else
//			{
//				timefileName.append("/DDT_");
//			}
//			timefileName.append("AE_");
//			timefileName.append(QString::number(iter_num, 10));
//			timefileName.append(".obj");
//			Point_3 *control_vertices = get_control_vertices();
//			if(!control_vertices)
//				return;
//			QFile file( timefileName);
//			if ( file.open(QIODevice::WriteOnly)) 
//			{
//				QTextStream out( &file );
//				int basis_size = get_basis_size();
//				out << "g object" << endl;
//				for(int i=0; i<basis_size; i++)
//				{
//					out << "v " <<control_vertices[i].x() << " " << control_vertices[i].y() << " " << control_vertices[i].z() << endl;
//				}
//				vector<Edge> edges = get_control_edges_auxiliary();
//				for(int i=0; i<edges.size(); i++)
//				{
//					int first = edges[i].first+1;
//					int second = edges[i].second+1;
//					out << "l " << first << " " << second << endl;
//				}
//			}
//		}
//	}
//
//
//	{
//		QString timefileName = "./time";
//		QDir dir(timefileName);
//		timefileName.append("/");
//		QStringList list = fileName.split("/").last().split(".");
//		timefileName.append(list.at(0));
//		bool suc = false;
//		if(dir.exists(list.at(0)))
//		{
//			suc = true;
//		}
//		else
//		{
//			suc = dir.mkdir(list.at(0));
//		}
//
//		if(suc)
//		{
//			if(type==Delaunay)
//			{
//				timefileName.append("/Delaunay_");
//			}
//			else
//			{
//				timefileName.append("/DDT_");
//			}
//			timefileName.append("CE_");
//			timefileName.append(QString::number(iter_num, 10));
//			timefileName.append(".obj");
//			Point_3 *control_vertices = get_control_vertices();
//			if(!control_vertices)
//				return;
//			QFile file( timefileName);
//			if ( file.open(QIODevice::WriteOnly)) 
//			{
//				QTextStream out( &file );
//				int basis_size = get_basis_size();
//				out << "g object" << endl;
//				for(int i=0; i<basis_size; i++)
//				{
//					out << "v " <<control_vertices[i].x() << " " << control_vertices[i].y() << " " << control_vertices[i].z() << endl;
//				}
//
//				vector<Edge> edges = get_control_edges();
//				int sz = edges.size();
//				for(int i=0; i<edges.size(); i++)
//				{
//					out << "l " << edges[i].first+1 << " " <<  edges[i].second+1 << endl;
//					//out << "l " << edges[i].second+1 << " " <<  edges[i].first+1 << endl;
//				}
//			}
//		}
//	}
//	return;
//}
//
//void CSurfaceData::save_global_costs()
//{
//	QFile file("./Record/123.ply2");
//	if (file.open(QIODevice::WriteOnly))
//	{
//		QTextStream out(&file);
//		out << m_pOriginalMesh->size_of_vertices() << endl;
//		out << m_pOriginalMesh->size_of_facets() << endl;
//
//		Polyhedron::Vertex_iterator vit = m_pOriginalMesh->vertices_begin();
//		for (; vit!=m_pOriginalMesh->vertices_end(); vit++)
//		{
//			out << vit->point().x() << endl;
//			out << vit->point().y() << endl;
//			out << vit->point().z() << endl;
//		}
//
//		vit = m_pOriginalMesh->vertices_begin();
//		Polyhedron::Facet_iterator fit = m_pOriginalMesh->facets_begin();
//		for (; fit!=m_pOriginalMesh->facets_end(); fit++)
//		{
//			Polyhedron::Halfedge_around_facet_circulator h = fit->facet_begin();
//			out << 3 << endl;
//			out << distance(vit, h->vertex()) << endl;
//			h++;
//			out << distance(vit, h->vertex()) << endl;
//			h++;
//			out << distance(vit, h->vertex()) << endl;
//		}
//
//		file.close();
//	}
//
//#if 0
//	if(type!=Delaunay)
//	{
//		list<double> global_costs = get_global_costs();
//
//		QString timefileName = "./Record";
//		QDir dir(timefileName);
//		timefileName.append("/");
//		QStringList list = fileName.split("/").last().split(".");
//		timefileName.append(list.at(0));
//		bool suc = false;
//		if(dir.exists(list.at(0)))
//		{
//			suc = true;
//		}
//		else
//		{
//			suc = dir.mkdir(list.at(0));
//		}
//
//		if(suc)
//		{
//			timefileName.append("/ddt_");
//			QString type;
//			SimulatedAnnealing sa_type = cdt_knotstri.get_sa_type();
//			if(sa_type == OneStep)
//				type = "os";
//			else
//			{
//				if(sa_type == SA)
//					type = "sa";
//				else
//					if(sa_type == Lop)
//						type = "lop";
//					else
//						type = "combination";
//			}
//			timefileName.append(type);
//			timefileName.append("_global_costs_");
//			timefileName.append(QString::number(iter_num-1, 10));
//			timefileName.append(".txt");
//			QFile file( timefileName);
//			if ( file.open(QIODevice::WriteOnly)) 
//			{
//				QTextStream out( &file );
//				if(sa_type==Combination)
//				{
//					out << cdt_knotstri.get_lop_num() << endl;
//				}
//				std::list<double>::iterator it = global_costs.begin();
//				std::list<double>::iterator last = global_costs.end();
//				last--;
//				for(; it!=last; it++)
//				{
//					out << *it << endl;
//				}
//				out << *it;
//				file.close();
//			}
//		}
//	}
//#endif
//}
//
//void CSurfaceData::read_knots()
//{
//	QString str = "./Knots/";
//	QStringList list = fileName.split("/").last().split(".");
//	str.append(list.at(0));
//	QString fname = QFileDialog::getOpenFileName(NULL, 
//		tr("Select File..."), str, tr("Knots Files(*.txt)"));
//	QFile file(fname);
//	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
//	{	
//		QTextStream in(&file);
//		in.setRealNumberPrecision(20);
//		QString line = in.readLine();
//		if(line.isNull())
//			return;
//		while (!line.isNull()) 
//		{
//			QStringList list = line.split(" ");
//
//			Knot knot;
//			if(list.at(0)=="p")
//			{
//				knot.pt = Point_2(list.at(1).toDouble(), list.at(2).toDouble());
//				line = in.readLine();
//				list = line.split(" ");
//				if(list.at(0)=="v")
//				{
//					knot.vertex = Point_3(list.at(1).toDouble(), list.at(2).toDouble(), list.at(3).toDouble());
//				}
//			}
//			knots.push_back(knot);
//			line = in.readLine();
//		}
//		file.close();
//	}
//}
//
//void CSurfaceData::write_knots(QString &fileName)
//{
//	QFile file(fileName);
//	if (file.open(QIODevice::WriteOnly))
//	{	
//		QTextStream out(&file);
//		out.setRealNumberPrecision(20);
//		vector<Knot_Data> knots = get_knots();
//		for(int i=0; i<knots.size(); i++)
//		{
//			out << "p ";
//			out << knots[i].pt.x() << " " << knots[i].pt.y() << endl;
//			out << "v ";
//			out << knots[i].vertex.x() << " " << knots[i].vertex.y() << " " << knots[i].vertex.z() << endl;
//		}
//		file.close();
//	}
//}
//
//void CSurfaceData::set_knots_input(bool ki)
//{
//	bknots_input = ki;
//}
