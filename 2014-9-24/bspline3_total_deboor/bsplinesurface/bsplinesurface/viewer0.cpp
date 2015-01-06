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

#include "viewer0.h"
#include <QGLViewer/vec.h>
#include <iostream>
using namespace std;
using namespace qglviewer;

// Constructor must call the base class constructor.
viewer0::viewer0(QWidget *parent)
	: QGLViewer(parent)
{
  restoreStateFromFile();
  flag=false;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 
}
void viewer0::init()
{
	// Make sure the manipulatedFrame is not easily clipped by the zNear and zFar planes
	setSceneRadius(30);
	camera()->fitSphere(Vec(0,0,0), 1);

	restoreStateFromFile();
	
}
void viewer0::draw()
{
	if (flag==true)
	{
	//	CFileDialog dlg(TRUE, LPCTSTR("off"), LPCTSTR("*.off"));
	//	if (dlg.DoModal() == IDOK)
	//	{
	//		mesh_.clear();
	//		open_mesh(dlg.GetPathName().GetBuffer());
	//		setSceneRadius(radius);
	//		Vec center2;
	//		center2.setValue(center1[0],center1[1],center1[2]);
 //           camera()->fitSphere(Vec(0,0,0), 1);//¸Ä³Écamera()->fitSphere(center2, 1);
	//	}
	
	const float nbSteps = 200.0;

	glBegin(GL_QUAD_STRIP);
	for (int i=0; i<nbSteps; ++i)
	{
		const float ratio = i/nbSteps;
		const float angle = 21.0*ratio;
		const float c = cos(angle);
		const float s = sin(angle);
		const float r1 = 1.0 - 0.8f*ratio;
		const float r2 = 0.8f - 0.8f*ratio;
		const float alt = ratio - 0.5f;
		const float nor = 0.5f;
		const float up = sqrt(1.0-nor*nor);
		glColor3f(1.0-ratio, 0.2f , ratio);
		glNormal3f(nor*c, up, nor*s);
		glVertex3f(r1*c, alt, r1*s);
		glVertex3f(r2*c, alt+0.05f, r2*s);
	}
	glEnd();

	}
	
		
}


