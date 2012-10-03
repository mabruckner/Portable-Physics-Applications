#include <GL/glut.h>

#include "Algorithms.h"
#include "Point.h"

#define MAX_POINTS 256

void redraw(void){
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0,0.0,1.0);
		glVertex3f(5.0,0.0,0.0);
		glVertex3f(0.0,5.0,0.0);
		glVertex3f(0.0,0.0,5.0);
	glEnd();
	glutSolidSphere(5,16,16);
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("HELLO WORLD");
	glutDisplayFunc(redraw);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10,10,-10,10,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutMainLoop();
	Point p;
	euler(&p,10,10,10,1);
	return 0;
}
