#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Chart.H>
#include <FL/fl_draw.H>

#include "Line_Chart.h"

#include <iostream>

using namespace std;

Line_Chart::Line_Chart(int x,int y,int w,int h,const char* label) : Fl_Widget(x,y,w,h,label)
{
	box(FL_PLASTIC_DOWN_BOX);
	boundrange=false;
	minrange=0;
	maxrange=0;
	tickunit=1;
}
int Line_Chart::add(double x,double y)
{
	int out=(int)data.size();
	data.push_back(make_pair(x,y));
	return out;
}
void Line_Chart::update(int i,double x,double y)
{
	data[i]=(make_pair(x,y));
}
void Line_Chart::rangebounds(bool yes,double min,double max)
{
	boundrange=yes;
	minrange=min;
	maxrange=max;
}
void Line_Chart::draw_line_chart()
{
	if((int)data.size()<=0){
		return;
	}
	double mix=data[0].first;
	double max=data[0].first;
	double miy=data[0].second;
	double may=data[0].second;

	for(int i=1;i<(int)data.size();i++){
		mix=mix>data[i].first ? data[i].first : mix;
		max=max<data[i].first ? data[i].first : max;
		miy=miy>data[i].second ? data[i].second : miy;
		may=may<data[i].second ? data[i].second : may;
	}
	if(boundrange){
		miy=minrange<miy ? minrange : miy;
		may=maxrange>may ? maxrange : may;
	}
	float border=5;
	cout<<mix<<endl<<max<<endl<<miy<<endl<<may<<endl;
	fl_push_matrix();
		fl_translate(x()+border,y()+border);
		fl_color(88,88,88);
		for(float y=tickunit*((int)miy/tickunit);y<may;y+=tickunit){
			fl_begin_line();
				fl_vertex(0,(y-may)*(-(h()-border*2)/(may-miy)));
				fl_vertex(border,(y-may)*(-(h()-border*2)/(may-miy)));
			fl_end_line();
		}
		fl_scale((w()-border*2)/(max-mix),-(h()-border*2)/(may-miy));
		fl_translate(-mix,-may);
		cout<<fl_transform_x(0,0)<<" , "<<fl_transform_y(0,0)<<endl;
		fl_line_style(FL_SOLID|FL_CAP_ROUND|FL_JOIN_ROUND,2,NULL);
		fl_begin_line();
		if((int)data.size()%2==0&&false){
			for(int i=0;i<(int)data.size()-2;i+=2){
				fl_curve(data[i].first,data[i].second,data[i+1].first,data[i+1].second,data[i+2].first,data[i+2].second,data[i+3].first,data[i+3].second);
			}
		}else{
				for(int i=0;i<(int)data.size();i++){
					fl_vertex(data[i].first,data[i].second);
				}
		}
		fl_end_line();
		fl_line_style(FL_SOLID|FL_CAP_ROUND|FL_JOIN_ROUND,1,NULL);
		fl_color(FL_BLACK);
		if(may>0&&miy<0){
			fl_begin_line();
				fl_vertex(mix,0);
				fl_vertex(max,0);
			fl_end_line();
		}
		if(max>0&&mix<0){
			fl_begin_line();
				fl_vertex(0,miy);
				fl_vertex(0,may);
			fl_end_line();
		}
		
	fl_pop_matrix();
/*
	fl_color(FL_BLACK);
	fl_line(x(),y()+h()*miy/(miy-may),x()+w(),y()+h()*miy/(miy-may));
	fl_color(FL_BLUE);
	for(int i=1;i<(int)data.size();i++){
		fl_line(x()+w()*(data[i-1].first-mix)/(max-mix),y()+h()*(data[i-1].second-miy)/(may-miy),x()+w()*(data[i].first-mix)/(max-mix),y()+h()*(data[i].second-miy)/(may-miy));
		cout<<data[i].first<<" , "<<data[i].second<<endl;
	}*/
}
void Line_Chart::draw()
{
	draw_box();
	Fl_Boxtype b = box();
    int xx = x()+Fl::box_dx(b);
    int yy = y()+Fl::box_dy(b);
    int ww = w()-Fl::box_dw(b);
    int hh = h()-Fl::box_dh(b);
    //fl_push_clip(xx, yy, ww, hh);
	fl_color(FL_WHITE);
	fl_rectf(x(),y(),w(),h());

	fl_color(FL_BLUE);
	switch(type()){
		case FL_LINE_CHART:
			draw_line_chart();
			break;
		default:
			break;
	}
	
	//fl_pop_clip();
}
