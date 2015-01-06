#include <OpenMesh/Core/IO/MeshIO.hh>//必须放在首行
#include "bsplinesurface.h"
#include<QMdiSubWindow>

bsplinesurface::bsplinesurface(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

  QObject::connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(load_mesh()));
  ui.subwindow_0->ui.centralwidget->mesh=mesh_;
 // ui.subwindow_0->ui.centralwidget->draw();
  ui.subwindow_0->ui.centralwidget->center1=center1;
  ui.subwindow_0->ui.centralwidget->radius=radius;
}

bsplinesurface::~bsplinesurface()
{

}
bool  bsplinesurface::load_mesh()
{

	QString filename;
	filename=QFileDialog::getOpenFileName(this,"open a file","C:/Users/asus/Desktop/bspline3_total_deboor/bsplinesurface/bsplinesurface/model","objectfile(*.obj  *.off  *.stl)") ;  
	if (filename==NULL)   //如果成功的执行
	{
		return false;
	}
	else
	{
		std::string s = filename.toStdString();//qstring转string
		mesh_.clear();
		readmesh(s);
		return true;
	}

}
bool bsplinesurface::readmesh(const string _filename)
{

	//load mesh
	if (OpenMesh::IO::read_mesh(mesh_, _filename))
	{
		// set center and radius
		Mesh::ConstVertexIter  v_it(mesh_.vertices_begin()), 
			v_end(mesh_.vertices_end());
		Mesh::Point            bbMin, bbMax;

		bbMin = bbMax = mesh_.point(v_it);
		for (; v_it!=v_end; ++v_it)
		{
			bbMin.minimize(mesh_.point(v_it));
			bbMax.maximize(mesh_.point(v_it));
		}
		center1= (OpenMesh::Vec3f)(bbMin + bbMax)*0.5;
		radius=0.5*(bbMin - bbMax).norm();

		//compute face & vertex normals
		mesh_.update_normals();


		return true;
	}

	return false;
}
bool bsplinesurface::save()
{
	return true;
}
bool  bsplinesurface::saveAs()
{
	return true;

}