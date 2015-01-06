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


// Constructor must call the base class constructor.
viewer0::viewer0(QWidget *parent)
	: QGLViewer(parent),MeshViewer()
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
	drawscene();
	}
			
}


