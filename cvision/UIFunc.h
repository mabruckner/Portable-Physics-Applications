#ifndef UIFUNC_H
#define UIFUNC_H
#include <gtk/gtk.h>
#include "Circuit.h"

#define PLACE_WIRE 0
#define PLACE_RESISTOR 1
#define PLACE_BATTERY 2

typedef struct
{
	Circuit map;
	int width;
	int height;
} Grid;

Grid grid;
char draw_state;
GtkBuilder* builder;

void draw_component(cairo_t *cr,double unit,double x1,double y1,double x2,double y2,Component* com);
void remove_component(int i);
void add_component(Component c);

#endif
