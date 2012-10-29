#ifndef POINT_H
#define POINT_H

#define RING_SIZE 64

typedef double pfloat;

struct rdata_struct
{
	pfloat data;
	struct rdata_struct* front;
	struct rdata_struct* back;
};
typedef struct rdata_struct rdata;
struct Point_struct
{
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
};
typedef struct Point_struct Point;

void init_point(Point *p);
void advance(Point* pt);
#endif
