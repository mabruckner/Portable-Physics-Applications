#include "Constants.h"
#include "Point.h"
#include "Algorithms.h"
#include <stdio.h>
#include <math.h>

int add_point(Point pt)
{
	if(num>=MAX_POINTS){
		return MAX_POINTS-num-1;
	}
	list[num]=pt;
	num++;
	return num-1;
}
int remove_point(int index)
{
	if(index>=num)
	{
		return num-index-1;
	}
	if(num<=0){
		return num-1;
	}
	int i=0;
	for(i=index;i<num-1;i++){
		list[i]=list[i+1];
	}
	num--;
	return num;
}
pfloat dist(pfloat x1,pfloat y1,pfloat z1,pfloat x2,pfloat y2,pfloat z2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
}

void accvect(pfloat* ax,pfloat* ay,pfloat* az,pfloat x,pfloat y,pfloat z)
{
	pfloat ox=0.0;
	pfloat oy=0.0;
	pfloat oz=0.0;
	int i=0;
	for(i=0;i<(int)num;i++){
		Point* p=&list[i];
		pfloat d=dist(x,y,z,p->xpos->data,p->ypos->data,p->zpos->data);
		if(d<=.1){
			continue;
		}
		pfloat mag=C*p->charge/(d*d);
		ox+=mag*(p->xpos->data-x)/d;
		oy+=mag*(p->ypos->data-y)/d;
		oz+=mag*(p->zpos->data-z)/d;
	}
	*ax=ox;
	*ay=oy;
	*az=oz;
}

int main(int argc,char** argv)
{
	Point p;
	init_point(&p);
	add_point(p);
	return 0;
}
