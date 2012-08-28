#ifndef LINE_CHART_H
#define LINE_CHART_H

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>

#include <vector>
#include <utility>
#include <cmath>


using namespace std;

class Line_Chart : public Fl_Widget
{
		bool boundrange;
		double minrange;
		double maxrange;
		void draw_line_chart();
	protected:
		vector<pair<double,double> > data;
	public:
		Line_Chart(int x,int y,int w,int h,const char* label);
		void draw();
		int add(double x,double y);
		void update(int i,double x,double y);
		void rangebounds(bool yes,double min,double max);
};
#endif