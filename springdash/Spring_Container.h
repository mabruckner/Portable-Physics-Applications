#ifndef SPRING_CONTAINER_H
#define SPRING_CONTAINER_H

#include<FL/Fl.H>
#include<FL/Fl_Window.H>
#include<FL/Fl_Slider.H>
#include<FL/Fl_Chart.H>
#include<FL/Fl_Multiline_Output.H>
#include<FL/Fl_Choice.H>

#include<cmath>

#include"Spring_Window.h"
#include"Spring_Calc.h"
#include "Line_Chart.h"

class Spring_Container : public Fl_Window
{
	public:
		Spring_Container(int x,int y,int w,int h,const char* label);
		static void call(Fl_Widget* w,void* v);
		void valuechanged();
		static void timeoutcall(void* data);
		void timeout();
		static void graphchanged(Fl_Widget* w,void* v);
		void updategraphs();
		int g;
	private:
		void initgraphs();
		void updatetext();
		Spring_Window* gl_box;
		Fl_Slider* k_slider;
		Fl_Slider* l_slider;
		Fl_Slider* m_slider;

		Fl_Slider* g_slider;

		Fl_Slider* x_slider;
		Fl_Slider* v_slider;

		Fl_Choice* gmenu;

		Line_Chart* c1;

		Spring_Calc calc;

		Fl_Multiline_Output* o_text;

		float t;

		bool changed;

		float round(float num){
			return std::floor(num*1000+.5)/1000;
		}
};
#endif
