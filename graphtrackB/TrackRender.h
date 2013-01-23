#ifndef TRACKRENDER_H
#define TRACKRENDER_H

#include "TrackLogic.h"

void setTrack(TrackData* t);
void setPos(float pos);
void drawHandler(GtkWidget *widget,cairo_t *cr,gpointer data);

#endif
