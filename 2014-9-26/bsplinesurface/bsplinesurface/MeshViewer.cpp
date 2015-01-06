//=============================================================================
//                                                
//   Code framework for the lecture
//
//   "Surface Representation and Geometric Modeling"
//
//   Mark Pauly, Mario Botsch, Balint Miklos, and Hao Li
//
//   Copyright (C) 2007 by  Applied Geometry Group and 
//							Computer Graphics Laboratory, ETH Zurich
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
//  CLASS MeshViewer - IMPLEMENTATION
//
//=============================================================================


//== INCLUDES =================================================================


#include "MeshViewer.h"


//== IMPLEMENTATION ========================================================== 

// Constructor must call the base class constructor.
MeshViewer::MeshViewer(QWidget *parent)
: QGLViewer(parent)
{
	
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mesh.request_face_normals();
	mesh.request_vertex_normals();
	center1[0]=center1[1]=center1[2]=0;
	radius=1;


}
void MeshViewer::init()
{
	
	restoreStateFromFile();
	Vec center2;
	center2.setValue(center1[0],center1[1],center1[2]);
    setSceneCenter(center2);
	setSceneRadius(radius);
	showEntireScene();
}

//-----------------------------------------------------------------------------



void MeshViewer::draw()
{
 //triangle drawing
   Mesh::ConstFaceIter        f_it(mesh.faces_begin()), 
                               f_end(mesh.faces_end());
    Mesh::ConstFaceVertexIter  fv_it;

    glEnable(GL_LIGHTING);
    glShadeModel(GL_FLAT);

    glBegin(GL_TRIANGLES);
    for (; f_it!=f_end; ++f_it)
    {
      GL::glNormal(mesh.normal(f_it));
      fv_it = mesh.cfv_iter(f_it.handle()); 
      GL::glVertex(mesh.point(fv_it));
      ++fv_it;
      GL::glVertex(mesh.point(fv_it));
      ++fv_it;
      GL::glVertex(mesh.point(fv_it));
    }
    glEnd();
}


//=============================================================================
