#ifndef SPRING_WINDOW_H
#define SPRING_WINDOW_H

#include<FL/Fl.H>
#include<FL/Fl_Gl_Window.H>

class Spring_Window : public Fl_Gl_Window
{
		void FixViewport(int w,int h);
		void drawmass(float x,float y,float z,float size);
		void drawspring(float x,float y,float z,int coilnum,float width,float length,float sl);
		void drawarrow(float x,float y,float z,float value);
	public:
		Spring_Window(int x,int y,int w,int h,const char* label);
		void draw();
		void resize(int x,int y,int w,int h);
		float disp;
};
#endif
