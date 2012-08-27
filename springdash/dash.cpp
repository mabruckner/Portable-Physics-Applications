#include<FL/Fl.H>
#include<FL/Fl_Slider.H>

#include "Spring_Container.h"

#include <iostream>

using namespace std;

void call(Fl_Widget* w,void* v)
{
	cout<<"CALLBACK"<<endl;
}

int main(int argc,char** argv)
{
	Fl::scheme("gtk+");
	Spring_Container* win=new Spring_Container(100,100,300,300,"OPENGL!!!");
	/*Fl_Slider* slide=new Fl_Slider(10,10,20,280,"X0");
	slide->type(FL_VERT_NICE_SLIDER);
	slide->callback(call);*/
	win->show();
	return (Fl::run());
}

