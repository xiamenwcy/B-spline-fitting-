

#include <Windows.h>
#include "draw.h"
#include"BSplineView.h"
#include <iostream>
using namespace std;



int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("双三次B样条曲面");

	Initialization();
	glutDisplayFunc(OnDisplay);
	glutReshapeFunc(OnReshape);
	
	glutMainLoop();
	return 0;
}


GLvoid Initialization()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	glEnable(GL_DEPTH_TEST);
	


}

GLvoid OnReshape(int w, int h)
{
	GLfloat  aspect;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w <= h)
	{
		aspect = GLfloat(h) /GLfloat(w);
		gluOrtho2D(-5.0f, 5.0f, -5.0f * aspect, 5 * aspect);
	}else{
		aspect = GLfloat(w) /GLfloat(h);
		gluOrtho2D(-5.0f * aspect, 5 * aspect, -5.0f, 5.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


GLvoid OnDisplay()
{
	
	CBSplineSurfaceView surface;
	surface.GenerateKnots(1);
	surface.solve_bspline(surface.ControlPoint,M,N,p,q,surface.uknots,surface.vknots,surface.ptPts);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
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
	glPopMatrix();

	glutSwapBuffers();


}





