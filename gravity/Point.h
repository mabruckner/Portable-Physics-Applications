#ifndef POINT_H
#define POINT_H
#include <vector>

using namespace std;

typedef float pfloat;

class Point
{
	public:
		Point(){
			mass = 10;
		};
		~Point(){};

		vector<pfloat> xpos;
		vector<pfloat> ypos;
		vector<pfloat> zpos;

		vector<pfloat> xvel;
		vector<pfloat> yvel;
		vector<pfloat> zvel;

		vector<pfloat> xacc;
		vector<pfloat> yacc;
		vector<pfloat> zacc;

		pfloat mass;
};
#endif
