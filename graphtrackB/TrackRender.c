#include <gtk/gtk.h>
#include <stdio.h>
#include "TrackRender.h"

static TrackData* track=NULL;
static float pos=0.0;
void setTrack(TrackData* newtrack)
{
	track=newtrack;
}
void setPos(float p)
{
	pos=p;
}

void drawHandler(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	GtkStyleContext* context=gtk_widget_get_style_context(widget);
	int i;
	gtk_render_background(context,cr,0.0,0.0,gtk_widget_get_allocated_width(widget),gtk_widget_get_allocated_height(widget));
	gtk_render_arrow(context,cr,0.0,50,50,20);
	gtk_render_line(context,cr,0.0,20,200,20);


	if(track==NULL)return;

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
	for(i=0;sum<=pos;i++){sum+=track->widths[i];/*printf("%i\n",i);*/}
	i--;sum-=track->widths[i];printf("%i,",i);
	//printf("%g,%g\n",pos,h-hf*(track->heights[i]*(pos-sum)+track->heights[i+1]*(track->widths[i]-(pos-sum)))/track->widths[i]);
	gtk_render_arrow(context,cr,0.0,pos*wf-10,h-hf*(track->heights[i+1]*(pos-sum)+track->heights[i]*(track->widths[i]-(pos-sum)))/track->widths[i],20);

	gtk_render_arrow(context,cr,0.0,pos*wf-10,100,20);
	gtk_render_frame(context,cr,0.0,0.0,gtk_widget_get_allocated_width(widget),gtk_widget_get_allocated_height(widget));
	//cr_save(cr);
	//cr_restore(cr);
}
