#ifndef POINT_H
#define POINT_H
#include <vector>

using namespace std;

typedef double pfloat;

class Point
{
	public:
		Point(){
			weight=0;
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

		pfloat weight;
};
#endif
