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
		pfloat d=dist(x,y,z,p->xpos->data,p->ypos->data,p->zpos->data);
		if(abs(d)<=.1){
			continue;
		}
		pfloat mag=G*p->weight/(d*d);
		ox+=mag*(p->xpos->data-x)/d;
		oy+=mag*(p->ypos->data-y)/d;
		oz+=mag*(p->zpos->data-z)/d;
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
	glRotatef(-45,1,0,0);
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
	glColor3f(1.0,1.0,1.0);
	for(int i=0;i<(int)list.size();i++){
		Point* p=&list[i];
		float r=.1*sqrt(p->weight);
		glPushMatrix();
		glTranslatef(p->xpos->data,p->ypos->data,p->zpos->data);
		glutSolidSphere(r,32,16);
		glPopMatrix();
		glBegin(GL_LINE_STRIP);
			rdata* xd=p->xpos;
			rdata* yd=p->ypos;
			rdata* zd=p->zpos;
			while((xd=xd->back)!=p->xpos&&(yd=yd->back)!=p->ypos&&(zd=zd->back)!=p->zpos)glVertex3f(xd->data,yd->data,zd->data);
		glEnd();
	}
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_STRIP);
		for(int i=0;i<timeindex;i++){
			glVertex3f(0,0,0);
		}
	glEnd();
	glBegin(GL_QUADS);
		float s=.25;
		float max=20;
		for(float i=-20;i<20;i+=s){
			for(float j=-20;j<20;j+=s){
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
/*	pfloat xf[(int)list.size()];
	pfloat yf[(int)list.size()];
	pfloat zf[(int)list.size()];
	for(int i=0;i<(int)list.size();i++){
		accvect(xf+i,yf+i,zf+i,list[i].xpos->data,list[i].ypos->data,list[i].zpos->data);
	}//cout<<xf[0]<<","<<yf[0]<<","<<zf[0]<<" - "<<list[1].xpos[timeindex]<<endl;
	for(int i=0;i<(int)list.size();i++){
		euler(&(list[i]),xf[i],yf[i],zf[i],.1);
	}
	timeindex++;*/
	for(int i=0;i<4;i++)
vertlet_integration(&list,accvect,.05);
	redraw();
}

void processNormalKeys(unsigned char key,int x,int y)
{
	if(key==27)exit(0);
}
void menufunc(int num){
	cout<<"MENU : "<<num<<endl;
}
int main(int argc, char** argv)
{
	timeindex=0;

	cout<<"RDATA"<<sizeof(rdata)<<endl;

	list=vector<Point>();
	G=10;

	Point a;
	a.weight=5;
	/*
	a.xpos->data=.04;
	a.ypos->data=-.04;
	*/
	a.xvel->data=.4;
	a.yvel->data=-.4;
	list.push_back(a);
	Point b;
/*
	b.xpos->data=-5.2;
	b.ypos->data=-4.8;
	b.xpos->back->data=-5;
	b.ypos->back->data=-5;
*/
	b.xpos->data=-5;
	b.ypos->data=-5;
	b.xvel->data=-2;
	b.yvel->data=2;
	b.weight=1;
	list.push_back(b);
	//euler(&list,accvect,.1);
	Point c;
	c.weight=.2;
	c.xpos->data=-6;
	c.ypos->data=-6;
	//c.xpos->back->data=29.99;
	list.push_back(c);

	/*Point d;
	d.xpos->data=10;
	d.weight=.5;
	d.yvel->data=-2.5;
	list.push_back(d);*/
	//euler(&b,10,10,10,1);cout<<"HELLO WORLD?"<<endl;
	//cout<<accmag(1,1,0)<<endl;cout<<(int)list.size()<<endl;
	euler(&list,accvect,.05);


	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("HELLO WORLD");
	//glutFullScreen();
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
	glutKeyboardFunc(processNormalKeys);


	glutCreateMenu(menufunc);
	glutAddMenuEntry("pause",0);
	glutAttachMenu(GLUT_LEFT_BUTTON);


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
