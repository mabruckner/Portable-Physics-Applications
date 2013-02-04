#include "PlotRender.h"
#include "TrackLogic.h"
#include <stdlib.h>

#define X_RES .05
TrackData* goaltrack;
MotionData* goalinit;
TrackData* actualtrack;
MotionData* actualinit;

//float time;

int goaldatanum=1001;
float* goaldata=NULL;
float* actualdata=NULL;

void setGoalTrack(TrackData* t,MotionData* init)
{
	goaltrack=t;
	goalinit=init;
	int i;
	if(goaldata!=NULL)free(goaldata);
	goaldata=malloc(sizeof(float)*3*goaldatanum);
	float* d=goaldata;
	MotionData pos=*init;
	for(i=0;i<goaldatanum;i++){
		*(d++)=pos.pos;
		*(d++)=pos.vel;
		*(d++)=pos.acc;
		advance(goaltrack,&pos,X_RES);
	}
}
void setActualTrack(TrackData* t,MotionData* init)
{
	actualtrack=t;
	actualinit=init;
	int i;
	if(actualdata!=NULL)free(goaldata);
	actualdata=malloc(sizeof(float)*3*goaldatanum);
	float* d=actualdata;
	MotionData pos=*init;
	for(i=0;i<goaldatanum;i++){
		*(d++)=pos.pos;
		*(d++)=pos.vel;
		*(d++)=pos.acc;
		advance(goaltrack,&pos,X_RES);
	}
}
void setTime(float t)
{

}
static void drawPlot(cairo_t *cr,float x,float y,float width,float hscale,int num,float* data,int skip)
{
	int i=0;
	cairo_save(cr);
	cairo_translate(cr,x,y);
	cairo_scale(cr,width/((num-1)*X_RES),hscale);
	cairo_move_to(cr,0.0,data[0]);
	cairo_line_to(cr,X_RES/2,(data[0]+data[skip])/2);
	for(i=1;i<num-1;i++){
		cairo_curve_to(cr,i*X_RES,data[i*skip],i*X_RES,data[i*skip],(i+.5)*X_RES,(data[i*skip]+data[(i+1)*skip])/2);
	}
	cairo_line_to(cr,(num-1)*X_RES,data[(num-1)*skip]);
	cairo_restore(cr);
}
void drawHandlerPos(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	GtkStyleContext* context=gtk_widget_get_style_context(widget);
	gtk_render_background(context,cr,0.0,0.0,gtk_widget_get_allocated_width(widget),gtk_widget_get_allocated_height(widget));
	cairo_set_line_cap(cr,CAIRO_LINE_CAP_ROUND);
	if(goaldata==NULL)return;

	drawPlot(cr,0,0,gtk_widget_get_allocated_width(widget),4.0,goaldatanum,goaldata,3);

	cairo_save(cr);
	double dash[2]={0.0,5.0};
	cairo_set_dash(cr,dash,2,0.0);
	cairo_set_source_rgb(cr,0.5,0.5,0.5);
	cairo_stroke(cr);
	cairo_restore(cr);

	drawPlot(cr,0,0,gtk_widget_get_allocated_width(widget),4.0,goaldatanum,actualdata,3);

	cairo_set_source_rgb(cr,0.0,0.0,1.0);
	cairo_stroke(cr);
}
void drawHandlerVel(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	GtkStyleContext* context=gtk_widget_get_style_context(widget);
	gtk_render_background(context,cr,0.0,0.0,gtk_widget_get_allocated_width(widget),gtk_widget_get_allocated_height(widget));
	cairo_set_line_cap(cr,CAIRO_LINE_CAP_ROUND);
	if(goaldata==NULL)return;
	

	drawPlot(cr,0,gtk_widget_get_allocated_height(widget)/2,gtk_widget_get_allocated_width(widget),4.0,goaldatanum,goaldata+1,3);

	cairo_save(cr);
	double dash[2]={0.0,5.0};
	cairo_set_dash(cr,dash,2,0.0);
	cairo_set_source_rgb(cr,0.5,0.5,0.5);
	cairo_stroke(cr);
	cairo_restore(cr);

	drawPlot(cr,0,gtk_widget_get_allocated_height(widget)/2,gtk_widget_get_allocated_width(widget),4.0,goaldatanum,actualdata+1,3);

	cairo_set_source_rgb(cr,0.0,1.0,0.0);
	cairo_stroke(cr);

}
void drawHandlerAcc(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	GtkStyleContext* context=gtk_widget_get_style_context(widget);
	gtk_render_background(context,cr,0.0,0.0,gtk_widget_get_allocated_width(widget),gtk_widget_get_allocated_height(widget));
	cairo_set_line_cap(cr,CAIRO_LINE_CAP_ROUND);
	if(goaldata==NULL)return;

	drawPlot(cr,0,gtk_widget_get_allocated_height(widget)/2,gtk_widget_get_allocated_width(widget),4.0,goaldatanum,goaldata+2,3);

	cairo_save(cr);
	double dash[2]={0.0,5.0};
	cairo_set_dash(cr,dash,2,0.0);
	cairo_set_source_rgb(cr,0.5,0.5,0.5);
	cairo_stroke(cr);
	cairo_restore(cr);

	drawPlot(cr,0,gtk_widget_get_allocated_height(widget)/2,gtk_widget_get_allocated_width(widget),4.0,goaldatanum,actualdata+2,3);

	cairo_set_source_rgb(cr,1.0,0.0,0.0);
	cairo_stroke(cr);
}
