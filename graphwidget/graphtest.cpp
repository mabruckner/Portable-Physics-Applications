#include "Graph.h"
#include <FL/Fl.H>
#include <vector>

using namespace std;

int main(int argc,char** argv)
{
	Graph g(10,10,300,300,"OPENGL");
	g.sort(0);
	for(int i=0;i<100;i++){
		vector<double> v=vector<double>();
		v.push_back(i);
		v.push_back(i%10);
		g.add(v);
	}
	g.sort(1);
	g.update();
	g.show();
	return (Fl::run());
}
