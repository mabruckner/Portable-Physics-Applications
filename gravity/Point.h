#ifndef POINT_H
#define POINT_H

#define RING_SIZE 1024

#include <vector>

using namespace std;

typedef double pfloat;
struct rdata
{
	pfloat data;
	rdata* front;
	rdata* back;
};
class Point
{
	public:
		Point();
		~Point(){};

		rdata* xpos;
		rdata* ypos;
		rdata* zpos;
		rdata* xvel;
		rdata* yvel;
		rdata* zvel;
		rdata* xacc;
		rdata* yacc;
		rdata* zacc;

		pfloat weight;

		rdata xpos_store[RING_SIZE];
		rdata ypos_store[RING_SIZE];
		rdata zpos_store[RING_SIZE];
		rdata xvel_store[RING_SIZE];
		rdata yvel_store[RING_SIZE];
		rdata zvel_store[RING_SIZE];
		rdata xacc_store[RING_SIZE];
		rdata yacc_store[RING_SIZE];
		rdata zacc_store[RING_SIZE];

		void advance();
	private:
		rdata* init(rdata n_store[RING_SIZE],pfloat start);
};
#endif
