#include "Graph.h"
#include <FL/gl.h>
#include <FL/fl_draw.H>
#include <iostream>
#include <sstream>

using namespace std;

Graph::Graph(int x,int y,int w,int h,const char* label) : Fl_Gl_Window(x,y,w,h,label)
{
	xvar=0;
	yvar=1;
	connect=true;
	orderby=0;
	border=10;
	lborder=40;
	bborder=20;
}
void Graph::draw()
{
	if(!valid()){
		valid(1);
		FixViewport(w(),h());
	}
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glColor3f(0,0,0);
		/*glBegin(GL_LINES);
			glVertex3f(1,1,0);glVertex3f(-1,-1,0);
		glEnd();*/
	if((int)ordered.size()>0){
		double mix=0;
		double max=0;
		double miy=0;
		double may=0;
		for(int i=0;i<(int)ordered.size();i++){
			mix=ordered[i][xvar]<mix ? ordered[i][xvar] : mix;
			max=ordered[i][xvar]>max ? ordered[i][xvar] : max;
			miy=ordered[i][yvar]<miy ? ordered[i][yvar] : miy;
			may=ordered[i][yvar]>may ? ordered[i][yvar] : may;
		}
		glPushMatrix();
		glScalef(2.0/h(),2.0/h(),1);
		glTranslatef(-w()/2.0,-h()/2.0,0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(lborder,bborder,0);
			glVertex3f(w()-border,bborder,0);
			glVertex3f(w()-border,h()-border,0);
			glVertex3f(lborder,h()-border,0);
		glEnd();
		if((int)labels.size()>xvar){
			gl_font(fl_font(),(int)border/2);
			gl_draw(labels[xvar].data(),0,0,w(),(int)border,FL_ALIGN_CENTER);
			if((int)labels.size()>yvar){
				string top=(labels[yvar]+" VS. "+labels[xvar]);
				gl_font(fl_font(),(int)border);
				gl_draw(top.data(),0,h()-(int)border,w(),border,FL_ALIGN_CENTER);
			}
		}


		gl_font(fl_font(),(int)border/4);
		stringstream s (stringstream::in|stringstream::out);
		s.precision(2);
		s<<mix;
		s<<"s";
		const char * c="";
		string str="";
		str=s.str();
		gl_draw(str.data(),(int)lborder,0);
		s.str("");
		s<<miy;
		str=s.str();
		gl_draw(str.data(),0,(int)bborder);
		s.str("");
		s<<may;
		str=s.str();
		gl_draw(str.data(),0,h()-(int)border);


		glTranslatef(lborder,bborder,0);
		glScalef((w()-border-lborder)/(max-mix),(h()-border-bborder)/(may-miy),1);
		glTranslatef(-mix,-miy,0);
		gl_color(color());
		glBegin(GL_LINE_STRIP);
		for(int i=0;i<(int)ordered.size();i++){
			glVertex3d(ordered[i][xvar],ordered[i][yvar],0);
		}
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	GLenum err = glGetError();
	if ( err != GL_NO_ERROR ) {
		cout<<"GLGETERROR="<< (int)err<<endl;
	}
}
void Graph::FixViewport(int w,int h)
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
	glFrustum(-ratio*.1,ratio*.1,-.1,.1,.1,10);
	glTranslatef(0,0,-1);
	//glRotatef(-90,0,1,0);
	//glRotatef(-90,1,0,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Graph::resize(int x,int y,int w,int h)
{
	Fl_Gl_Window::resize(x,y,w,h);
	FixViewport(w,h);
	redraw();
}
void Graph::sort(int start,int end)
{
	if(end-start<1){
		return;
	}
	int pivot=start;
	while(orderby>=(int)ordered[pivot].size()&&pivot<=end){
		pivot++;
	}
	double pvalue=0;
	if(orderby<(int)ordered[pivot].size()){
		pvalue=ordered[pivot][orderby];
	}
	int e=end;
	while(pivot<e){
		if(orderby>=(int)ordered[pivot+1].size()||pvalue>=ordered[pivot+1][orderby]){
			vector<double> tmp=ordered[pivot];
			ordered[pivot]=ordered[pivot+1];
			ordered[pivot+1]=tmp;
			pivot++;
		}else{
			vector<double> tmp=ordered[e];
			ordered[e]=ordered[pivot+1];
			ordered[pivot+1]=tmp;
			e--;
		}
	}
	sort(start,pivot-1);
	sort(pivot+1,end);
}
