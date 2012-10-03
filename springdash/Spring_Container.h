#ifndef SPRING_CONTAINER_H
#define SPRING_CONTAINER_H

#include<FL/Fl.H>
#include<FL/Fl_Window.H>
#include<FL/Fl_Slider.H>
#include<FL/Fl_Chart.H>
#include<FL/Fl_Multiline_Output.H>
#include<FL/Fl_Choice.H>
#include<FL/Fl_Menu_Bar.H>
#include<FL/Fl_Button.H>
#include<FL/Fl_Check_Button.H>
#include<FL/Fl_File_Input.H>
#include<FL/Fl_Counter.H>

#include<cmath>

#include"Spring_Window.h"
#include"Spring_Calc.h"
#include "Line_Chart.h"

#include "../graphwidget/Graph.h"

class Spring_Container : public Fl_Window
{
	public:
		Spring_Container(int x,int y,int w,int h,const char* label);
		static void call(Fl_Widget* w,void* v);
		void valuechanged();
		static void timeoutcall(void* data);
		void timeout();
		static void graphchanged(Fl_Widget* w,void* v);
		static void startexport(Fl_Widget* w,void* v){((Spring_Container*)v)->export_win->show();};
		void updategraphs();
		int g;

		static void exportfile(Fl_Widget* w,void* v);

		Fl_Window* export_win;
		Fl_Button* export_button;
		Fl_Check_Button* export_time;
		Fl_Check_Button* export_disp;
		Fl_Check_Button* export_vel;
		Fl_Check_Button* export_acc;
		Fl_Check_Button* export_KE;
		Fl_Check_Button* export_EPE;
		Fl_Check_Button* export_GPE;
		Fl_Check_Button* export_E;
		Fl_Counter* export_min;
		Fl_Counter* export_step;
		Fl_Counter* export_max;
		Fl_File_Input* export_file;
		Spring_Calc calc;
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

		Fl_Menu_Bar* menu;

		Graph graph;


		Fl_Multiline_Output* o_text;

		float t;

		bool changed;

		float round(float num){
			return std::floor(num*1000+.5)/1000;
		}
};
#endif
