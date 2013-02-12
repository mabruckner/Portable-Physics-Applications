#ifndef TRACKRENDER_H
#define TRACKRENDER_H

#include "TrackLogic.h"

#define ALLOW_EDIT 1
#define VERTICAL_SNAP 2
#define HORIZONTAL_SNAP 4

#define VERTICAL_RESTRICT 8
#define HORIZONTAL_RESTRICT 16


void setTrack(TrackData* t);
void setPos(float pos);
gboolean mouseHandler(GtkWidget* widget,GdkEvent * evt,gpointer data);
void drawHandler(GtkWidget *widget,cairo_t *cr,gpointer data);
void motionHandler();

#endif
