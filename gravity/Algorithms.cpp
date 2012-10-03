#include "Algorithms.h"
#include "Point.h"

void euler(Point* pt,pfloat xf,pfloat yf,pfloat zf,pfloat delta)
{
	int t=(int)pt->xpos.size();
	pt->xacc.push_back(xf/pt->mass);
	pt->yacc.push_back(yf/pt->mass);
	pt->zacc.push_back(zf/pt->mass);

	pt->xvel.push_back(delta*pt->xacc[t]);
	pt->yvel.push_back(delta*pt->yacc[t]);
	pt->zvel.push_back(delta*pt->zacc[t]);

	pt->xpos.push_back(delta*pt->xvel[t]);
	pt->ypos.push_back(delta*pt->yvel[t]);
	pt->zpos.push_back(delta*pt->zvel[t]);
}
