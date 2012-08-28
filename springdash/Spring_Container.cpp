#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Multiline_Output.H>

#include<iostream>
#include<sstream>
#include<cstring>

#include "Spring_Container.h"
#include "Line_Chart.h"

Spring_Container::Spring_Container(int x,int y,int w,int h,const char* label=0) : Fl_Window(x,y,w,h,label)
{
	gl_box=new Spring_Window(190,10,w-200,h-180,"GL");
	resizable(gl_box);
	k_slider=new Fl_Slider(10,10,20,h-170,"k");
	k_slider->step(1);
	k_slider->range(1,100);
	k_slider->value(10);
	k_slider->tooltip("spring constant");
	l_slider=new Fl_Slider(40,10,20,h-170,"l");
	l_slider->step(.1);
	l_slider->range(0,1);
	l_slider->value(.1);
	l_slider->tooltip("damping constant");
	m_slider=new Fl_Slider(70,10,20,h-170,"m");
	m_slider->step(.1);
	m_slider->range(.1,10);
	m_slider->value(1);
	m_slider->tooltip("mass");
	g_slider=new Fl_Slider(100,10,20,h-170,"g");
	g_slider->step(.1);
	g_slider->range(10,-10);
	g_slider->value(-9.8);
	g_slider->tooltip("acceleration due to gravity");

	x_slider=new Fl_Slider(130,10,20,h-170,"x0");
	x_slider->step(.5);
	x_slider->range(-10,10);
	x_slider->value(0);
	x_slider->tooltip("initial position");
	v_slider=new Fl_Slider(160,10,20,h-170,"v0");
	v_slider->step(.5);
	v_slider->range(-10,10);
	v_slider->value(0);
	v_slider->tooltip("initial velocity");

	k_slider->type(FL_VERT_NICE_SLIDER);
	l_slider->type(FL_VERT_NICE_SLIDER);
	m_slider->type(FL_VERT_NICE_SLIDER);
	g_slider->type(FL_VERT_NICE_SLIDER);
	x_slider->type(FL_VERT_NICE_SLIDER);
	v_slider->type(FL_VERT_NICE_SLIDER);

	k_slider->box(FL_FLAT_BOX);
	l_slider->box(FL_FLAT_BOX);
	m_slider->box(FL_FLAT_BOX);
	g_slider->box(FL_FLAT_BOX);
	x_slider->box(FL_FLAT_BOX);
	v_slider->box(FL_FLAT_BOX);

	k_slider->callback(Spring_Container::call,(void*)this);
	l_slider->callback(Spring_Container::call,(void*)this);
	m_slider->callback(Spring_Container::call,(void*)this);
	g_slider->callback(Spring_Container::call,(void*)this);
	x_slider->callback(Spring_Container::call,(void*)this);
	v_slider->callback(Spring_Container::call,(void*)this);

	g=0;
	c1=new Line_Chart(10,h-110,w-20,100,"CHART");
	gmenu=new Fl_Choice(10,h-140,170,20,"");
	gmenu->add("Displacement",0,Spring_Container::graphchanged,this,0);
	gmenu->add("Velocity",0,Spring_Container::graphchanged,this,0);
	gmenu->add("Acceleration",0,Spring_Container::graphchanged,this,0);
	gmenu->add("Net Force",0,Spring_Container::graphchanged,this,0);
	gmenu->add("Potential Energy",0,Spring_Container::graphchanged,this,0);
	gmenu->add("Kinetic Energy",0,Spring_Container::graphchanged,this,0);
	gmenu->add("Total Energy",0,Spring_Container::graphchanged,this,0);
	gmenu->value(0);
	c1->type(FL_LINE_CHART);
	//c1->autosize(1);
	c1->rangebounds(true,-1,1);
	c1->color(FL_BLUE);
	valuechanged();
	initgraphs();

	o_text=new Fl_Multiline_Output(190,h-160,w-200,40);

	changed=true;

	t=0;

	Fl::add_timeout(.1,timeoutcall,(void*)this);
}
void Spring_Container::call(Fl_Widget* w,void* v)
{
	((Spring_Container*)v)->valuechanged();
}
void Spring_Container::valuechanged()
{
	calc.k(k_slider->value());
	calc.l(l_slider->value());
	calc.m(m_slider->value());
	calc.g(g_slider->value());

	calc.x0(x_slider->value());
	calc.v0(v_slider->value());

	changed=true;

	cout<<calc.eqstring()<<endl;
}
void Spring_Container::timeoutcall(void* data)
{
	((Spring_Container*)data)->timeout();
	Fl::repeat_timeout(.1,Spring_Container::timeoutcall,data);
}
void Spring_Container::timeout()
{
	if(changed){
		updategraphs();
		changed=false;
	}
	updatetext();
	gl_box->disp=(float)calc.disp(t);
	gl_box->redraw();
	t+=.1;
	if(t>=10){
		t-=10;
	}
}
void Spring_Container::initgraphs()
{
	for(int i=0;i<500;i++){
		cout<<c1->add((double)i/50,calc.disp((float)i/50))<<endl;
	}
}
void Spring_Container::updategraphs()
{
	switch(gmenu->value()){
		case 0:
			c1->color(FL_BLUE);
			for(int i=0;i<500;i++){
				c1->update(i,(double)i/50,calc.disp((float)i/50));
			}
			break;
		case 1:
			c1->color(FL_GREEN);
			for(int i=0;i<500;i++){
				c1->update(i,(double)i/50,calc.vel((float)i/50));
			}
			break;
		case 2:
			c1->color(FL_RED);
			for(int i=0;i<500;i++){
				c1->update(i,(double)i/50,calc.acc((float)i/50));
			}
			break;
		case 3:
			c1->color(FL_YELLOW);
			for(int i=0;i<500;i++){
				c1->update(i,(double)i/50,calc.acc((float)i/50)/calc.m());
			}
			break;
		case 4:
			c1->color(FL_CYAN);
			for(int i=0;i<500;i++){
				c1->update(i,(double)i/50,calc.disp((float)i/50)*calc.g()*calc.m()/2+calc.disp((float)i/50)*calc.disp((float)i/50)*calc.k()/2);
			}
			break;
		case 5:
			c1->color(FL_MAGENTA);
			for(int i=0;i<500;i++){
				c1->update(i,(double)i/50,calc.vel((float)i/50)*calc.vel((float)i/50)*calc.m()/2);
			}
			break;
		case 6:
			c1->color(FL_BLUE);
			for(int i=0;i<500;i++){
				c1->update(i,(double)i/50,calc.disp((float)i/50)*calc.g()*calc.m()+calc.disp((float)i/50)*calc.disp((float)i/50)*calc.k()/2+calc.vel((float)i/50)*calc.vel((float)i/50)*calc.m()/2);
			}
			break;
	}
			
	c1->redraw();
}
void Spring_Container::updatetext()
{
	stringstream txt(stringstream::in | stringstream::out);
	txt<<"x("<<round(t)<<")="<<round(calc.disp(t))<<endl;
	txt<<"{x(t) = "<<calc.eqstring()<<"}";
	txt<<"\tg="<<round(calc.g());
	txt<<"\tk="<<round(calc.k());
	txt<<"\tl="<<round(calc.l());
	txt<<"\tm="<<round(calc.m());
	txt<<"\tx0="<<round(calc.x0());
	txt<<"\tv0="<<round(calc.v0());
	o_text->value(txt.str().data());
}
void Spring_Container::graphchanged(Fl_Widget* w,void* v)
{
	((Spring_Container*)v)->updategraphs();
}
