#include <vector>
#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GL/glut.h>

#include "Algorithms.h"
#include "Point.h"

#define MAX_POINTS 256
using namespace std;

vector<Point> list;

pfloat tratio;

pfloat G;

int timeindex;

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
		if(abs(d)<=.1){
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
	pfloat a,b,c;//cout<<a<<","<<b<<","<<c<<endl;
	accvect(&a,&b,&c,x,y,z);//cout<<a<<","<<b<<","<<c<<endl;
	return dist(a,b,c,0,0,0);
}

void resize(int w,int h)
{
	if(w==0){
		w=1;
	}
	float ratio=(float)h/w;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,w,h);
	glFrustum(-5,5,-ratio*5,ratio*5,5,100);
	glTranslatef(0,0,-20);
	glRotatef(-5,1,0,0);
}

void redraw(void)
{
	glClearColor(0.0,0.0,0.0,1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*glBegin(GL_TRIANGLES);
		glColor3f(1.0,0.0,1.0);
		glVertex3f(5.0,0.0,0.0);
		glVertex3f(0.0,5.0,0.0);
		glVertex3f(0.0,0.0,5.0);
	glEnd();*/
	glColor3f(0.0,.5,1.0);
	for(int i=0;i<(int)list.size();i++){
		Point* p=&list[i];
		int n=(int)p->xpos.size()-1;
		float r=sqrt(p->weight);
		glPushMatrix();
		glTranslatef(p->xpos[n],p->ypos[n],p->zpos[n]);
		glutSolidSphere(r,16,16);
		glPopMatrix();
	}
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUADS);
		float s=.125;
		float max=5;
		for(float i=-10;i<10;i+=s){
			for(float j=-10;j<10;j+=s){
				float a1=(float)accmag((pfloat)i,(pfloat)j,0);
				float a2=(float)accmag((pfloat)i+s,(pfloat)j,0);
				float a3=(float)accmag((pfloat)i+s,(pfloat)j+s,0);
				float a4=(float)accmag((pfloat)i,(pfloat)j+s,0);
				if(a1>max||a2>max||a3>max||a4>max){
					continue;
				}
				glColor3f(a1/2.0,1.0,1.0-a1/2.0);
				glVertex3f((float)i,(float)j,-a1*5);
				glColor3f(a2/2.0,1.0,1.0-a2/2.0);
				glVertex3f((float)i+s,(float)j,-a2*5);
				glColor3f(a3/2.0,1.0,1.0-a3/2.0);
				glVertex3f((float)i+s,(float)j+s,-a3*5);
				glColor3f(a4/2.0,1.0,1.0-a4/2.0);
				glVertex3f((float)i,(float)j+s,-a4*5);
			}
		}
	glEnd();
	glutSwapBuffers();
}

void step(void)
{
	pfloat xf[(int)list.size()];
	pfloat yf[(int)list.size()];
	pfloat zf[(int)list.size()];
	for(int i=0;i<(int)list.size();i++){
		accvect(xf+i,yf+i,zf+i,list[i].xpos[timeindex],list[i].ypos[timeindex],list[i].zpos[timeindex]);
	}//cout<<xf[0]<<","<<yf[0]<<","<<zf[0]<<" - "<<list[1].xpos[timeindex]<<endl;
	for(int i=0;i<(int)list.size();i++){
		euler(&(list[i]),xf[i],yf[i],zf[i],.01);
	}
	timeindex++;
	redraw();
}

int main(int argc, char** argv)
{
	list=vector<Point>();
	G=10;
	Point a;
	Point pt;pt.xacc[0]=1;
	for(int i=0;i<100;i++){
	euler(&pt,1,0,0,1);
	cout<<pt.xpos[i]<<endl;
	}
	
	timeindex=0;
	a.weight=5;
	a.xvel[0]=.4;
	a.yvel[0]=-.4;
	list.push_back(a);
	Point b;
	b.xpos[0]=-5;
	b.ypos[0]=-5;
	b.xvel[0]=-2;
	b.yvel[0]=2;
	b.weight=1;
	list.push_back(b);
	euler(&b,10,10,10,1);cout<<"HELLO WORLD?"<<endl;
	cout<<accmag(1,1,0)<<endl;cout<<(int)list.size()<<endl;


	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("HELLO WORLD");
	GLenum err=glewInit();
	if(err!=GLEW_OK){
		cout<<"ERROR: "<<glewGetErrorString(err)<<endl;
		return 0;
	}
	/*if (glewIsSupported("GL_VERSION_3_3"))
		cout<<"Ready for OpenGL 3.3\n";
	else {
		cout<<"OpenGL 3.3 not supported\n";
		exit(1);
	}*/

	glutDisplayFunc(redraw);
	glutIdleFunc(step);
	glutReshapeFunc(resize);
	glEnable(GL_DEPTH_TEST);
	cout<<glGetString(GL_VERSION)<<endl;
cout<<"HELLO"<<endl;
	GLuint v=glCreateShader(GL_VERTEX_SHADER);
	GLuint f=glCreateShader(GL_FRAGMENT_SHADER);
	const char* textV="varying vec3 normal;\nvoid main(){normal=gl_NormalMatrix * gl_Normal;gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;gl_FrontColor=gl_Color;}";
	const char* textF="varying vec3 normal;\nvoid main(){gl_FragColor =clamp(dot(normal,vec3(0.7071,-0.7071,0.0)),0.01,0.99)*gl_Color;}";
	glShaderSource(v,1,&textV,NULL);
	glShaderSource(f,1,&textF,NULL);
	glCompileShader(v);
	glCompileShader(f);
	GLuint p=glCreateProgram();
	glAttachShader(p,v);
	glAttachShader(p,f);
	glLinkProgram(p);
	glUseProgram(p);
cout<<"GOODBYE"<<endl;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5,5,-5,5,5,100);
	glTranslatef(0,0,-20);
	glRotatef(-90,1,0,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutMainLoop();
	return 0;
}
