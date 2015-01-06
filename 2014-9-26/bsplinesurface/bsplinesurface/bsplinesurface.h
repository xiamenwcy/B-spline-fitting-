#ifndef BSPLINESURFACE_H
#define BSPLINESURFACE_H

#include <QtGui/QMainWindow>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include "ui_bsplinesurface.h"
#include <QtGui/QFileDialog>
#include <QtCore/QString>
#include <OpenMesh/Core/Geometry/VectorT.hh>
#include <fstream>
#include <iostream>
using namespace std;


 typedef OpenMesh::TriMesh_ArrayKernelT<>  Mesh;

class bsplinesurface : public QMainWindow
{
	Q_OBJECT

public:
	bsplinesurface(QWidget *parent = 0, Qt::WFlags flags = 0);
	~bsplinesurface();

private:
	Ui::bsplinesurfaceClass ui;

public slots:
		bool  load_mesh(); 
		bool save();
		bool saveAs();
public:
	/// read mesh
	bool readmesh(const string _filename);
	/// update buffer with face indices
	void update_face_indices();

public:
	Mesh                  mesh_;
	OpenMesh::Vec3f   center1;//设置场景的中心
	double  radius;//设置场景的半径
   
};

#endif // BSPLINESURFACE_H
