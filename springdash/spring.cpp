#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>

#include <FL/gl.h>

#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>

using namespace std;

class Spring_Window : public Fl_Gl_Window
{
	private:
		float mass;
		float damp;
		float spring;
		float grav;
		float initx;
		float initv;
		float time;
		void FixViewport(int w,int h);
		void drawmass(float x,float y,float z,float size);
		void drawspring(float x,float y,float z,int coilnum,float width,float length,float sl);
		string datastring();
		void drawarrow(float x,float y,float z,float value);
	public:
		Spring_Window(int x,int y,int w,int h,const char* label);
		void draw();
		void resize(int x,int y,int w,int h);

		float m(){return mass;}
		void m(float m){mass= m>0 ? m : 1.0;}
		float l(){return damp;}
		void l(float l){damp= l>=0 ? l : 0;}
		float k(){return spring;}
		void k(float k){spring = k>0 ? k : 1.0;}
		float g(){return grav;}
		void g(float g){grav=g;}

		float x0(){return initx;}
		void x0(float x0){initx=x0;}
		float v0(){return initv;}
		void v0(float v0){initv=v0;}
		float t(){return time;}
		void t(float t){time=t;}

		float disp();
		float vel();
		float acc();
		string eqstring();

		static void tick(void* data){
			Spring_Window *win=(Spring_Window*)data;
			win->t(win->t()+.05);
			win->redraw();
			Fl::repeat_timeout(.05,tick,data);
		}
};
Spring_Window::Spring_Window(int x,int y,int w,int h,const char* label=0) : Fl_Gl_Window(x,y,w,h,label)
{
	mass=1;
	damp=0;
	spring=1;
	grav=-9.8;
	initx=0;
	initv=0;
	time=0;
	Fl::add_timeout(.05,tick,(void*) this);
}
void Spring_Window::draw()
{
	if(!valid()){
		valid(1);
		FixViewport(w(),h());
	}
	float maxX=10*(float)w()/h();
	float s=disp();
	float v=vel();
	float a=acc();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
const char *p;
gl_font(1,12);
glRasterPos3f(0,-maxX,-9.9);p=eqstring().data();gl_draw(p,strlen(p));
glRasterPos3f(0,-10,0);p=datastring().data();gl_draw(p,-10,-10,10,10,FL_ALIGN_RIGHT);
glColor3f(0,0,1.0);
drawarrow(0,-5,0,s);
glColor3f(0,1.0,0);
drawarrow(0,-4,0,v);
glColor3f(1.0,0,0);
drawarrow(0,-3,0,a);
	glRotatef(90,0,0,1);
	drawmass(0,0,s,1);
	drawspring(0,0,10,20,.5,9-s,.02);
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
	cout<<h<<" / "<<w<<" = "<<ratio<<endl;
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
	cout<<eqstring()<<endl;
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
string Spring_Window::eqstring()
{
	double a=-(double)damp/(2*mass);
	double c=sqrt(((double)spring/mass)-((double)damp*damp)/(4*mass*mass));
	float c2=-initv-grav/spring;
	float c1=(-initx-initx*damp/mass-damp*grav/(spring*mass))/c;
	float n=grav/spring;
	stringstream out (stringstream::in | stringstream::out);
	if(a!=0){
		out<<"e^(";
		out<<a<<"t)";
	}
	if(c!=0){
		if(c1!=0||c2!=0){
			out<<"( ";
			if(c1!=0){
				out<<c1;out<<"sin("<<c<<"t) "<<( c2!=0 ? " + " : "" );
			}
			if(c2!=0){
				out<<c2<<"cos("<<c<<"t) ";
			}
			out<<")";
		}
	}else{
		if(c2!=0){
			out<<c2;
		}
	}
	if(((a!=0)||(c!=0&&(c1!=0||c2!=0))||(c2!=0))&&(n!=0)){
		out<<" + "<<n;
	}
	string o=out.str();
	if(o.length()==0){
		o+="0";
	}
	return o;
}
string Spring_Window::datastring()
{
	stringstream out (stringstream::in | stringstream::out);
	out<<"x0 : "<<x0()<<"\n";
	out<<"v0 : "<<v0()<<endl<<endl;
	out<<"spring constant  : "<<k()<<endl;
	out<<"damping constant : "<<l()<<endl;
	out<<"mass             : "<<m()<<endl;
	return out.str();
}
float Spring_Window::disp()
{
	float a=-damp/(2*mass);
	float c=sqrt((spring/mass)-(damp*damp)/(4*mass*mass));
	float c2=-initv-grav/spring;
	float c1=(-initx-initx*damp/mass-damp*grav/(spring*mass))/c;
	float n=grav/spring;
	return exp(a*time)*(c1*sin(c*time)+c2*cos(c*time))+n;
}
float Spring_Window::vel()
{
	float a=-damp/(2*mass);
	float c=sqrt((spring/mass)-(damp*damp)/(4*mass*mass));
	float c2=-initv-grav/spring;
	float c1=(-initx-initx*damp/mass-damp*grav/(spring*mass))/c;
//	return a*exp(a*time)*(c1*sin(c*time)+c2*cos(c*time))+c*exp(a*time)*(c1*cos(c*time)-c2*sin(c*time));
	return exp(a*time)*((a*c1-c*c2)*sin(c*time)+(a*c2+c*c1)*cos(c*time));
}
float Spring_Window::acc()
{
	float a=-damp/(2*mass);
	float c=sqrt((spring/mass)-(damp*damp)/(4*mass*mass));
	float c2=-initv-grav/spring;
	float c1=(-initx-initx*damp/mass-damp*grav/(spring*mass))/c;
	return a*exp(a*time)*((a*c1-c*c2)*sin(c*time)+(a*c2+c*c1)*cos(c*time))+ c*exp(a*time)*((a*c1-c*c2)*cos(c*time)-(a*c2+c*c1)*sin(c*time));
}
int main(int argc,char** argv){
	Fl_Window w(100,100,600,600,"FL");
	Spring_Window win(0,0,600,600,"OPENGL TEST");
	win.box(FL_EMBOSSED_BOX);
	w.show();
	return (Fl::run());
}
