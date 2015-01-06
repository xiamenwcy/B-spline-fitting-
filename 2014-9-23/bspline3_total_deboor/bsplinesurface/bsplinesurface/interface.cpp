/****************************************************************************

 Copyright (C) 2002-2013 Gilles Debunne. All rights reserved.

 This file is part of the QGLViewer library version 2.5.2.

 http://www.libqglviewer.com - contact@libqglviewer.com

 This file may be used under the terms of the GNU General Public License 
 versions 2.0 or 3.0 as published by the Free Software Foundation and
 appearing in the LICENSE file included in the packaging of this file.
 In addition, as a special exception, Gilles Debunne gives you certain 
 additional rights, described in the file GPL_EXCEPTION in this package.

 libQGLViewer uses dual licensing. Commercial/proprietary software must
 purchase a libQGLViewer Commercial License.

 This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

*****************************************************************************/

#include "interface.h"
#include <math.h>
#include <QGLViewer/vec.h>
#include <iostream>
using namespace std;
using namespace qglviewer;

// Constructor must call the base class constructor.
Viewer::Viewer(QWidget *parent)
	: QGLViewer(parent)
{
  restoreStateFromFile();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  surface.GenerateKnots(1);
  surface.solve_bspline(surface.ControlPoint,M,N,p,q,surface.uknots,surface.vknots,surface.ptPts);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 
}
void Viewer::init()
{
	// Make sure the manipulatedFrame is not easily clipped by the zNear and zFar planes
	setSceneRadius(30);
	camera()->fitSphere(Vec(0,0,0), 1);

	restoreStateFromFile();
	
}
void Viewer::draw()
{
	/*glPushMatrix();
	glTranslated(0, 0.5, 0);
	glRotated(30.0, 1.0, 0.0, 0.0);
	glRotated(25.0, 0.0, 1.0, 0.0);

	glColor3d(1.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	
	for(int i=1;i<=npoints;i++)
		for(int j=0;j<mpoints;j++)
		{
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3d(surface.ptPts[i-1][j].x,surface.ptPts[i-1][j].y,surface.ptPts[i-1][j].z);
			glVertex3d(surface.ptPts[i][j].x,surface.ptPts[i][j].y,surface.ptPts[i][j].z);
			glVertex3d(surface.ptPts[i-1][j+1].x,surface.ptPts[i-1][j+1].y,surface.ptPts[i-1][j+1].z);
			glVertex3d(surface.ptPts[i][j+1].x,surface.ptPts[i][j+1].y,surface.ptPts[i][j+1].z);
			glEnd();
		}
		
glPopMatrix();*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(0, -1.0f, 0);
	glRotated(30.0, 1.0, 0.0, 0.0);
	glRotated(25.0, 0.0, 1.0, 0.0);
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	glColor3d(1,0,0.0);

	int i,j;
	for (i=0;i<mpoints+1;i++)
	{
		glBegin(GL_LINE_STRIP);	
		for (j=0;j<npoints+1;j++)
		{
			glVertex3d(surface.ptPts[i][j].x,surface.ptPts[i][j].y,surface.ptPts[i][j].z);

		}
		glEnd();
	}
	for (j=0;j<npoints+1;j++)
	{
		glBegin(GL_LINE_STRIP);	
		for (i=0;i<mpoints+1;i++)
		{
			glVertex3d(surface.ptPts[i][j].x,surface.ptPts[i][j].y,surface.ptPts[i][j].z);

		}
		glEnd();
	}

	glColor3d(0.0,1.0,0.0);
	glLineWidth(2);

	for (i=0;i<M+1;i++)
	{
		glBegin(GL_LINE_STRIP);	
		for (j=0;j<N+1;j++)
		{
			glVertex3f(surface.ControlPoint[i][j].x,surface.ControlPoint[i][j].y,surface.ControlPoint[i][j].z);

		}
		glEnd();
	}
	for (j=0;j<N+1;j++)
	{
		glBegin(GL_LINE_STRIP);	
		for (i=0;i<M+1;i++)
		{
			glVertex3f(surface.ControlPoint[i][j].x,surface.ControlPoint[i][j].y,surface.ControlPoint[i][j].z);

		}
		glEnd();
	}

	glPopMatrix();


	
}


