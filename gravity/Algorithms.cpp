#include "Algorithms.h"
#include "Point.h"

void euler(Point* pt,pfloat xf,pfloat yf,pfloat zf,pfloat delta)
{
	int t=(int)pt->xpos.size();
	pt->xacc.push_back(xf);
	pt->yacc.push_back(yf);
	pt->zacc.push_back(zf);

	pt->xvel.push_back(pt->xvel[t-1]+delta*(pt->xacc[t-1]+pt->xacc[t])/2);
	pt->yvel.push_back(pt->yvel[t-1]+delta*(pt->yacc[t-1]+pt->yacc[t])/2);
	pt->zvel.push_back(pt->zvel[t-1]+delta*(pt->zacc[t-1]+pt->zacc[t])/2);

	pt->xpos.push_back(pt->xpos[t-1]+delta*(pt->xvel[t-1]+pt->xvel[t])/2);
	pt->ypos.push_back(pt->ypos[t-1]+delta*(pt->yvel[t-1]+pt->yvel[t])/2);
	pt->zpos.push_back(pt->zpos[t-1]+delta*(pt->zvel[t-1]+pt->zvel[t])/2);
}
