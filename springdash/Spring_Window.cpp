

#include<FL/Fl.H>
#include<FL/Fl_Gl_Window.H>
#include<FL/gl.h>

#include"Spring_Window.h"

#include<iostream>
#include<cmath>

using namespace std;

Spring_Window::Spring_Window(int x,int y,int w,int h,const char* label=0) : Fl_Gl_Window(x,y,w,h,label)
{
	disp=0;
}
void Spring_Window::draw()
{
	if(!valid()){
		valid(1);
		FixViewport(w(),h());
	}
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glRotatef(90,0,0,1);
		drawmass(0,0,disp,1);
		drawspring(0,0,10,20,.5,9-disp,.02);
	glPopMatrix();
	GLenum err = glGetError();
	if ( err != GL_NO_ERROR ) {
		cout<<"GLGETERROR="<< (int)err<<endl;
	}
}
void Spring_Window::FixViewport(int w,int h)
{
	float ratio=(float)w/h;
	if(h==0||w==0){
		ratio=1;
	}
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glClearColor(1,1,1,1);
	glLoadIdentity();
	glViewport(0,0,w,h);
	glFrustum(-ratio,ratio,-1,1,1.5,100);
	glTranslatef(0,0,-15);
	glRotatef(-90,0,1,0);
	glRotatef(-90,1,0,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Spring_Window::resize(int x,int y,int w,int h)
{
	Fl_Gl_Window::resize(x,y,w,h);
	FixViewport(w,h);
	redraw();
}
void Spring_Window::drawmass(float x,float y,float z,float size)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glColor3f(0,0,0);
		glPushMatrix();
		glTranslatef(x,y,z);
		glScalef(size,size,size);
		glBegin(GL_LINES);
			glVertex3f(1,1,1);glVertex3f(-1,1,1);
			glVertex3f(1,1,-1);glVertex3f(-1,1,-1);
			glVertex3f(1,-1,1);glVertex3f(-1,-1,1);
			glVertex3f(1,-1,-1);glVertex3f(-1,-1,-1);

			glVertex3f(1,1,1);glVertex3f(1,-1,1);
			glVertex3f(1,1,-1);glVertex3f(1,-1,-1);
			glVertex3f(-1,1,1);glVertex3f(-1,-1,1);
			glVertex3f(-1,1,-1);glVertex3f(-1,-1,-1);

			glVertex3f(1,1,1);glVertex3f(1,1,-1);
			glVertex3f(1,-1,1);glVertex3f(1,-1,-1);
			glVertex3f(-1,1,1);glVertex3f(-1,1,-1);
			glVertex3f(-1,-1,1);glVertex3f(-1,-1,-1);
		glEnd();
		glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}
void Spring_Window::drawarrow(float x,float y,float z,float value)
{
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glTranslatef(x,y,z);
	float al=.875;
	glBegin(GL_TRIANGLES);
		glVertex3f(0,0,value);glVertex3f(.1,.1,al*value);glVertex3f(.1,-.1,al*value);
		glVertex3f(0,0,value);glVertex3f(.1,-.1,al*value);glVertex3f(-.1,-.1,al*value);
		glVertex3f(0,0,value);glVertex3f(-.1,-.1,al*value);glVertex3f(-.1,.1,al*value);
		glVertex3f(0,0,value);glVertex3f(-.1,.1,al*value);glVertex3f(.1,.1,al*value);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(0,0,0);glVertex3f(0,0,value);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glPopMatrix();
}
//draws a spring extending in the -z direction from (x,y,z)
void Spring_Window::drawspring(float x,float y,float z,int coilnum,float width,float length,float sl)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glColor3f(0,0,0);
		glPushMatrix();
		glTranslatef(x,y,z);
		glBegin(GL_LINE_STRIP);
			int res=10;
			for(int i=0;i<=coilnum*res;i++){
				float w=width;
				if((float)i/(coilnum*res)<sl){
					w=width*((float)i/(coilnum*res))/sl;
				}
				if((float)i/(coilnum*res)>1-sl){
					w=width*((float)((coilnum*res)-i)/(coilnum*res))/sl;
				}
				glVertex3f(w*cos(M_PI*2*i/((float)res)),w*sin(M_PI*2*i/((float)res)),-length*i/((float)(coilnum*res)));
			}
		glEnd();
		glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

