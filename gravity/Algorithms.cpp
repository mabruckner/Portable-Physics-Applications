#include "Algorithms.h"
#include "Point.h"

void vertlet_integration(vector<Point>* list,void afunc(pfloat* ax,pfloat* ay,pfloat* az,pfloat x,pfloat y,pfloat z),pfloat delta)
{
	pfloat dt2=delta*delta;
	for(int i=0;i<(int)list->size();i++){
		Point* pt=&(list->at(i));
		pfloat ax=0.0;
		pfloat ay=0.0;
		pfloat az=0.0;
		afunc(&ax,&ay,&az,pt->xpos->data,pt->ypos->data,pt->zpos->data);
		pt->xpos->front->data=2*pt->xpos->data-pt->xpos->back->data+ax*dt2;
		pt->ypos->front->data=2*pt->ypos->data-pt->ypos->back->data+ay*dt2;
		pt->zpos->front->data=2*pt->zpos->data-pt->zpos->back->data+az*dt2;
	}
	for(int i=0;i<(int)list->size();i++){
		list->at(i).advance();
	}
}
void improved_euler(vector<Point>* list,void ffunc(vector<Point>* list,pfloat x,pfloat y,pfloat z),pfloat delta)
{

}
void euler(vector<Point>* list,void afunc(pfloat* ax,pfloat* ay,pfloat* az,pfloat x,pfloat y,pfloat z),pfloat delta)
{
	for(int i=0;i<(int)list->size();i++)
	{
		Point* pt=&(list->at(i));
		pfloat xf=0.0;
		pfloat yf=0.0;
		pfloat zf=0.0;
		afunc(&xf,&yf,&zf,pt->xpos->data,pt->ypos->data,pt->zpos->data);
		pt->xacc->front->data=xf;
		pt->yacc->front->data=yf;
		pt->zacc->front->data=zf;

		pt->xvel->front->data=pt->xvel->data+delta*(pt->xacc->data+pt->xacc->front->data)/2;
		pt->yvel->front->data=pt->yvel->data+delta*(pt->yacc->data+pt->yacc->front->data)/2;
		pt->zvel->front->data=pt->zvel->data+delta*(pt->zacc->data+pt->zacc->front->data)/2;

		pt->xpos->front->data=pt->xpos->data+delta*(pt->xvel->data+pt->xvel->front->data)/2;
		pt->ypos->front->data=pt->ypos->data+delta*(pt->yvel->data+pt->yvel->front->data)/2;
		pt->zpos->front->data=pt->zpos->data+delta*(pt->zvel->data+pt->zvel->front->data)/2;
	}
	for(int i=0;i<(int)list->size();i++){
		list->at(i).advance();
	}
}
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
