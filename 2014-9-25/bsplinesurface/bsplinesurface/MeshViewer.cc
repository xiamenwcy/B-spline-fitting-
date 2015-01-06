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

#include <OpenMesh/Core/IO/MeshIO.hh>
#include "MeshViewer.hh"


//== IMPLEMENTATION ========================================================== 


MeshViewer::
MeshViewer()
{
	mesh_.request_face_normals();
   mesh_.request_vertex_normals();
 center1[0]=center1[1]=center1[2]=0;
 radius=1;
  

  
}

//-----------------------------------------------------------------------------


bool
MeshViewer::
open_mesh(const string _filename)
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
		center1= (OpenMesh::Vec3d)(bbMin + bbMax)*0.5;
		radius=0.5*(bbMin - bbMax).norm();
     //compute face & vertex normals
    mesh_.update_normals();

    // update face indices for faster rendering
    update_face_indices();

    return true;
  }

  return false;
}


//-----------------------------------------------------------------------------


void
MeshViewer::
update_face_indices()
{
  Mesh::ConstFaceIter        f_it(mesh_.faces_sbegin()), 
                             f_end(mesh_.faces_end());
  Mesh::ConstFaceVertexIter  fv_it;

  indices_.clear();
  indices_.reserve(mesh_.n_faces()*3);
  std::cout << "mesh indices updated" << std::endl;

  for (; f_it!=f_end; ++f_it)
  {
    indices_.push_back((fv_it=mesh_.cfv_iter(f_it)).handle().idx());
    indices_.push_back((++fv_it).handle().idx());
    indices_.push_back((++fv_it).handle().idx());
  }
}


//-----------------------------------------------------------------------------


void 
MeshViewer::
drawscene()
{
 //triangle drawing
   Mesh::ConstFaceIter        f_it(mesh_.faces_begin()), 
                               f_end(mesh_.faces_end());
    Mesh::ConstFaceVertexIter  fv_it;

    glEnable(GL_LIGHTING);
    glShadeModel(GL_FLAT);

    glBegin(GL_TRIANGLES);
    for (; f_it!=f_end; ++f_it)
    {
      GL::glNormal(mesh_.normal(f_it));
      fv_it = mesh_.cfv_iter(f_it.handle()); 
      GL::glVertex(mesh_.point(fv_it));
      ++fv_it;
      GL::glVertex(mesh_.point(fv_it));
      ++fv_it;
      GL::glVertex(mesh_.point(fv_it));
    }
    glEnd();
  glFlush();


}


//=============================================================================
