#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_File_Chooser.H>

#include<iostream>
#include<sstream>
#include<cstring>
#include<fstream>

#include "Spring_Container.h"
#include "Line_Chart.h"

Spring_Container::Spring_Container(int x,int y,int w,int h,const char* label=0) : Fl_Window(x,y,w,h,label)
{
	menu=new Fl_Menu_Bar(0,0,w,20,"MENUBAR!");
	menu->add("File/Export",0,Spring_Container::startexport,this,0);
	//menu->add("File/Quit",0,0,0,0);
	gl_box=new Spring_Window(190,30,w-200,h-200,"GL");
	resizable(gl_box);
	k_slider=new Fl_Slider(10,30,20,h-190,"k");
	k_slider->step(1);
	k_slider->range(100,1);
	k_slider->value(10);
	k_slider->tooltip("spring constant (Nm)");
	l_slider=new Fl_Slider(40,30,20,h-190,"l");
	l_slider->step(.01);
	l_slider->range(1,0);
	l_slider->value(.1);
	l_slider->tooltip("damping constant");
	m_slider=new Fl_Slider(70,30,20,h-190,"m");
	m_slider->step(.05);
	m_slider->range(10,.1);
	m_slider->value(1);
	m_slider->tooltip("mass (kg)");
	g_slider=new Fl_Slider(100,30,20,h-190,"g");
	g_slider->step(.1);
	g_slider->range(10,-10);
	g_slider->value(-9.8);
	g_slider->tooltip("acceleration due to gravity (m/s*s)");

	x_slider=new Fl_Slider(130,30,20,h-190,"x0");
	x_slider->step(.1);
	x_slider->range(-10,10);
	x_slider->value(0);
	x_slider->tooltip("initial position (m)");
	v_slider=new Fl_Slider(160,30,20,h-190,"v0");
	v_slider->step(.5);
	v_slider->range(-10,10);
	v_slider->value(0);
	v_slider->tooltip("initial velocity (m/s)");

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
	//c1=new Line_Chart(10,h-110,170,100,"CHART");
	graph=new Graph(190,h-110,w-200,100,"GRAPH");
	graph->color(FL_BLUE);
	gmenu=new Fl_Choice(10,h-140,170,20,"");
	gmenu->add("Displacement",0,Spring_Container::graphchanged,this,0);
	gmenu->add("Velocity",0,Spring_Container::graphchanged,this,0);
	gmenu->add("Acceleration",0,Spring_Container::graphchanged,this,0);
	gmenu->add("Net Force",0,Spring_Container::graphchanged,this,0);
	gmenu->add("Potential Energy",0,Spring_Container::graphchanged,this,0);
	gmenu->add("Kinetic Energy",0,Spring_Container::graphchanged,this,0);
	gmenu->add("Total Energy",0,Spring_Container::graphchanged,this,0);
	gmenu->value(0);
	//c1->type(FL_LINE_CHART);
	///c1->autosize(1);
	//c1->rangebounds(true,-1,1);
	//c1->color(FL_BLUE);
	valuechanged();
	initgraphs();

	o_text=new Fl_Multiline_Output(190,h-160,w-200,40);

	changed=true;

	t=0;

	export_win=new Fl_Window(300,250,"Export CSV");
	export_button=new Fl_Button(100,220,100,20,"EXPORT");
	export_time=new Fl_Check_Button(10,10,100,20,"time");
	export_disp=new Fl_Check_Button(10,30,100,20,"displacement");
	export_vel=new Fl_Check_Button(10,50,100,20,"velocity");
	export_acc=new Fl_Check_Button(10,70,100,20,"acceleration");
	export_KE=new Fl_Check_Button(10,90,100,20,"kinetic energy");
	export_EPE=new Fl_Check_Button(10,110,100,20,"elastic potential energy");
	export_GPE=new Fl_Check_Button(10,130,100,20,"gravitational potential energy");
	export_E=new Fl_Check_Button(10,150,100,20,"total energy");
	export_file=new Fl_File_Input(10,170,280,30,"");

	export_min=new Fl_Counter(200,10,90,20,"min");
	export_min->value(0);
	export_min->step(1);
	export_min->lstep(10);
	export_step=new Fl_Counter(200,50,90,20,"step");
	export_step->value(.1);
	export_step->step(.01);
	export_step->lstep(.1);
	export_max=new Fl_Counter(202,90,90,20,"max");
	export_max->value(10);
	export_max->step(1);
	export_max->lstep(10);

	export_button->callback(Spring_Container::exportfile,(void*)this);
export_win->show();
	export_win->hide();
	/*	Fl_Check_Button* export_disp;
		Fl_Check_Button* export_vel;
		Fl_Check_Button* export_acc;
		Fl_Check_Button* export_KE;
		Fl_Check_Button* export_EPE;
		Fl_Check_Button* export_GPE;*/

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

	//cout<<calc.eqstring()<<endl;
}
void Spring_Container::timeoutcall(void* data)
{
	((Spring_Container*)data)->timeout();
	Fl::repeat_timeout(.1,Spring_Container::timeoutcall,data);
}
void Spring_Container::timeout()
{
	if(changed){
		initgraphs();
		changed=false;
	}
	updatetext();
	gl_box->disp=(float)calc.disp(t);
	gl_box->redraw();
	t+=.1;
	if(t>=10){
		t-=10;
	}
	//t=c1->settime(true,t);
}
void Spring_Container::initgraphs()
{
	bool add=(int)graph->ptdata().size()==0;
	for(int i=0;i<500;i++){
		//c1->add((double)i/50,calc.disp((float)i/50));
		vector<double> pt=vector<double>();
		double t=(double)i/50;
		pt.push_back(t);
		pt.push_back(calc.disp(t));
		pt.push_back(calc.vel(t));
		pt.push_back(calc.acc(t));
		pt.push_back(calc.acc(t)/calc.m());
		pt.push_back(-calc.disp(t)*calc.g()*calc.m()+calc.disp(t)*calc.disp(t)*calc.k()/2);
		pt.push_back(calc.vel(t)*calc.vel(t)*calc.m()/2);
		pt.push_back(calc.vel(t)*calc.vel(t)*calc.m()/2-calc.disp(t)*calc.g()*calc.m()+calc.disp(t)*calc.disp(t)*calc.k()/2);
		if(add){
			graph->add(pt);
		}else{
			graph->set(i,pt);
		}
	}
	if(add){
		vector<string> v=vector<string>();
		v.push_back("time");
		v.push_back("position");
		v.push_back("velocity");
		v.push_back("acceleration");
		v.push_back("net force");
		v.push_back("potential energy");
		v.push_back("kinetic energy");
		v.push_back("total energy");
		graph->labellist(v);
	}
	graph->update();
}
void Spring_Container::updategraphs()
{
	graph->yaxis(gmenu->value()+1);
	switch(gmenu->value()){
		case 0:
			graph->color(FL_BLUE);
			break;
		case 1:
			graph->color(FL_GREEN);
			break;
		case 2:
			graph->color(FL_RED);
			break;
		case 3:
			graph->color(FL_YELLOW);
			break;
		case 4:
			graph->color(FL_CYAN);
			break;
		case 5:
			graph->color(FL_MAGENTA);
			break;
		case 6:
			graph->color(FL_BLUE);
			break;
	}
	graph->update();
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
void Spring_Container::exportfile(Fl_Widget* w,void* v){
	Spring_Container* box=(Spring_Container*)v;
	/*Fl_File_Chooser dialog("","*.csv",Fl_File_Chooser::CREATE,"choose or create a file");
	if(dialog.show()==0){
		return;
	}*/
	char * filepath=fl_dir_chooser("select a directory",0,0);
	if(filepath==NULL){
		box->export_win->hide();
		return;
	}
	stringstream s(stringstream::in | stringstream::out);
	s<<filepath<<"/"<<box->export_file->value();
	const char * fullpath=s.str().data();
	ofstream f(fullpath);
	//s.ignore();
	double start=0;
	start=box->export_min->value();
	cout<<box->export_min->value()<<endl<<start<<endl;
	double end=10;
	end=box->export_max->value();
	end=end>=start ? end : start;
	double step=.1;
	s.ignore();
	step=box->export_step->value();
	step=step>0? step : .01;
	Spring_Calc* calc=&(box->calc);
	for(int i=0;step*i+start<=end;i++){
		double t=step*i+start;cout<<t<<endl;
		bool comma=false;
		if(box->export_time->value()){
			comma=true;
			float value=floor(t*1000)/1000;
			f<<value;
		}
		if(box->export_disp->value()){
			if(comma)f<<",";
			comma=true;
			float value=floor(calc->disp(t)*1000)/1000;
			f<<value;
		}
		if(box->export_vel->value()){
			if(comma)f<<",";
			comma=true;
			float value=floor(calc->vel(t)*1000)/1000;
			f<<value;
		}
		if(box->export_acc->value()){
			if(comma)f<<",";
			comma=true;
			float value=floor(calc->acc(t)*1000)/1000;
			f<<value;
		}
		if(box->export_KE->value()){
			if(comma)f<<",";
			comma=true;
			float value=floor(calc->vel(t)*calc->vel(t)*calc->m()*500)/1000;
			f<<value;
		}
		if(box->export_EPE->value()){
			if(comma)f<<",";
			comma=true;
			float value=floor(calc->disp(t)*calc->disp(t)*calc->k()*500)/1000;
			f<<value;
		}
		if(box->export_GPE->value()){
			if(comma)f<<",";
			comma=true;
			float value=floor(-calc->disp(t)*calc->g()*calc->m()*1000)/1000;
			f<<value;
		}
		if(box->export_E->value()){
			if(comma)f<<",";
			comma=true;
			float value=floor(calc->vel(t)*calc->vel(t)*calc->m()*500+calc->disp(t)*calc->disp(t)*calc->k()*500-calc->disp(t)*calc->g()*calc->m()*1000)/1000;
			f<<value;
		}
		f<<endl;
	}
	f.close();
	//delete filepath;
	box->export_win->hide();
//	char *filename=fl_file_chooser("choose file path","*.csv","",0);
}
