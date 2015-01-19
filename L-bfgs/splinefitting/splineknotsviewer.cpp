//#include <CGAL/Cartesian.h>
#include "splineknotsviewer.h"
#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_2.h>
#include <QtGui/QInputDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <fstream>
//#include "enriched_polyhedron.h"

//typedef CGAL::Cartesian<double>  Kernel3;
//typedef Enriched_polyhedron<Kernel3,Enriched_items> Polyhedron;

//typedef CGAL::Polygon_2<K>                                 Polygon_2;

SplineKnotsViewer::SplineKnotsViewer(void)
{	surfacedata = NULL;
    uknot=NULL;
	vknot=NULL;
	//basis_index = -1;
	bknotsview = false;
	bcurvature_show=false;
	berror_show=false;
	parameter2=NULL;
	/*bdomainview = false;*/
	///*bcentroidview = false;
	//bbasisview = false;
	//bbasissumview = false;
	//bbasis_knots = false;
	//bbasis_support = false;
	//btriangulation_view = false;
	//bdelaunayview = false;
	//bddtview = false;
	//bfeatureview = false;
	 bmeshdomainview= false;
	 setAutoBufferSwap( false );
	 setAutoFillBackground( false );
	berrordomainview = false;
	/*bdensitydomainview = false;
	bthintrianglesview = false;
	thintrianglesangle_view = false;
	bprincipaldirection_view = false;*/

}

void SplineKnotsViewer::clear_data()
{
	//basis_index = -1;
	/*
	bdomainview = false;
	bcentroidview = false;
	bbasisview = false;
	bbasissumview = false;
	bbasis_knots = false;
	bbasis_support = false;
	btriangulation_view = false;
	bdelaunayview = false;
	bddtview = false;
	bfeatureview = false;*/
	//index=0;
	bknotsview=false;
	bmeshdomainview=false;	
	bcurvature_show=false;
	
}  

SplineKnotsViewer::~SplineKnotsViewer(void)
{
	clear_data();
}  

void SplineKnotsViewer::set_surface_data(CSurfaceData *data)
{
	surfacedata = data;
	/*Bbox_2 box_2 = surfacedata->get_box();
	Bbox_3 box_3(box_2.xmin(), box_2.ymin(), 0, box_2.xmax(), box_2.ymax(), 1);
	set_scene(box_3); 	updateGL();*/ 
}

void SplineKnotsViewer::update_view() 
{
	Bbox_2 box_2 = surfacedata->get_box();
	Bbox_3 box_3(box_2.xmin(), box_2.ymin(), 0, box_2.xmax(), box_2.ymax(), 1);
	set_scene(box_3); 
    bmeshdomainview= true;
	updateGL();
}

void SplineKnotsViewer::set_scene(Bbox_3 &box)
{
	
	Mesh::Point     bbMin(box.xmin(), box.ymin(), box.zmin());
	Mesh::Point     bbMax(box.xmax(), box.ymax(), box.zmax());
	Mesh::Point     center= (bbMin + bbMax)*0.5;
	double radius=0.5*(bbMin - bbMax).norm();
	setSceneCenter(Vec(center[0], center[1], center[2]));
	setSceneRadius(radius);
	camera()->showEntireScene();
}

void SplineKnotsViewer::draw()
{
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(3.0f, 1.0f);
	glDisable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	if(bknotsview)
		draw_knots();
	//if(bdomainview/* || berrordomainview || bdensitydomainview*/) 
	//	draw_domain();
	if(berrordomainview) 
		draw_curvature_error_domain();
	if(bmeshdomainview)
		draw_domain_mesh();
	if(bcurvature_show)
		draw_curvature_mesh();
	if (berror_show)
	    draw_fitting_error_domain();
	/*if(bcentroidview)
		draw_centroidtrianles();
	if(bbasisview)
		draw_basis();
	if(bbasissumview)
		draw_basis_sum();
	if(bbasis_knots)
		draw_basis_knots();
	if(bbasis_support)
		draw_basis_suport();
	if(btriangulation_view)
		draw_triangulation();
	if(bdelaunayview)
		draw_delaunay();
	if(bddtview)
		draw_ddt();
	if(bfeatureview)
		draw_feature_hull();
	if(bthintrianglesview)
		draw_thin_triangles();
	if(thintrianglesangle_view)
		draw_thin_triangles_angle();
	if(bprincipaldirection_view)
		draw_principal_directions();*/
	glDisable(GL_POLYGON_OFFSET_FILL);
	glPopMatrix();
}

void SplineKnotsViewer::init()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Restore previous viewer state.
	restoreStateFromFile();
	setBackgroundColor(QColor(255,255,255,0));
    setMouseBinding(Qt::NoModifier, Qt::LeftButton, NO_CLICK_ACTION);
	//setMouseBinding(Qt::NoModifier, Qt::LeftButton, CAMERA, ROTATE);
}

void SplineKnotsViewer::draw_knots()
{ 	
	
	if(surfacedata==NULL||parameter2==NULL)
		return;
	else if(parameter2->getq()==0)//���������������ʱû��������ϡ�
	    return;
	glColor3d(1.0, 0.0, 0.0);
	glLineWidth(0.5);
	int p=parameter2->getp();
	int q=parameter2->getq();
	int m=parameter2->getm();
	int n=parameter2->getn();
	for (int j=q;j<n+1;j++)
	  for (int i=p;i<m+1;i++)
		{
			glBegin(GL_LINE_LOOP);
			glVertex2d(uknot[i-p],vknot[j-q]);
			glVertex2d(uknot[i-p+1],vknot[j-q]);
			glVertex2d(uknot[i-p+1],vknot[j-q+1]);
			glVertex2d(uknot[i-p],vknot[j-q+1]);
			glEnd();
		}
	


}
void SplineKnotsViewer::draw_fitting_error_domain()
{
	if(surfacedata==NULL)
		return;
	if ((surfacedata->get_domain()).empty())
		return;
	Mesh *mesh = surfacedata->get_error_fitted_mesh();
	if (mesh==NULL)
		return;
	Mesh::ConstFaceIter        f_it(mesh->faces_begin()),f_end(mesh->faces_end());
	Mesh::ConstFaceVertexIter  fv_it;
	//glLineWidth(0.5);
	for (; f_it!=f_end; ++f_it)
	{

		//glBegin(GL_LINE_LOOP);
		glBegin(GL_TRIANGLES);
		fv_it = mesh->cfv_iter(*f_it); 
		glColor3ubv(mesh->color(*fv_it).data());
		glVertex2dv(&mesh->texcoord2D(fv_it)[0]);
		++fv_it;
		glColor3ubv(mesh->color(*fv_it).data());
		glVertex2dv(&mesh->texcoord2D(fv_it)[0]);
		++fv_it;
		glColor3ubv(mesh->color(*fv_it).data());
		glVertex2dv(&mesh->texcoord2D(fv_it)[0]);
		glEnd();
	}



   
}
//void SplineKnotsViewer::draw_centroidtrianles()
//{
//
//	if(surfacedata==NULL)
//		return;
//	vector<CentroidTriangulation> centroid_points = surfacedata->get_centroid_points();
//#if 1
//	{
//		vector<vector<unsigned>> centroidtrianglesk_1 = surfacedata->get_centroidtrianglesk_1();
//		vector<vector<unsigned>>::iterator it = centroidtrianglesk_1.begin(), it_end = centroidtrianglesk_1.end();
//		glColor3d(1.0, 1.0, 1.0); 	
//		for(; it!=it_end; it++) 	
//		{ 		
//			glBegin(GL_POLYGON);
//			for(int i=0;i<it->size();i++)
//			{ 				
//				glVertex2d(centroid_points[it->at(i)].pt.x(), centroid_points[it->at(i)].pt.y());	
//			}
//			glEnd();
//		}
//
//		it = centroidtrianglesk_1.begin();
//		glLineWidth(2.0f);
//		glColor3d(0.0, 0.0, 0.0);
//		for(; it!=it_end; it++)
//		{ 		
//			glBegin(GL_LINE_LOOP); 			
//			for(int i=0;i<it->size();i++)
//			{ 				
//				glVertex2d(centroid_points[it->at(i)].pt.x(), centroid_points[it->at(i)].pt.y());
//			} 		
//			glEnd(); 	
//		}  	
//		it = centroidtrianglesk_1.begin();
//		glPointSize(8.0f);
//		glColor3d(0.0, 0.0, 1.0);
//		glBegin(GL_POINTS);
//		for(; it!=it_end; it++)
//		{	 		
//			for(int i=0;i<it->size();i++)
//			{ 			
//				glVertex2d(centroid_points[it->at(i)].pt.x(), centroid_points[it->at(i)].pt.y());
//			} 	
//		} 	
//		glEnd();
//	}
//#endif
//#if 1
//	{
//		vector<vector<unsigned>> centroidtrianglesk_2 = surfacedata->get_centroidtrianglesk_2();
//		vector<vector<unsigned>>::iterator it = centroidtrianglesk_2.begin(), it_end = centroidtrianglesk_2.end();
//		glColor3d(0.0, 0.8,0.0);
//		for(; it!=it_end; it++)
//		{ 		
//			glBegin(GL_POLYGON);
//			for(int i=0;i<it->size();i++) 			
//			{ 				
//				glVertex2d(centroid_points[it->at(i)].pt.x(), centroid_points[it->at(i)].pt.y());
//			} 		
//			glEnd(); 	
//		} 	
//		it = centroidtrianglesk_2.begin();
//		glLineWidth(2.0f);
//		glColor3d(0.0, 0.0,0.0);
//		for(; it!=it_end; it++)
//		{ 		
//			glBegin(GL_LINE_LOOP);
//			for(int i=0;i<it->size();i++)
//			{ 				
//				glVertex2d(centroid_points[it->at(i)].pt.x(), centroid_points[it->at(i)].pt.y());
//			}
//			glEnd();
//		} 	
//		it = centroidtrianglesk_2.begin();
//		glPointSize(8.0f);
//		glColor3d(0.0, 0.0, 1.0);
//		glBegin(GL_POINTS); 	
//		for(; it!=it_end; it++)
//		{
//			for(int i=0;i<it->size();i++)
//			{ 			
//				glVertex2d(centroid_points[it->at(i)].pt.x(), centroid_points[it->at(i)].pt.y());
//			}		 	
//		} 	
//		glEnd(); 
//	}
//#endif
//} 
//
//void SplineKnotsViewer::draw_basis_knots()
//{ 	
//#if 0
//	vector<SplineBasis>  basisCollection = surfacedata->get_basis_collection();
//	if(!basisCollection.empty()) 	
//	{ 		
//		int sz = basisCollection.size();
//		int degree = basisCollection[0].interior.size();
//		vector<Point_2> knots = surfacedata->get_knots();
//		Point_2 *control_point = new Point_2[sz];
//		glPointSize(8.0f); 		
//		glColor3d(0.0, 0.0, 0.0); 		
//		glBegin(GL_POINTS); 		
//		for(int i=0; i<sz; i++) 		
//		{ 			
//			double x = 0; 			
//			double y = 0; 			
//			for(int j=0; j<degree; j++)
//			{ 				
//				x += knots[basisCollection[i].interior[j]].x();
//				y += knots[basisCollection[i].interior[j]].y();
//			}
//			x /= degree;
//			y /= degree;
//			control_point[i] = Point_2(x, y);
//			glVertex2d(x, y);
//		} 		
//		glEnd();
//
//		vector<Facet> control_facets = surfacedata->get_control_facets();
//		sz = control_facets.size();
//		glColor3d(1.0, 0, 0.0);
//		glLineWidth(2.0f);
//		for(int i=0; i<sz; i++)
//		{
//			glBegin(GL_LINE_LOOP);
//			unsigned index = control_facets[i].first;
//			glVertex2d(control_point[index].x(), control_point[index].y());
//			index = control_facets[i].second;
//			glVertex2d(control_point[index].x(), control_point[index].y());
//			index = control_facets[i].third;
//			glVertex2d(control_point[index].x(), control_point[index].y());
//			glEnd();
//		}
//
//		delete []control_point;
//	}
//#else
//	if(surfacedata==NULL)
//		return;
//	vector<CentroidTriangulation> centroid_points = surfacedata->get_centroid_points();
//	vector<vector<unsigned>> vertices_triangles = surfacedata->get_vertices_triangles_plane();
//
//	glPointSize(8.0f); 		
//	glColor3d(0.0, 0.0, 0.0); 	
//	glBegin(GL_POINTS); 
//		for(int i=0; i<vertices_triangles.size(); i++)
//		{
//			for(int j=0; j<3; j++)
//			{
//				glVertex2d(centroid_points[vertices_triangles[i].at(j)].pt.x(), centroid_points[vertices_triangles[i].at(j)].pt.y());
//			}
//		}
//	glEnd();
//
//	glColor3d(1.0, 0, 0.0);
//	glLineWidth(2.0f);
//	for(int i=0; i<vertices_triangles.size(); i++)
//	{
//		glBegin(GL_LINE_LOOP);
//			for(int j=0; j<3; j++)
//			{
//				glVertex2d(centroid_points[vertices_triangles[i].at(j)].pt.x(), centroid_points[vertices_triangles[i].at(j)].pt.y());
//			}
//		glEnd();
//	}
//#endif
//}
//
//void SplineKnotsViewer::draw_domain()
//{
//	//if(surfacedata==NULL)
//	//	return;
//	//glColor3d(0.1, 0.1,0.8);
//	//glPointSize(2.0);
//
//	//Polyhedron *m_pDomainMesh = surfacedata->get_domain_mesh();
//	//if(m_pDomainMesh==NULL)
//	//	return;
//	//
//
//	//if(m_pDomainMesh != NULL && m_pDomainMesh->is_valid() && !m_pDomainMesh->empty())
//	//{
//	//	m_pDomainMesh->gl_draw(true, true);
//	//}
//}

void SplineKnotsViewer::draw_domain_mesh()
{
	if(surfacedata==NULL)
		return;
	if ((surfacedata->get_domain()).empty())
		return;
	Mesh *mesh = surfacedata->get_original_mesh();
	if (mesh==NULL)
		return;
	Mesh::ConstFaceIter        f_it(mesh->faces_begin()),f_end(mesh->faces_end());
	Mesh::ConstFaceVertexIter  fv_it;
	glColor3d(0.4, 0.4, 0.5);
	glLineWidth(0.5);
	
	for (; f_it!=f_end; ++f_it)
	{
		glBegin(GL_LINE_LOOP);
		fv_it = mesh->cfv_iter(*f_it); 
		glVertex2dv(&mesh->texcoord2D(fv_it)[0]);
		++fv_it;
		glVertex2dv(&mesh->texcoord2D(fv_it)[0]);
		++fv_it;
		glVertex2dv(&mesh->texcoord2D(fv_it)[0]);
		glEnd();
	}

	
}
void SplineKnotsViewer::draw_curvature_mesh()
{
	if(surfacedata==NULL)
		return;
	if ((surfacedata->get_domain()).empty())
		return;
	Mesh *mesh = surfacedata->get_original_mesh();
	if (mesh==NULL)
		return;
	Mesh::ConstFaceIter        f_it(mesh->faces_begin()),f_end(mesh->faces_end());
	Mesh::ConstFaceVertexIter  fv_it;
	//glLineWidth(0.5);
	for (; f_it!=f_end; ++f_it)
	{
		
		//glBegin(GL_LINE_LOOP);
		glBegin(GL_TRIANGLES);
		fv_it = mesh->cfv_iter(*f_it); 
		glColor3ubv(mesh->color(*fv_it).data());
		glVertex2dv(&mesh->texcoord2D(fv_it)[0]);
		++fv_it;
		glColor3ubv(mesh->color(*fv_it).data());
		glVertex2dv(&mesh->texcoord2D(fv_it)[0]);
		++fv_it;
		glColor3ubv(mesh->color(*fv_it).data());
		glVertex2dv(&mesh->texcoord2D(fv_it)[0]);
		glEnd();
	}

}
void SplineKnotsViewer::draw_curvature_colorbar(QPainter *painter) 
{
	const int barwidth = 20;
	const int barheight = 200;
	painter->save();
    painter->translate(0.8*width(), 0.7*height());
	painter->save();
	int h1, s1, v1;
    int h2, s2, v2;
	int color[3];
	color[0] = 250;
	color[1] = 0;
	color[2] = 0;
	QColor d_light(color[0], color[1], color[2]);

	color[0] = 0;
	color[1] = 0;
	color[2] = 255;
    QColor d_dark(color[0], color[1], color[2]);
    d_light.getHsv( &h1, &s1, &v1 );
    d_dark.getHsv( &h2, &s2, &v2 );
	QRect rect(0, -100, barwidth, barheight);
    painter->setClipRect( rect );
    painter->setClipping( true );

    painter->fillRect( rect, d_dark );

    int sectionSize = 4;

    int numIntervals;
    numIntervals = rect.height() / sectionSize;

    for ( int i = 0; i < numIntervals; i++ )
    {
        QRect colorsection;
        colorsection.setRect( rect.x(), rect.y() + i * sectionSize,
            rect.width(), sectionSize );

        const double ratio = i / static_cast<double>( numIntervals );
        QColor c;
        c.setHsv( h1 + qRound( ratio * ( h2 - h1 ) ),
            s1 + qRound( ratio * ( s2 - s1 ) ),
            v1 + qRound( ratio * ( v2 - v1 ) ) );
		/*int color[3];
		c.getRgb(&color[0], &color[1], &color[2]);*/
        painter->fillRect( colorsection, c );
    }
	painter->restore();
	sectionSize = 8;
	painter->translate(barwidth, 0);
	QFont font("Times", 10);
	painter->setPen(Qt::black);
	painter->setFont(font);
	double max_curve=surfacedata->get_max_meancurvature();
	double min_curve=surfacedata->get_min_meancurvature();
	double cur_step = (max_curve-min_curve)/ sectionSize;
	for ( int i = 0; i <= sectionSize; i++ )
	{
		QString str = QString::number(i*cur_step+min_curve);
		painter->drawText(5, barheight/2-barheight/8*i, str);
	}
	painter->restore();
}
void SplineKnotsViewer::draw_curvature_error_domain()
{

	if(surfacedata==NULL)
		return;
	if ((surfacedata->get_domain()).empty())
		return;
	MyMesh polymesh = surfacedata->get_polymesh();
	if (polymesh.edges_empty()==true)
		return;
	MyMesh::ConstFaceIter        f_it(polymesh.faces_begin()),f_end(polymesh.faces_end());
	MyMesh::ConstFaceVertexIter  fv_it;
	//glLineWidth(0.5);
	for (; f_it!=f_end; ++f_it)
	{

		glColor3ubv(polymesh.color(*f_it).data());
		glBegin(GL_POLYGON);
		fv_it = polymesh.cfv_iter(*f_it); 
		glVertex3dv(&polymesh.point(fv_it)[0]);
		++fv_it;
		glVertex3dv(&polymesh.point(fv_it)[0]);
		++fv_it;
		glVertex3dv(&polymesh.point(fv_it)[0]);
		++fv_it;
		glVertex3dv(&polymesh.point(fv_it)[0]);
		glEnd();
	}


}

void SplineKnotsViewer::draw_curvature_error_colorbar(QPainter *painter) 
{
const int barwidth = 20;
	const int barheight = 200;
	painter->save();
    painter->translate(0.8*width(), 0.7*height());
	painter->save();
	int h1, s1, v1;
    int h2, s2, v2;
	int color[3];
	color[0] = 127;
	color[1] = 0;
	color[2] = 0;
	QColor d_light(color[0], color[1], color[2]);

	color[0] = 0;
	color[1] = 0;
	color[2] = 127;
    QColor d_dark(color[0], color[1], color[2]);
    d_light.getHsv( &h1, &s1, &v1 );
    d_dark.getHsv( &h2, &s2, &v2 );
	QRect rect(0, -100, barwidth, barheight);
    painter->setClipRect( rect );
    painter->setClipping( true );

    painter->fillRect( rect, d_dark );

    int sectionSize = 4;

    int numIntervals;
    numIntervals = rect.height() / sectionSize;

    for ( int i = 0; i < numIntervals; i++ )
    {
        QRect colorsection;
        colorsection.setRect( rect.x(), rect.y() + i * sectionSize,
            rect.width(), sectionSize );

        const double ratio = i / static_cast<double>( numIntervals );
        QColor c;
        c.setHsv( h1 + qRound( ratio * ( h2 - h1 ) ),
            s1 + qRound( ratio * ( s2 - s1 ) ),
            v1 + qRound( ratio * ( v2 - v1 ) ) );
		/*int color[3];
		c.getRgb(&color[0], &color[1], &color[2]);*/
        painter->fillRect( colorsection, c );
    }
	painter->restore();
	sectionSize = 8;
	painter->translate(barwidth, 0);
	QFont font("Times", 10);
	painter->setPen(Qt::black);
	painter->setFont(font);
	double max_curve=surfacedata->get_max_knotcurerror();
	double min_curve=surfacedata->get_min_knotcurerror();
	double cur_step = (max_curve-min_curve)/ sectionSize;
	for ( int i = 0; i <= sectionSize; i++ )
	{
		QString str = QString::number(i*cur_step+min_curve);
		painter->drawText(5, barheight/2-barheight/8*i, str);
	}
	painter->restore();

}
void SplineKnotsViewer::draw_fitting_error_colorbar(QPainter *painter)
{
	const int barwidth = 20;
	const int barheight = 200;
	painter->save();
	painter->translate(0.8*width(), 0.7*height());
	painter->save();
	int h1, s1, v1;
	int h2, s2, v2;
	int color[3];
	color[0] = 250;
	color[1] = 0;
	color[2] = 0;
	QColor d_light(color[0], color[1], color[2]);

	color[0] = 0;
	color[1] = 0;
	color[2] = 255;
	QColor d_dark(color[0], color[1], color[2]);
	d_light.getHsv( &h1, &s1, &v1 );
	d_dark.getHsv( &h2, &s2, &v2 );
	QRect rect(0, -100, barwidth, barheight);
	painter->setClipRect( rect );//���òü���Ĭ���òü�������ԭ�ȵġ�
	painter->setClipping( true );

	painter->fillRect( rect, d_dark );//��d_dark�����rect

	int sectionSize = 4;

	int numIntervals;
	numIntervals = rect.height() / sectionSize;

	for ( int i = 0; i < numIntervals; i++ )
	{
		QRect colorsection;
		colorsection.setRect( rect.x(), rect.y() + i * sectionSize,
			rect.width(), sectionSize );

		const double ratio = i / static_cast<double>( numIntervals );
		QColor c;
		c.setHsv( h1 + qRound( ratio * ( h2 - h1 ) ),
			s1 + qRound( ratio * ( s2 - s1 ) ),
			v1 + qRound( ratio * ( v2 - v1 ) ) );

		painter->fillRect( colorsection, c );
	}
	painter->restore();
	sectionSize = 8;
	painter->translate(barwidth, 0);
	QFont font("Times", 10);
	painter->setPen(Qt::black);
	painter->setFont(font);
	double err_step = max_err / sectionSize;
	for ( int i = 0; i <= sectionSize; i++ )
	{
		QString str = QString::number(i*err_step);
		painter->drawText(5, barheight/2-barheight/8*i, str);
	}
	painter->restore();

}
void SplineKnotsViewer::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)
		QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);

	// Save current OpenGL state
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// Classical 3D drawing, usually performed by paintGL().
	preDraw();
	draw();
	postDraw();

	// Restore OpenGL state
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();

	painter.begin(this);
	if(bcurvature_show)
		draw_curvature_colorbar(&painter);
	if (berrordomainview)
	    draw_curvature_error_colorbar(&painter);
	if (berror_show)
	     draw_fitting_error_colorbar(&painter);
	painter.end();
	swapBuffers( );
}
//void SplineKnotsViewer::draw_basis_sum()
//{
//	if(surfacedata==NULL)
//		return;
//	
//	Polyhedron *basissummesh = NULL;
//	basissummesh = surfacedata->get_basis_sum_polyhedron();
//	if(basissummesh)
//		basissummesh->gl_draw(true, true, true);
//}
//
//void SplineKnotsViewer::draw_basis()
//{
//	if(surfacedata==NULL || basis_index == -1)
//		return;
//
//	Polyhedron *basismesh = surfacedata->get_basis_mesh();
//
//	if(basismesh!=NULL && basismesh->is_valid() && !basismesh->empty())
//	{
//		basismesh->gl_draw(true, true, true);
//	}
//}
//
void SplineKnotsViewer::set_knots_view(bool kv) 
{ 	
	bknotsview = kv;
	if(kv)
	{
		if(surfacedata==NULL)
			return;
		parameter2 = surfacedata->getparameter();

		/*if (parameter2==NULL)
			return;*/
		B_parameter p(0,0,0,0);
		if(*parameter2==p)
			return;
		if (!parameter2->configure_knots())
			return;

			uknot=parameter2->getuknot();
			vknot=parameter2->getvknot();
		Bbox_3 box_3(0,0,0, 1, 1, 1);
		set_scene(box_3);
	}
	updateGL();
}
void SplineKnotsViewer::set_curvature_show(bool kv) 
{ 	
	if (kv)
	{
		Mesh *m_pOriginalMesh = surfacedata->get_original_mesh();      
		if(!m_pOriginalMesh)
			return;
		surfacedata->update_curvature_color();
       bmeshdomainview=false;
       berror_show = false;
	}
	bcurvature_show=kv;
	updateGL();
}
void SplineKnotsViewer::error_fitting_view(bool kv)
{
	
	if(kv)
	{
		
		
		Mesh *m_pFittedMesh = surfacedata->get_fitted_mesh();
		if(!m_pFittedMesh)
			return;
		double mean_error;
		Max_Error max_error;
		//if(error == NULL)
		//{
		surfacedata->compute_error();
		mean_error = surfacedata->get_mean_error();
		QString str = "The mean error between original surface and the fitted surface is ";
		str.append(QString::number(mean_error));
		max_error = surfacedata->get_max_error();
		str.append(", the maximal relative error between original surface and the fitted surface is ");
		str.append(QString::number(max_error.error));
		QMessageBox::information(this, "Error of Fitted Surface", str, QMessageBox::Yes, QMessageBox::Yes);
		//}
		bool ok = false;
		max_err = 
			QInputDialog::getDouble(this, 
			tr("Max Error"),
			tr("Please input number:"),
			0.01,
			0,
			1,
			8,
			&ok);//���������һ�����Ǽ�����������ȽϹ���������ֻ��һ������������Ҫ����������ı�׼��
		//ʹ֮�������Ƚϴ�ĵ�ͻ������
		if(!ok)
			max_err = 1;
		surfacedata->set_max_error(max_err);
	
		
		
	}
	berror_show = kv;
	bmeshdomainview=false;
	bcurvature_show=false;
	updateGL();

}
//void SplineKnotsViewer::set_domain_view(bool dv)
//{
//	bdomainview = dv;
//	if(dv)
//	{
//		if(surfacedata==NULL)
//			return;
//		Point_2 *domain = surfacedata->get_domain();
//		
//		if(domain == NULL)
//			return;
//		int num = surfacedata->get_mesh_vertex_num();
//		vector<Point_2> out;
//		CGAL::convex_hull_points_2(domain, domain+num, back_inserter(out));
//		Polygon_2 poly(out.begin(), out.end());
//		Bbox_2 box_2 = poly.bbox();
//		Bbox_3 box_3(box_2.xmin(),box_2.ymin(), 0, box_2.xmax(), box_2.ymax(), 1);
//		set_scene(box_3); 
//
//		int iter_num = surfacedata->get_iterator_num();
//		surfacedata->get_domain_mesh();
//		surfacedata->set_domain_color(1);
//	} 	
//	updateGL();
//}  
//
//void SplineKnotsViewer::set_centroid_view(bool cv)
//{ 	
//	if(cv)
//	{
//		if(surfacedata==NULL)
//			return;
//		vector<Knot_Data> knots = surfacedata->get_knots();
//		if(knots.empty())
//			return;
//		vector<Point_2> out;
//		vector<Point_2> pts;
//		for(int i=0; i<knots.size(); i++)
//		{
//			pts.push_back(knots[i].pt);
//		}
//		CGAL::convex_hull_points_2(pts.begin(), pts.end(), back_inserter(out));
//		Polygon_2 poly(out.begin(), out.end());
//		Bbox_2 box_2 = poly.bbox();
//		Bbox_3 box_3(box_2.xmin(),box_2.ymin(), 0, box_2.xmax(), box_2.ymax(), 1);
//		set_scene(box_3);
//	}
//	bcentroidview = cv;
//	updateGL();
//}
//
//void SplineKnotsViewer::set_basis_view(bool bv)
//{
//	bbasisview = bv;
//}
//
//void SplineKnotsViewer::set_basis_sum_view(bool sv)
//{
//	bbasissumview = sv;
//	if(sv)
//	{
//		if(surfacedata==NULL)
//			return;
//
//		Polyhedron *basissummesh = NULL;
//		
//		basissummesh = surfacedata->get_basis_sum_polyhedron();
//		QFile file("F:/basis_sum.txt");
//		if(file.open(QIODevice::WriteOnly))
//		{
//			QTextStream out(&file);
//		for(Polyhedron::Vertex_iterator vit=basissummesh->vertices_begin(); vit!=basissummesh->vertices_end(); vit++)
//		{
//			out << vit->point().x() << " " << vit->point().y() << " " << vit->point().z() << endl;
//
//		}
//		file.close();
//		}
//		if(!basissummesh)
//			return;
//		Iso_cuboid cube = basissummesh->bbox();
//		Bbox_3 box = cube.bbox();
//		box = Bbox_3(box.xmin(), box.ymin(), 0, box.xmax(), box.ymax(), 1);
//		set_scene(box);
//	}
//	updateGL();
//}
//
//void SplineKnotsViewer::set_basis_index(int &index)
//{
//	basis_index = index;
//	//surfacedata->get_basis_polyhedron(index);
//	updateGL();
//}

//void SplineKnotsViewer::set_basis_knots_view(bool bv)
//{
//	bbasis_knots = bv;
//	updateGL();
//}
//
//void SplineKnotsViewer::triangular_test()
//{
//	vector<pair<unsigned, unsigned>> samePairs;
//	int count = surfacedata->triangular_test(samePairs);
//	QString str = "The number of configurations with only one triangle as their boundary is: ";
//	str.append(QString::number(count));
//	str.append("\n");
//	for (int i=0; i<samePairs.size(); i++)
//	{
//		str.append("(");
//		str.append(QString::number(samePairs[i].first));
//		str.append(", ");
//		str.append(QString::number(samePairs[i].second));
//		str.append("), ");
//	}
//	
//	QMessageBox::information(this, "Number of similar basis", str, QMessageBox::Yes, QMessageBox::Yes);
//}
//
//void SplineKnotsViewer::save_data()
//{
//	// QString fileName = QFileDialog::getSaveFileName(this,
// //                              tr("Save Mesh"), ".",
// //                              tr("Mesh files (*.off *.obj *.txt)"));
// //   if (fileName.isEmpty())
// //       return;
//
//	//if(bbasisview  && basis_index>=0)
//	//{
//	//	vector<SplineBasis> basisCollection = surfacedata->get_spline_basis();
//	//	QFile file( fileName);
//	//	if ( file.open(QIODevice::WriteOnly)) 
//	//	{
//	//		QTextStream out( &file );
//	//		for(int i=0; i<basisCollection[basis_index].indices.size(); i++)
//	//		{
//	//			out << basisCollection[basis_index].basis[i]<<endl;
//	//		}
//	//		file.close();
//	//	}
//	//}
//
//	//Polyhedron *mesh = NULL;
//
//	//if(bdomainview)
//	//	mesh = surfacedata->get_domain_mesh();
//	///*else if(bbasisview && basis_index>=0)
//	//	mesh = surfacedata->get_basis_polyhedron(basis_index);*/
//	//else if(bbasissumview)
//	//	mesh = surfacedata->get_basis_sum_polyhedron();
//
//	//if(mesh)
//	//	mesh->write_obj(fileName, true);
//}

//void SplineKnotsViewer::set_basis_support_view(bool bv)
//{
//	bbasis_support = bv;
//
//	if(basis_index>=0)
//	{
//		QFile file("./Record/basis.txt");
//		if ( file.open(QIODevice::WriteOnly)) 
//		{
//			QTextStream out( &file );
//			vector<Point_2> pts;
//			vector<SplineBasis> basisCollection = surfacedata->get_basis_collection();
//			vector<vector<unsigned>>::iterator it = basisCollection[basis_index].boundaries.begin();
//			out << "Boundaries:" << endl;
//			for(; it!=basisCollection[basis_index].boundaries.end(); it++)
//			{
//				out << it->at(0) << " " << it->at(1) << " " << it->at(2) << endl;
//			}
//			vector<unsigned>::iterator in_it = basisCollection[basis_index].interior.begin();
//			out << "Interior:" << endl;
//			for(; in_it!=basisCollection[basis_index].interior.end(); in_it++)
//			{
//				out << *in_it << " ";
//			}
//			out << endl;
//			//out << basisCollection[basis_index].interior
//			surfacedata->get_basis_knots(pts, basis_index);
//			for(int i=0; i<pts.size(); i++)
//			{
//				out << pts[i].x() << " " << pts[i].y() << endl;
//			}
//			out << endl;
//			vector<Point_2> basis_convex_hull = surfacedata->get_basis_convex_hull(basis_index);
//			int sz = basis_convex_hull.size();
//			for(int i=0; i<sz; i++)
//			{
//					out << basis_convex_hull[i].x() << " " << basis_convex_hull[i].y() << endl;
//			}
//			file.close();
//		}
//	}
//}
//
//void SplineKnotsViewer::draw_basis_suport()
//{
//	if(basis_index<0)
//		return;
//
//	vector<Point_2> basis_convex_hull = surfacedata->get_basis_convex_hull(basis_index);
//	glColor3d(0.0, 1.0, 0.0);
//	glLineWidth(1.0f);
//	int sz = basis_convex_hull.size();
//	glBegin(GL_LINE_LOOP);
//		for(int i=0; i<sz; i++)
//		{
//			glVertex2d(basis_convex_hull[i].x(), basis_convex_hull[i].y());
//		}
//	glEnd();
//
//	vector<vector<Point_2>> boundaries;
//	vector<Point_2> interior;
//	SplineBasis basis;
//	surfacedata->getBasisInfo(boundaries, interior, basis, basis_index);
//
//	glColor3d(0.0, 0.0, 1.0);
//	glLineWidth(1.0f);
//	sz = boundaries.size();
//	for(int i=0; i<sz; i++)
//	{
//		glBegin(GL_LINE_LOOP);
//		for (int j=0; j<3; j++)
//		{
//			glVertex2d(boundaries[i][j].x(), boundaries[i][j].y());
//		}
//		glEnd();
//	}
//	glColor3d(1.0, 1.0, 0.0);
//	glPointSize(4.0f);
//	glBegin(GL_POINTS);
//	for(int i=0; i<interior.size(); i++)
//	{
//		glVertex2d(interior[i].x(), interior[i].y());
//	}
//	glEnd();
//}
//
//void SplineKnotsViewer::set_triangulation_view(bool tv)
//{
//	btriangulation_view = tv;
//}
//
//void SplineKnotsViewer::draw_triangulation()
//{
//	if(!surfacedata)
//		return;
//
//	vector<BoundaryInteriorConfigs> configsk;
//	surfacedata->get_configsk(configsk);
//	vector<Knot_Data> knots = surfacedata->get_knots();
//
//	vector<BoundaryInteriorConfigs>::iterator it = configsk.begin();
//	glColor3d(0.0, 0.0, 0.0);
//	glLineWidth(2.0f);
//	for(; it!=configsk.end(); it++)
//	{
//		glBegin(GL_LINE_LOOP);
//			for(int i=0;i<3;i++)
//			{ 				
//				glVertex2d(knots[it->boundary[i]].pt.x(), knots[it->boundary[i]].pt.y());	
//			}
//		glEnd();
//	}
//}
//
//void SplineKnotsViewer::set_delaunay_view(bool dv)
//{
//	bdelaunayview = dv;
//}
//
//void SplineKnotsViewer::set_ddt_view(bool dv)
//{
//	bddtview = dv;
//}
//
//void SplineKnotsViewer::draw_delaunay()
//{
//	if(!surfacedata)
//		return;
//	vector<BoundaryInteriorConfigs> delaunay_configs = surfacedata->get_configs0();
//	vector<Knot_Data> knots = surfacedata->get_knots();
//
//	vector<BoundaryInteriorConfigs>::iterator it = delaunay_configs.begin();
//	glColor3d(0.0, 0.0, 0.0);
//	glLineWidth(2.0f);
//	for(; it!=delaunay_configs.end(); it++)
//	{
//		glBegin(GL_LINE_LOOP);
//			for(int i=0;i<3;i++)
//			{ 				
//				glVertex2d(knots[it->boundary[i]].pt.x(), knots[it->boundary[i]].pt.y());	
//			}
//		glEnd();
//	}
//}
//
//void SplineKnotsViewer::draw_ddt()
//{
//	if(!surfacedata)
//		return;
//
//	vector<BoundaryInteriorConfigs> ddt_configs = surfacedata->get_configs0();
//	vector<Knot_Data> knots = surfacedata->get_knots();
//	//vector<Knot> knots = surfacedata->get_multiple_knots();
//
//	vector<BoundaryInteriorConfigs>::iterator it = ddt_configs.begin();
//	glColor3d(0.0, 0.0, 0.0);
//	glLineWidth(2.0f);
//	for(; it!=ddt_configs.end(); it++)
//	{
//		glBegin(GL_LINE_LOOP);
//			for(int i=0;i<3;i++)
//			{ 				
//				glVertex2d(knots[it->boundary[i]].pt.x(), knots[it->boundary[i]].pt.y());	
//			}
//		glEnd();
//	}
//}
//
//void SplineKnotsViewer::set_feature_blocks(bool fv)
//{
//	if(fv)
//	{
//		vector<Insert_Knot> triangles = surfacedata->get_error_triangles();
//		int num = triangles.size();
//		QString s = QString::number(num, 10);
//		QMessageBox::information(this, tr("The size of the error triangles."), s); 
//	}
//	bfeatureview = fv;
//}
//
//void SplineKnotsViewer::draw_feature_hull()
//{
//	if(!surfacedata)
//		return;
//
//	glColor3d(0.0, 1.0, 0.0);
//	glLineWidth(2.0f);
//
//	vector<Knot_Data> knots = surfacedata->get_knots();
//	vector<Insert_Knot> triangles = surfacedata->get_error_triangles();
//	for(int i=0; i<triangles.size(); i++)
//	{
//		glBegin(GL_LINE_LOOP);
//			for(int j=0;j<3;j++)
//			{ 				
//				glVertex2d(knots[triangles[i].triangle[j]].pt.x(), knots[triangles[i].triangle[j]].pt.y());
//			}
//		glEnd();
//	}
//	glColor3d(1.0, 0.0, 1.0);
//	glPointSize(4.0);
//	glBegin(GL_POINTS);
//	for(int i=0; i<triangles.size(); i++)
//	{		
//		glVertex2d(triangles[i].pt.x(), triangles[i].pt.y());
//	}
//	glEnd();
//}
//
//void SplineKnotsViewer::set_density_threshold()
//{
//	if(bfeatureview)
//	{
//		bool ok = false;
//		double thres = 
//					QInputDialog::getDouble(this, 
//											tr("Density Threshold"),
//											tr("Please input number:"),
//								0.5,
//								0,
//								1,
//								5,
//								&ok);
//		//if(ok)
//		//{
//		//	surfacedata->set_density_threshold(thres);
//		//}
//	}
//}
//
void SplineKnotsViewer::set_domain_mesh_view(bool dv)
{
	bmeshdomainview=dv;
	updateGL();
}
	
void SplineKnotsViewer::set_error_domain_view(bool ev)
{
	berrordomainview = ev;
	 berror_show=false;
	 bcurvature_show=false;
	updateGL();
}

//void SplineKnotsViewer::set_density_domain_view(bool ev)
//{
//	bdensitydomainview = ev;
//	if(ev)
//	{
//		surfacedata->get_domain_mesh();
//		surfacedata->set_domain_color(0);
//	}
//}
//
//void SplineKnotsViewer::set_thintriangles_view(bool tv)
//{
//	bthintrianglesview = tv;
//	if(tv)
//	{
//		bool ok = false;
//		double thres = 
//					QInputDialog::getDouble(this, 
//											tr("Area ratio Threshold"),
//											tr("Please input number:"),
//								10,
//								1,
//								100,
//								5,
//								&ok);
//		if(!ok)
//			return;
//		thres = 1/thres;
//		vector<vector<unsigned>> triangles = surfacedata->get_thin_triangles(thres);
//		int sz = triangles.size();
//		QString s = QString::number(sz, 10);
//		QMessageBox::information(this, tr("The size of the thin triangles."), s); 
//	}
//}
//
//void SplineKnotsViewer::draw_thin_triangles()
//{
//	if(!surfacedata)
//		return;
//
//	glColor3d(0.5, 1.0, 0.5);
//	glLineWidth(2.0f);
//
//	vector<Knot_Data> knots = surfacedata->get_knots();
//	vector<vector<unsigned>> triangles = surfacedata->get_thin_triangles();
//	for(int i=0; i<triangles.size(); i++)
//	{
//		glBegin(GL_LINE_LOOP);
//			for(int j=0;j<3;j++)
//			{ 				
//				glVertex2d(knots[triangles[i][j]].pt.x(), knots[triangles[i][j]].pt.y());
//			}
//		glEnd();
//	}
//}
//
//void SplineKnotsViewer::draw_thin_triangles_angle()
//{
//	if(!surfacedata)
//		return;
//
//	glColor3d(0.0, 1.0, 1.0);
//	glLineWidth(2.0f);
//
//	vector<Knot_Data> knots = surfacedata->get_knots();
//	vector<vector<unsigned>> triangles = surfacedata->get_thin_triangles_angle();
//	for(int i=0; i<triangles.size(); i++)
//	{
//		glBegin(GL_LINE_LOOP);
//			for(int j=0;j<3;j++)
//			{ 				
//				glVertex2d(knots[triangles[i][j]].pt.x(), knots[triangles[i][j]].pt.y());
//			}
//		glEnd();
//	}
//}
//
//void SplineKnotsViewer::set_thintriangles_angle_view(bool av)
//{
//	thintrianglesangle_view = av;
//	if(av)
//	{
//		bool ok = false;
//		double thres = 
//					QInputDialog::getDouble(this, 
//											tr("Area ratio Threshold"),
//											tr("Please input number:"),
//								160,
//								90,
//								180,
//								5,
//								&ok);
//		if(!ok)
//			return;
//		thres = thres*M_PI/180;
//		vector<vector<unsigned>> triangles = surfacedata->get_thin_triangles_angle(thres);
//		int sz = triangles.size();
//		QString s = QString::number(sz, 10);
//		QMessageBox::information(this, tr("The size of the thin triangles."), s); 
//	}
//}
//
//void SplineKnotsViewer::set_principal_direction_view(bool pv)
//{
//
//}
//
//void SplineKnotsViewer::draw_principal_directions()
//{
//	
//}