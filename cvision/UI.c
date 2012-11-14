#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"
#include "UI.h"
typedef struct
{
	Circuit map;
	int width;
	int height;
} Grid;
static Grid grid;
static char draw_state;

static cairo_surface_t *surface;
static GtkBuilder * builder;
static void draw_component(cairo_t *cr,double unit,double x1,double y1,double x2,double y2,Component* com)
{
	if(com->type==WIRE)
	{
		cairo_move_to(cr,x1,y1);
		cairo_line_to(cr,x2,y2);
		cairo_stroke(cr);
		return;
	}
	if(com->type==RESISTOR)
	{
		
	}
	if(com->type==BATTERY)
	{
		
	}
}
static gboolean draw_callback(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	double gutter=20;
	guint width=gtk_widget_get_allocated_width(widget);
	guint height=gtk_widget_get_allocated_height(widget);
	double sw,sh,spacing;
	sw=((double)width-2*gutter)/grid.width;
	sh=((double)height-2*gutter)/grid.height;
	spacing=MIN(sw,sh);
	cairo_translate(cr,(double)width/2,(double)height/2);
	cairo_translate(cr,-(double)grid.width/2.0*spacing,-(double)grid.height/2.0*spacing);
	int i,j;
	cairo_set_source_rgb(cr,255,0,0);
	for(i=0;i<grid.map.ccount;i++)
	{
		Component* c=grid.map.components+i;
		int A=c->A;
		int B=c->B;
		draw_component(cr,spacing,spacing*(A%(grid.width+1)),spacing*(A/(grid.width+1)),spacing*(B%(grid.width+1)),spacing*(B/(grid.width+1)),c);
	}
	cairo_set_source_rgb(cr,0,0,0);
	for(i=0;i<=grid.width;i++)
	{
		for(j=0;j<=grid.height;j++)
		{
			cairo_arc(cr,i*spacing,j*spacing,5,0,2*G_PI);
			cairo_stroke(cr);
		}
	}
	cairo_set_source_rgb(cr,0,255,0);
	cairo_arc(cr,250,250,250,0,2*G_PI);
	cairo_stroke(cr);
return FALSE;
}
static void init_grid(int width,int height)
{
	grid.map.vertices=NULL;
	grid.map.components=NULL;
	while(grid.map.vertices==NULL||grid.map.components==NULL)
	{
		grid.width=width;
		grid.height=height;
		grid.map.vcount=(width+1)*(height+1);
		grid.map.vertices=(Vertex*)calloc(grid.map.vcount,sizeof(Vertex));
		grid.map.components=(Component*)calloc((width+1)*height+(height+1)*width,sizeof(Component));
		grid.map.ccount=0;
		break;//<-REPLACE WITH HANDLING ROUTINES SHOULD THE ALLOCATIONS FAIL
	}
	int i;
	for(i=0;i<grid.map.vcount;i++)
	{
		grid.map.vertices[i].id=i;
	}
}
static void reset_grid()
{
}
static void init_buttons()
{

}
void init_UI()
{
	init_grid(10,10);
	printf("beginning\n");
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder,"builder.ui",NULL);
	GtkWidget* area=(GtkWidget*)gtk_builder_get_object(builder,"circuitarea");
	g_signal_connect(G_OBJECT(area),"draw",G_CALLBACK(draw_callback),NULL);
	GtkWidget* window=(GtkWidget*)gtk_builder_get_object(builder,"window");
	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	printf("done\n");//gtk_widget_show(window);
}
