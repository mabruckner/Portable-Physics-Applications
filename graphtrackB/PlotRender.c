#include "PlotRender.h"
#include "TrackLogic.h"

#define X_RES .1
TrackData* goaltrack;
MotionData* goalinit;

int goaldatanum=1001;
float* goaldata=NULL;

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
void setActualTrack(TrackData* t)
{

}
void setTime(float t)
{

}
static void drawPlot(cairo_t *cr,float x,float y,float width,float hscale,int num,float* data)
{


}
void drawHandlerPos(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	GtkStyleContext* context=gtk_widget_get_style_context(widget);
	int i;
	gtk_render_background(context,cr,0.0,0.0,gtk_widget_get_allocated_width(widget),gtk_widget_get_allocated_height(widget));
	if(goaldata==NULL)return;
	cairo_save(cr);
	cairo_scale(cr,gtk_widget_get_allocated_width(widget)/(X_RES*(goaldatanum-1)),4.0);
	float a=0.0;
	float b=(goaldata[0]+goaldata[3])/2;
	cairo_move_to(cr,X_RES/2,b);
	for(i=1;i<goaldatanum-1;i++){
		a=b;
		b=(goaldata[i*3]+goaldata[(i+1)*3])/2;
		cairo_curve_to(cr,i*X_RES,goaldata[i*3],i*X_RES,goaldata[i*3],(i+.5)*X_RES,b);
		//cairo_line_to(cr,(i)*X_RES,b);
	}
	cairo_line_to(cr,X_RES*(goaldatanum-1),goaldata[(goaldatanum-1)*3]);
	cairo_restore(cr);
	cairo_set_source_rgb(cr,0.0,0.0,1.0);
	cairo_stroke(cr);
}
void drawHandlerVel(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	GtkStyleContext* context=gtk_widget_get_style_context(widget);
	int i;
	gtk_render_background(context,cr,0.0,0.0,gtk_widget_get_allocated_width(widget),gtk_widget_get_allocated_height(widget));
	if(goaldata==NULL)return;
	cairo_save(cr);
	cairo_translate(cr,0.0,gtk_widget_get_allocated_height(widget)/2.0);
	cairo_scale(cr,gtk_widget_get_allocated_width(widget)/(X_RES*(goaldatanum-1)),4.0);
	float a=0.0;
	float b=(goaldata[1]+goaldata[4])/2;
	cairo_move_to(cr,X_RES/2,b);
	for(i=1;i<goaldatanum-1;i++){
		a=b;
		b=(goaldata[i*3+1]+goaldata[(i+1)*3+1])/2;
		cairo_curve_to(cr,i*X_RES,goaldata[i*3+1],i*X_RES,goaldata[i*3+1],(i+.5)*X_RES,b);
		//cairo_line_to(cr,(i)*X_RES,b);
	}
	cairo_line_to(cr,X_RES*(goaldatanum-1),goaldata[(goaldatanum-1)*3+1]);
	cairo_restore(cr);
	cairo_set_source_rgb(cr,0.0,1.0,0.0);
	cairo_stroke(cr);

}
void drawHandlerAcc(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	GtkStyleContext* context=gtk_widget_get_style_context(widget);
	int i;
	gtk_render_background(context,cr,0.0,0.0,gtk_widget_get_allocated_width(widget),gtk_widget_get_allocated_height(widget));
	if(goaldata==NULL)return;
	cairo_save(cr);
	cairo_translate(cr,0.0,gtk_widget_get_allocated_height(widget)/2.0);
	cairo_scale(cr,gtk_widget_get_allocated_width(widget)/(X_RES*(goaldatanum-1)),4.0);
	float a=0.0;
	float b=(goaldata[2]+goaldata[5])/2;
	cairo_move_to(cr,X_RES/2,b);
	for(i=1;i<goaldatanum-1;i++){
		a=b;
		b=(goaldata[i*3+2]+goaldata[(i+1)*3+2])/2;
		cairo_curve_to(cr,i*X_RES,goaldata[i*3+2],i*X_RES,goaldata[i*3+2],(i+.5)*X_RES,b);
		//cairo_line_to(cr,(i)*X_RES,b);
	}
	cairo_line_to(cr,X_RES*(goaldatanum-1),goaldata[(goaldatanum-1)*3+2]);
	cairo_restore(cr);
	cairo_set_source_rgb(cr,1.0,0.0,0.0);
	cairo_stroke(cr);
}
