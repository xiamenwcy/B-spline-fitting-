//=============================================================================
//                                                
//   Code framework for the lecture
//
//   "Surface Representation and Geometric Modeling"
//
//   Mark Pauly, Mario Botsch, Balint Miklos, and Hao Li
//
//   Copyright (C) 2007 by  Computer Graphics Laboratory, ETH Zurich
//
//                                                                            
//-----------------------------------------------------------------------------
//                                                                            
//                                License                                     
//                                                                            
//   This program is free software; you can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your option) any later version.
//   
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//   
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin Street, Fifth Floor, 
//   Boston, MA  02110-1301, USA.
//                                                                            
//=============================================================================
//=============================================================================
//
//  CLASS MeshViewerWidget
//
//=============================================================================


#ifndef MESH_VIEWER_WIDGET_HH
#define MESH_VIEWER_WIDGET_HH


//== INCLUDES =================================================================
#include <QGLViewer/qglviewer.h>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <QGLViewer/vec.h>
#include "gl.hh"
using namespace qglviewer;
//== CLASS DEFINITION =========================================================



 class MeshViewer:public QGLViewer 
{
public :
	MeshViewer(QWidget *parent);
protected :
	virtual void draw();
	virtual void init();
protected:

	typedef OpenMesh::TriMesh_ArrayKernelT<>  Mesh;

public:
   Mesh                  mesh;
  OpenMesh::Vec3f   center1;//设置场景的中心
  double  radius;//设置场景的半径

 
};


//=============================================================================
#endif // MESH_VIEWER_WIDGET_HH defined
//=============================================================================

