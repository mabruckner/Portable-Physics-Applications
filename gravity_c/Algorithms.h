#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Point.h"
#include <math.h>

void vertlet_integration(Point* list,int num,void afunc(pfloat* ax,pfloat* ay,pfloat* az,pfloat x,pfloat y,pfloat z),pfloat delta);
void euler(Point* list,int num,void afunc(pfloat* ax,pfloat* ay,pfloat* az,pfloat x,pfloat y,pfloat z),pfloat delta);
//void euler(Point* pt,pfloat x,pfloat y,pfloat z,pfloat delta);

#endif
