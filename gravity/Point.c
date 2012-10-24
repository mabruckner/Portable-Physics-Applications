#ifndef POINT_H
#define POINT_H

#define RING_SIZE 64

typedef double pfloat;
struct rdata
{
	pfloat data;
	rdata* front;
	rdata* back;
};
rdata* Point::init(rdata n_store[RING_SIZE],pfloat start)
{
	for(int i=0;i<RING_SIZE;i++){
		n_store[i].data=start;
		n_store[i].front=n_store+((i+1)%RING_SIZE);
		n_store[i].back=n_store+((i-1)>=0?i-1:RING_SIZE-1);
	}
	return n_store;
}Point::Point()
{
	weight=0;
	xpos=init(xpos_store,0.0);
	ypos=init(ypos_store,0.0);
	zpos=init(zpos_store,0.0);
	xvel=init(xvel_store,0.0);
	yvel=init(yvel_store,0.0);
	zvel=init(zvel_store,0.0);
	xacc=init(xacc_store,0.0);
	yacc=init(yacc_store,0.0);
	zacc=init(zacc_store,0.0);
}
void advance(Point* pt)
{
	pt->xpos=pt->xpos->front;
	pt->ypos=pt->ypos->front;
	pt->zpos=pt->zpos->front;
	pt->xvel=pt->xvel->front;
	pt->yvel=pt->yvel->front;
	pt->zvel=pt->zvel->front;
	pt->xacc=pt->xacc->front;
	pt->yacc=pt->yacc->front;
	pt->zacc=pt->zacc->front;
}
struct Point
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

	void advance();

	rdata* init(rdata n_store[RING_SIZE],pfloat start);
};
#endif
