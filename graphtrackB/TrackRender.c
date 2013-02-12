#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include "TrackRender.h"
static int flags=ALLOW_EDIT|VERTICAL_SNAP|HORIZONTAL_SNAP;

static float wstep=2.0;
static float hstep=1.0;
static int wnum=20;
static int hnum=20;

static TrackData* track=NULL;
static float pos=0.0;

static float mouseX;
static float mouseY;
static int mousedown;
static int selection;
void setTrack(TrackData* newtrack)
{
	track=newtrack;
}
void setPos(float p)
{
	pos=p;
}
gboolean mouseHandler(GtkWidget* widget,GdkEvent * evt,gpointer data)
{
	if(evt->type==GDK_BUTTON_PRESS){
		GdkEventButton* event=(GdkEventButton*)evt;
		mousedown=event->button;
	}else if(evt->type==GDK_BUTTON_RELEASE){
		GdkEventButton* event=(GdkEventButton*)evt;
		mousedown=0;
	}
	GdkEventMotion* event=(GdkEventMotion*)evt;
	mouseX=event->x;
	mouseY=event->y;
}
void renderTrack(cairo_t *cr,float x,float y,float width,float height)
{
	int i;
	float sum=0.0;
	float xpos=0.0;
	float wscale=width/(wnum*wstep);
	float hscale=height/(hnum*hstep);
	for(i=0;i<track->num-1;i++)sum+=track->widths[i];
	cairo_save(cr);
	cairo_set_line_cap(cr,CAIRO_LINE_CAP_ROUND);
	cairo_set_line_join(cr,CAIRO_LINE_JOIN_ROUND);
	cairo_translate(cr,x,y);
	cairo_save(cr);
	cairo_scale(cr,wscale,hscale);
	if(flags&HORIZONTAL_SNAP){
		for(i=0;i<=wnum;i++){
			cairo_move_to(cr,i*wstep,0);
			cairo_line_to(cr,i*wstep,hnum*hstep);
		}
	}
	if(flags&VERTICAL_SNAP){
		for(i=0;i<=hnum;i++){
			cairo_move_to(cr,0,i*hstep);
			cairo_line_to(cr,wnum*wstep,i*hstep);
		}
	}
	cairo_restore(cr);
	cairo_set_source_rgb(cr,0.5,0.5,0.5);
	cairo_stroke(cr);
	cairo_save(cr);
	cairo_scale(cr,wscale,hscale);
	if(!mousedown){
		selection=-1;
		for(i=0;i<track->num;i++){
			double xnum=mouseX;
			double ynum=mouseY;
			cairo_device_to_user(cr,&xnum,&ynum);
			xnum=(xnum-xpos)/wstep;
			ynum=(ynum-track->heights[i])/hstep;
			if(sqrt(xnum*xnum+ynum*ynum)<=.5)selection=i;
			if(i<track->num-1)xpos+=track->widths[i];
		}
	}else{
		//printf("%i\n",selection);
		if(selection>=0){
			double xnum=mouseX;
			double ynum=mouseY;
			cairo_device_to_user(cr,&xnum,&ynum);
			/*if(!(flags&HORIZONTAL_RESTRICT)){
				int sumtmp=0.0;
				int j;
				if(flags&HORIZONTAL_SNAP){
					track->heights[selection]=floor(ynum/hstep+.5)*hstep;
				}else{
					track->heights[selection]=ynum;
				}
			}*/
			if(!(flags&VERTICAL_RESTRICT)){
				if(flags&VERTICAL_SNAP){
					track->heights[selection]=floor(ynum/hstep+.5)*hstep;
				}else{
					track->heights[selection]=ynum;
				}
				track->heights[selection]=track->heights[selection]<0 ? 0 : (track->heights[selection]>hstep*hnum ? hstep*hnum : track->heights[selection]);
			}
		}
	}
	xpos=0;
	cairo_move_to(cr,0,track->heights[0]);
	for(i=0;i<track->num-1;i++){
		xpos+=track->widths[i];
		cairo_line_to(cr,xpos,track->heights[i+1]);
	}
	xpos=0;
	cairo_restore(cr);
	cairo_set_source_rgb(cr,0.0,0.0,0.0);
	cairo_stroke(cr);
	for(i=0;i<track->num-1;i++){
		cairo_new_sub_path(cr);
		cairo_arc(cr,xpos*wscale,track->heights[i]*hscale,selection==i?5:2,0,2*M_PI);
		cairo_close_path(cr);
		xpos+=track->widths[i];
	}
	cairo_new_sub_path(cr);
	cairo_arc(cr,xpos*wscale,track->heights[i]*hscale,selection==i?5:2,0,2*M_PI);
	cairo_close_path(cr);

	cairo_fill_preserve(cr);
	cairo_stroke(cr);

	sum=0;
	for(i=0;i<track->num-1&&pos>sum;i++)sum+=track->widths[i];
	i--;
	sum-=track->widths[i];
	cairo_arc(cr,wscale*pos,hscale*(track->heights[i]+(track->heights[i+1]-track->heights[i])*((pos-sum)/track->widths[i])),5,0,2*M_PI);
	cairo_fill_preserve(cr);
	cairo_stroke(cr);

	cairo_restore(cr);
}
void drawHandler(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	GtkStyleContext* context=gtk_widget_get_style_context(widget);
	int i;
	gtk_render_background(context,cr,0.0,0.0,gtk_widget_get_allocated_width(widget),gtk_widget_get_allocated_height(widget));
	gtk_render_arrow(context,cr,0.0,50,50,20);
	gtk_render_line(context,cr,0.0,20,200,20);

	cairo_arc(cr,mouseX,mouseY,10,0,2*M_PI);
	if(track==NULL)return;
/*
	float padding=20;
	float radius=10;

	float width=0;
	float height=0;
	for(i=0;i<track->num-1;i++)width+=track->widths[i];
	for(i=0;i<track->num;i++)height=track->heights[i]>height ? track->heights[i] : height;
	//printf("%g,%g\n",width,height);
	float wf=gtk_widget_get_allocated_width(widget)/width;
	float hf=gtk_widget_get_allocated_height(widget)/height;
	//printf("%g,%g\n",wf,hf);
	float sum=0.0;
	float w=gtk_widget_get_allocated_width(widget);
	float h=gtk_widget_get_allocated_height(widget);
	for(i=0;i<track->num-1;i++){
		gtk_render_line(context,cr,sum*wf,h,sum*wf,h-track->heights[i]*hf);
		gtk_render_line(context,cr,sum*wf,h,(sum+track->widths[i])*wf,h);
		gtk_render_line(context,cr,sum*wf,h-track->heights[i]*hf,(sum+track->widths[i])*wf,h-track->heights[i+1]*hf);
		sum+=track->widths[i];
	}
	gtk_render_line(context,cr,sum*wf,0.0,sum*wf,track->heights[i]*hf);
	sum=0;
	for(i=0;sum<=pos;i++){sum+=track->widths[i];}
	i--;sum-=track->widths[i];//printf("%i,",i);
	//printf("%g,%g\n",pos,h-hf*(track->heights[i]*(pos-sum)+track->heights[i+1]*(track->widths[i]-(pos-sum)))/track->widths[i]);
	gtk_render_arrow(context,cr,0.0,pos*wf-10,h-hf*(track->heights[i+1]*(pos-sum)+track->heights[i]*(track->widths[i]-(pos-sum)))/track->widths[i],20);*/
	renderTrack(cr,10,gtk_widget_get_allocated_height(widget)-10,gtk_widget_get_allocated_width(widget)-20,-(gtk_widget_get_allocated_height(widget)-20));
//	gtk_render_arrow(context,cr,0.0,pos*wf-10,100,20);
	gtk_render_frame(context,cr,0.0,0.0,gtk_widget_get_allocated_width(widget),gtk_widget_get_allocated_height(widget));
	//cr_save(cr);
	//cr_restore(cr);
}
