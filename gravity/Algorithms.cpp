#include "Algorithms.h"
#include "Point.h"

void euler(Point* pt,pfloat xf,pfloat yf,pfloat zf,pfloat delta)
{
	pt->advance();
	pt->xacc->data=xf;
	pt->yacc->data=yf;
	pt->zacc->data=zf;

	pt->xvel->data=pt->xvel->back->data+delta*(pt->xacc->back->data+pt->xacc->data)/2;
	pt->yvel->data=pt->yvel->back->data+delta*(pt->yacc->back->data+pt->yacc->data)/2;
	pt->zvel->data=pt->zvel->back->data+delta*(pt->zacc->back->data+pt->zacc->data)/2;

	pt->xpos->data=pt->xpos->back->data+delta*(pt->xvel->back->data+pt->xvel->data)/2;
	pt->ypos->data=pt->ypos->back->data+delta*(pt->yvel->back->data+pt->yvel->data)/2;
	pt->zpos->data=pt->zpos->back->data+delta*(pt->zvel->back->data+pt->zvel->data)/2;
}
