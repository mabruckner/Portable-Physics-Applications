#ifndef PLOTRENDER_H
#define PLOTRENDER_H
#include <gtk/gtk.h>
#include "TrackLogic.h"

void setGoalTrack(TrackData* t,MotionData* init);
void setActualTrack(TrackData* t);
void setTime(float t);

void drawHandlerPos(GtkWidget *widget,cairo_t *cr,gpointer data);
void drawHandlerVel(GtkWidget *widget,cairo_t *cr,gpointer data);
void drawHandlerAcc(GtkWidget *widget,cairo_t *cr,gpointer data);

#endif
