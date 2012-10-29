#include "Point.h"
static rdata* init(rdata n_store[RING_SIZE],pfloat start)
{
	int i;
	for(i=0;i<RING_SIZE;i++){
		n_store[i].data=start;
		n_store[i].front=n_store+((i+1)%RING_SIZE);
		n_store[i].back=n_store+((i-1)>=0?i-1:RING_SIZE-1);
	}
	return n_store;
}
void init_point(Point *p)
{
	p->weight=0;
	p->xpos=init(p->xpos_store,0.0);
	p->ypos=init(p->ypos_store,0.0);
	p->zpos=init(p->zpos_store,0.0);
	p->xvel=init(p->xvel_store,0.0);
	p->yvel=init(p->yvel_store,0.0);
	p->zvel=init(p->zvel_store,0.0);
	p->xacc=init(p->xacc_store,0.0);
	p->yacc=init(p->yacc_store,0.0);
	p->zacc=init(p->zacc_store,0.0);
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
