#include "Viewer.h"
#include "UIFunc.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Render.h"
#include <math.h>

static float mouseX=0;
static float mouseY=0;
static float pitch=-45;
static float yaw=-135;


static float current_time=0;
void resizeFunc(int w,int h)
{
	if(w==0){
		w=1;
	}
	float  ratio=(float)h/w;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-ratio,ratio,1,1000);
	
	glTranslatef(0,0,-100);
//	glRotatef(90,0,0,1);
	//glRotatef(-45,1,0,0);
	//glRotatef(-135,0,0,1);
	
}
void motionFuncPassive(int x,int y)
{
	mouseX=x;
	mouseY=y;
}
void motionFunc(int x,int y)
{
yaw+=x-mouseX;
pitch+=y-mouseY;
	mouseX=x;	
mouseY=y;
//	displayFunc();
}
void mouseFunc(int button,int state,int x,int y)
{
	if(state==GLUT_DOWN){
		mouseX=x;
		mouseY=y;
	}else{
		//pitch+=y-mouseY;
		//yaw+=x-mouseX;
	}
}
void displayFunc()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glRotatef(pitch,1,0,0);
	glRotatef(yaw,0,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float r=2/sqrt(grid.width*grid.width+grid.height*grid.height);
	glClearColor(1.0,1.0,.5,1.0);
	glNormal3f(0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0,0,0);
	glBegin(GL_LINES);
		glVertex3f(-50,0,0);
		glVertex3f(50,0,0);
		glVertex3f(0,-50,0);
		glVertex3f(0,50,0);
	glEnd();
glColor3f(0.0,1.0,0.0);
	//glutSolidSphere(10,32,16);
	glNormal3f(0,0,1);
	glScalef(r*50,r*50,r*50);
	glTranslatef(-(float)grid.width/2,-(float)grid.height/2,0);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(1,1,.5);
	glBegin(GL_QUADS);
		glVertex3f(0,0,-.1);
		glVertex3f(0,grid.height,-.1);
		glVertex3f(grid.width,grid.height,-.1);
		glVertex3f(grid.width,0,-.1);glEnd();
		int i,j;
		float size=.1;
glColor3f(1,1,1);
		for(i=0;i<grid.width+1;i++){
			for(j=0;j<grid.height+1;j++){renderVertex(i+j*(grid.width+1),size,.1);
				/*float height=grid.map.vertices[i+j*(grid.width+1)].voltage*5;
				glNormal3f(0,0,1);
				glVertex3f(i-size,j-size,height);
				glVertex3f(i-size,j+size,height);
				glVertex3f(i+size,j+size,height);
				glVertex3f(i+size,j-size,height);
				glNormal3f(1,0,0);
				glVertex3f(i+size,j-size,height);
				glVertex3f(i+size,j+size,height);
				glVertex3f(i+size,j+size,0);
				glVertex3f(i+size,j-size,0);
				glNormal3f(-1,0,0);
				glVertex3f(i-size,j-size,height);
				glVertex3f(i-size,j+size,height);
				glVertex3f(i-size,j+size,0);
				glVertex3f(i-size,j-size,0);
				glNormal3f(0,1,0);
				glVertex3f(i-size,j+size,height);
				glVertex3f(i+size,j+size,height);
				glVertex3f(i+size,j+size,0);
				glVertex3f(i-size,j+size,0);
				glNormal3f(0,-1,0);
				glVertex3f(i-size,j-size,height);
				glVertex3f(i+size,j-size,height);
				glVertex3f(i+size,j-size,0);
				glVertex3f(i-size,j-size,0);*/
			}
		}
		for(i=0;i<grid.map.ccount;i++){renderComponent(i,size,.1,current_time);/*
			Component* c=grid.map.components+i;
			int x1=c->A%(grid.width+1);
			int y1=c->A/(grid.width+1);
			float h1=grid.map.vertices[c->A].voltage*5;
			int x2=c->B%(grid.width+1);
			int y2=c->B/(grid.width+1);
			float h2=grid.map.vertices[c->B].voltage*5;
			glVertex3f(x1,y1,h1);
			glVertex3f(x1,y1,0);
			glVertex3f(x2,y2,0);
			glVertex3f(x2,y2,h2);*/
		}
	//glEnd();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glutSwapBuffers();
}
void timerFunc(int value)
{
	displayFunc();
	current_time+=.01;
	glutTimerFunc(30,timerFunc,value+1);
}
void init_Viewer(gpointer* data)
{
//	gdk_threads_leave();
	printf("THREAD!\n");
//	int argc=1;
//	char** argv={"program"};
//	glutInit(&argc,argv);
	printf("INIT!\n");
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600,600);
glutCreateWindow("VIEWER");
	glEnable(GL_DEPTH_TEST);
	GLenum err=glewInit();
	if(err!=GLEW_OK){
		return;
	}
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(resizeFunc);
	glutMotionFunc(motionFunc);
	glutMouseFunc(mouseFunc);
	glutTimerFunc(100,timerFunc,0);
	GLuint v=glCreateShader(GL_VERTEX_SHADER);
	GLuint f=glCreateShader(GL_FRAGMENT_SHADER);
	const char* textV="varying vec3 normal;\nvoid main(){normal= gl_Normal;gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;gl_FrontColor=gl_Color;}";
	const char* textF="varying vec3 normal;\nvoid main(){gl_FragColor =clamp(dot(normal,vec3(0.5,0.1,0.9)),0.0,1.0)*gl_Color;}";
	glShaderSource(v,1,&textV,NULL);
	glShaderSource(f,1,&textF,NULL);
	glCompileShader(v);
	glCompileShader(f);
	GLuint p=glCreateProgram();
	glAttachShader(p,v);
	glAttachShader(p,f);
	glLinkProgram(p);
	glUseProgram(p);
/*	glutMainLoop();*/
int i;
	for(i=0;i<10000;i++){
		printf("%i\n",(int)sqrt(i));
	}
glutMainLoop();
}
