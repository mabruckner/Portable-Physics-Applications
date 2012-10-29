#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "Point.h"

void vertlet_integration(vector<Point>* list,void afunc(pfloat* ax,pfloat* ay,pfloat* az,pfloat x,pfloat y,pfloat z),pfloat delta);
void euler(vector<Point>* list,void afunc(pfloat* ax,pfloat* ay,pfloat* az,pfloat x,pfloat y,pfloat z),pfloat delta);
void euler(Point* pt,pfloat x,pfloat y,pfloat z,pfloat delta);

#endif
