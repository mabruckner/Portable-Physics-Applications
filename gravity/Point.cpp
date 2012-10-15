#include "Point.h"

Point::Point()
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
void Point::advance()
{
	xpos=xpos->front;
	ypos=ypos->front;
	zpos=zpos->front;
	xvel=xvel->front;
	yvel=yvel->front;
	zvel=zvel->front;
	xacc=xacc->front;
	yacc=yacc->front;
	zacc=zacc->front;
}
rdata* Point::init(rdata n_store[RING_SIZE],pfloat start)
{
	for(int i=0;i<RING_SIZE;i++){
		n_store[i].data=start;
		n_store[i].front=n_store+((i+1)%RING_SIZE);
		n_store[i].back=n_store+((i-1)>=0?i-1:RING_SIZE-1);
	}
	return n_store;
}
