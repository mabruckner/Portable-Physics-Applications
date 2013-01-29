#ifndef PLOTRENDER_H
#define PLOTRENDER_H

void setGoalTrack(TrackData* t);
void setActualTrack(TrackData* t);
void setTime(float t);

void drawHandlerPos(GtkWidget *widget,cairo_t *cr,gpointer data);
void drawHandlerVel(GtkWidget *widget,cairo_t *cr,gpointer data);
void drawHandlerAcc(GtkWidget *widget,cairo_t *cr,gpointer data);

#endif
