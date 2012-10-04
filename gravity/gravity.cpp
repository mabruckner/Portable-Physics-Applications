#include <vector>
#include <iostream>
#include <cmath>

#include <GL/glut.h>

#include "Algorithms.h"
#include "Point.h"

#define MAX_POINTS 256
using namespace std;

vector<Point> list;

pfloat tratio;

pfloat G;

pfloat dist(pfloat x1,pfloat y1,pfloat z1,pfloat x2,pfloat y2,pfloat z2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
}

void accvect(pfloat* ax,pfloat* ay,pfloat* az,pfloat x,pfloat y,pfloat z)
{
	pfloat ox=0.0;
	pfloat oy=0.0;
	pfloat oz=0.0;
	for(int i=0;i<(int)list.size();i++){
		Point* p=&list[i];
		int n=(int)p->xpos.size()-1;
		pfloat d=dist(x,y,z,p->xpos[n],p->ypos[n],p->zpos[n]);
		if(d==0){
			continue;
		}
		pfloat mag=G*p->weight/(d*d);
		ox+=mag*(p->xpos[n]-x)/d;
		oy+=mag*(p->ypos[n]-y)/d;
		oz+=mag*(p->zpos[n]-z)/d;
	}
	*ax=ox;
	*ay=oy;
	*az=oz;
}

pfloat accmag(pfloat x,pfloat y,pfloat z)
{
	pfloat a,b,c;cout<<a<<","<<b<<","<<c<<endl;
	accvect(&a,&b,&c,x,y,z);cout<<a<<","<<b<<","<<c<<endl;
	return dist(a,b,c,0,0,0);
}

void redraw(void)
{
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
	list=vector<Point>();
	G=10;
	Point p;
	p.xpos.push_back(0);
	p.ypos.push_back(0);
	p.zpos.push_back(0);
	list.push_back(p);
	euler(&p,10,10,10,1);cout<<"HELLO WORLD?"<<endl;
	cout<<accmag(1,1,1)<<endl;cout<<(int)list.size()<<endl;


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
	return 0;
}
