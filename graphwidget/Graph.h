#ifndef GRAPH_H
#define GRAPH_H

#include <FL/Fl.H>
#include <FL/gl.h>
#include <FL/Fl_Gl_Window.H>

#include <vector>
#include <string>

using namespace std;

class Graph : public Fl_Gl_Window
{
	private:
		vector<vector<double> > data;
		vector<vector<double> > ordered;
		vector<string> units;
		vector<string> labels;
		int orderby;
		int xvar;
		int yvar;
		bool connect;
		bool mouseover;
		double value;
		double mousex;
		double mousey;

		void FixViewport(int w,int h);
		float border;
		float bborder;
		float lborder;

		void sort(int start,int end);
	protected:
		void draw();
	public:
		Graph(int x,int y,int w,int h,const char* label);
		void resize(int x,int y,int w,int h);

		void scatter(bool is){connect=!is;};
		bool scatter(){return !connect;};

		void xaxis(int x);
		int xaxis(){return xvar;};

		void yaxis(int y){yvar = y;}
		int yaxis(){return yvar;};

		void sort(int axis){orderby=axis;ordered=data;sort(0,(int)ordered.size()-1);};
		int sort(){return orderby;};

		void ptdata(vector<vector<double> > d){data=d;ordered=data;sort(0,(int)ordered.size()-1);};
		vector<vector<double> > ptdata(){return data;};

		void add(vector<double> pt){data.push_back(pt);ordered.push_back(pt);};
		void set(int index,vector<double> pt){data[index]=pt;ordered[index]=pt;};

		void update(){sort(sort());redraw();};

		void select(double v);
		double select();

		void unitlist(vector<string> l){units=l;};
		vector<string> unitlist(){return units;};

		void labellist(vector<string> l){labels=l;};
		vector<string> labellist(){return labels;};
};

#endif
