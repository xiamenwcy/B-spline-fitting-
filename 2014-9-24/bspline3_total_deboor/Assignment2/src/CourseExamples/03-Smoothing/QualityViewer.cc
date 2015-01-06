//=============================================================================
//                                                                            
//   Example code for the full-day course
//
//   M. Botsch, M. Pauly, C. Roessl, S. Bischoff, L. Kobbelt,
//   "Geometric Modeling Based on Triangle Meshes"
//   held at SIGGRAPH 2006, Boston, and Eurographics 2006, Vienna.
//
//   Copyright (C) 2006 by  Computer Graphics Laboratory, ETH Zurich, 
//                      and Computer Graphics Group,      RWTH Aachen
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
//  CLASS QualityViewer - IMPLEMENTATION
//
//=============================================================================


//== INCLUDES =================================================================

#include "QualityViewer.hh"
#include <vector>
#include <float.h>



//== IMPLEMENTATION ========================================================== 


QualityViewer::
QualityViewer(const char* _title, int _width, int _height)
: MeshViewer(_title, _width, _height)
{ 
	mesh_.request_vertex_colors();

	mesh_.add_property(tshape_);
	mesh_.add_property(vgausscurvature_);

	mesh_.add_property(vcurvature_);
	mesh_.add_property(vunicurvature_);
	mesh_.add_property(eweight_);

	



	add_draw_mode("Gaussian Curvature");
	add_draw_mode("Triangle Shape");
	add_draw_mode("Reflection Lines");

	init();
}


//-----------------------------------------------------------------------------


QualityViewer::
~QualityViewer()
{
	if (glIsTexture(textureID_))  
		glDeleteTextures( 1, &textureID_);
}

//-----------------------------------------------------------------------------


void
QualityViewer::
init()
{
	// base class first
	MeshViewer::init();


	// generate checkerboard-like image
	GLubyte tex[256*256*3], *tp=tex;
	for (int x=0; x<256; ++x)
		for (int y=0; y<256; ++y)
			if (((x+2)/4 % 10) == 0 || ((y+2)/4 % 10) == 0)
			{
				*(tp++) = 0;
				*(tp++) = 0;
				*(tp++) = 0;
			}
			else
			{
				*(tp++) = 255;
				*(tp++) = 255;
				*(tp++) = 255;
			}


			// generate texture
			if (!glIsTexture(textureID_))
				glGenTextures(1, &textureID_);
			glBindTexture(GL_TEXTURE_2D, textureID_);


			// copy texture to GL
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256,
				0, GL_RGB, GL_UNSIGNED_BYTE, tex);
}



//-----------------------------------------------------------------------------


bool
QualityViewer::
open_mesh(const char* _filename)
{
	// load mesh
	if (MeshViewer::open_mesh(_filename))
	{
		// compute curvature stuff
		calc_weights();
		calc_mean_curvature();
		calc_uniform_mean_curvature();
		calc_gauss_curvature();
		calc_triangle_quality();
		face_color_coding();

		glutPostRedisplay();
		return true;
	}
	return false;
}


//-----------------------------------------------------------------------------

void 
QualityViewer::
calc_triangle_quality()
{
	// ------------- IMPLEMENT HERE ---------
	// TASK 2.2 Compute triangle shape measure and save it in the tshape_ property
	// For numerical stability you might want to set the property value to
	// a predifined large value (e.g. FLT_MAX) if the denominator is smaller than FLT_MIN
	// ------------- IMPLEMENT HERE ---------

}


void 
QualityViewer::
calc_gauss_curvature()
{
	// ------------- IMPLEMENT HERE ---------
	// TASK 2.3 Approximate Gaussian curvature.
	// Hint: When calculating angles out of cross products make sure the value 
	// you pass to the acos function is between -1.0 and 1.0.
	// ------------- IMPLEMENT HERE ---------


}

//-----------------------------------------------------------------------------


void 
QualityViewer::
calc_uniform_mean_curvature()
{
	// ------------- IMPLEMENT HERE ---------
	// Bonus.a Approximate mean curvature using the length of the uniform Laplacian approximation
	// Save your approximation in vunicurvature_ vertex property of the mesh.
	// ------------- IMPLEMENT HERE ---------

}

void
QualityViewer::
calc_weights()
{
		// ------------- IMPLEMENT HERE ---------
	// Bonus.b Compute cotangent weights for laplacian, and produce them in the mesh edge property eweight_
	// Use the weights from calc_weights(): eweight_
	// ------------- IMPLEMENT HERE ---------
}


//-----------------------------------------------------------------------------


void 
QualityViewer::
calc_mean_curvature()
{
	// ------------- IMPLEMENT HERE ---------
	// Bonus.c. Approximate mean curvature using the length of the Laplace-Beltrami approximation
	// Save your approximation in vcurvature_ vertex property of the mesh.
	// Use the weights from calc_weights(): eweight_
	// ------------- IMPLEMENT HERE ---------

}



//-----------------------------------------------------------------------------

void 
QualityViewer::
face_color_coding()
{
	Mesh::ConstFaceIter        f_it, f_end(mesh_.faces_end());
	Mesh::Scalar      sh, min_shape(FLT_MAX), max_shape(-FLT_MAX);
	Mesh::Color       col;

	face_colors_.clear();
	face_colors_.reserve(mesh_.n_faces()*3);

	min_shape = 0.6f;
	max_shape = 2.0f;

	// map curvatures to colors
	for (f_it = mesh_.faces_sbegin(); f_it!=f_end; ++f_it)
	{
		sh = mesh_.property(tshape_,f_it);
		col = value_to_color(sh, min_shape, max_shape);

		face_colors_.push_back((float)col[0]/255);
		face_colors_.push_back((float)col[1]/255);
		face_colors_.push_back((float)col[2]/255);
	}
}



//-----------------------------------------------------------------------------


void 
QualityViewer::
color_coding(Vertex_property prop)
{
	Mesh::VertexIter  v_it, v_end(mesh_.vertices_end());
	Mesh::Scalar      curv, min(FLT_MAX), max(-FLT_MAX);
	Mesh::Color       col;
	
	// put all values into one array
	std::vector<Mesh::Scalar> values;
	values.reserve(mesh_.n_vertices());
	for (v_it=mesh_.vertices_begin(); v_it!=v_end; ++v_it)
		values.push_back(mesh_.property(prop, v_it));

	//discard upper and lower 5%
	unsigned int n = values.size()-1;
	unsigned int i = n / 20;
	std::sort(values.begin(), values.end());
	min = values[i];
	max = values[n-1-i];

	// map curvatures to colors
	for (v_it=mesh_.vertices_begin(); v_it!=v_end; ++v_it)
	{
		curv = mesh_.property(prop, v_it);
		mesh_.set_color(v_it, value_to_color(curv, min, max));
	}
}


QualityViewer::Mesh::Color 
QualityViewer::
value_to_color(QualityViewer::Mesh::Scalar value, QualityViewer::Mesh::Scalar min, QualityViewer::Mesh::Scalar max) {
	Mesh::Scalar v0, v1, v2, v3, v4;
	v0 = min + 0.0/4.0 * (max - min);
	v1 = min + 1.0/4.0 * (max - min);
	v2 = min + 2.0/4.0 * (max - min);
	v3 = min + 3.0/4.0 * (max - min);
	v4 = min + 4.0/4.0 * (max - min);

	Mesh::Color col = Mesh::Color(255,255,255);

	unsigned char u;

	if (value < v0) col = Mesh::Color(0, 0, 255);
	else if (value > v4) col = Mesh::Color(255, 0, 0);

	else if (value <= v2) 
	{
		if (value <= v1) // [v0, v1]
		{
			u = (unsigned char) (255.0 * (value - v0) / (v1 - v0));
			col = Mesh::Color(0, u, 255);
		}      
		else // ]v1, v2]
		{
			u = (unsigned char) (255.0 * (value - v1) / (v2 - v1));
			col = Mesh::Color(0, 255, 255-u);
		}
	}
	else 
	{
		if (value <= v3) // ]v2, v3]
		{
			u = (unsigned char) (255.0 * (value - v2) / (v3 - v2));
			col = Mesh::Color(u, 255, 0);
		}
		else // ]v3, v4]
		{
			u = (unsigned char) (255.0 * (value - v3) / (v4 - v3));
			col = Mesh::Color(255, 255-u, 0);
		}
	}

	return col;
}


//-----------------------------------------------------------------------------


void 
QualityViewer::
draw(const std::string& _draw_mode)
{

	if (indices_.empty())
	{
		MeshViewer::draw(_draw_mode);
		return;
	}


	if (_draw_mode == "Gaussian Curvature") color_coding(vgausscurvature_);
	if (_draw_mode == "Uniform Mean Curvature") color_coding(vunicurvature_);
	if (_draw_mode == "Mean Curvature") color_coding(vcurvature_);


	if (_draw_mode == "Mean Curvature" || _draw_mode == "Gaussian Curvature" || _draw_mode == "Uniform Mean Curvature")
	{

		glDisable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		GL::glVertexPointer(mesh_.points());
		GL::glNormalPointer(mesh_.vertex_normals());
		GL::glColorPointer(mesh_.vertex_colors());
		
		glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, &indices_[0]);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

	}

	if (_draw_mode == "Triangle Shape")
	{

		glDisable(GL_LIGHTING);
		glShadeModel(GL_FLAT);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		GL::glVertexPointer(mesh_.points());
		GL::glNormalPointer(mesh_.vertex_normals());


		glDepthRange(0.01, 1.0);
		glBegin(GL_TRIANGLES);
		for (unsigned i=0; i<indices_.size(); i++)
		{
			if (i%3==0) glColor3f(face_colors_[i], face_colors_[i+1], face_colors_[i+2]);
			glArrayElement(indices_[i]);
		}
		glEnd();


		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		glColor3f(0.3, 0.3, 0.3);

		glEnableClientState(GL_VERTEX_ARRAY);
		GL::glVertexPointer(mesh_.points());

		glDrawBuffer(GL_BACK);
		glDepthRange(0.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDepthFunc(GL_LEQUAL);
		glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, &indices_[0]);

		glDisableClientState(GL_VERTEX_ARRAY);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDepthFunc(GL_LESS);
	}

	else if (_draw_mode == "Reflection Lines")
	{
		glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
		glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
		glEnable( GL_TEXTURE_GEN_S );
		glEnable( GL_TEXTURE_GEN_T );
		glEnable( GL_TEXTURE_2D );    
		glEnable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		GL::glVertexPointer(mesh_.points());
		GL::glNormalPointer(mesh_.vertex_normals());

		glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, &indices_[0]);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		glDisable( GL_TEXTURE_GEN_S );
		glDisable( GL_TEXTURE_GEN_T );
		glDisable( GL_TEXTURE_2D );
	}



	else MeshViewer::draw(_draw_mode);
}


//=============================================================================
