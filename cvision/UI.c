#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Circuit.h"
#include "UI.h"
#define PLACE_WIRE 0
#define PLACE_RESISTOR 1
#define PLACE_BATTERY 2
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
double mouseX;
double mouseY;

static double gutter=20;

static void remove_component(int i);

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
		cairo_move_to(cr,x1,y1);
		
		cairo_stroke(cr);
	}
	if(com->type==BATTERY)
	{
		
	}
}
static gboolean draw_callback(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	guint width=gtk_widget_get_allocated_width(widget);
	guint height=gtk_widget_get_allocated_height(widget);
	double sw,sh,spacing;
	sw=((double)width-2*gutter)/grid.width;
	sh=((double)height-2*gutter)/grid.height;
	spacing=MIN(sw,sh);
	cairo_set_source_rgb(cr,0,0,255);
	cairo_arc(cr,mouseX,mouseY,5,0,2*G_PI);
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
static void add_component(Component c)
{
	int i;
	for(i=0;i<grid.map.ccount;i++){
		if(grid.map.components[i].A==c.A&&grid.map.components[i].B==c.B)remove_component(i);
	}

	grid.map.components[grid.map.ccount]=c;
	grid.map.ccount++;
}
static void remove_component(int i)
{
	if(grid.map.components[i].type!=WIRE){
		free(grid.map.components[i].data);
	}
	grid.map.components[i]=grid.map.components[grid.map.ccount-1];	
	grid.map.ccount--;
}
static gboolean press_callback(GtkWidget* widget,GdkEventButton* event,gpointer data)
{
	double mx=event->x;
	double my=event->y;
	double width=gtk_widget_get_allocated_width(widget);
	double height=gtk_widget_get_allocated_height(widget);
	double spacing=MIN((width-2*gutter)/grid.width,(height-2*gutter)/grid.height);
	mx-=width/2.0;
	my-=height/2.0;
	mx=mx/spacing;
	my=my/spacing;
	mx+=grid.width/2.0;
	my+=grid.height/2.0;
	int ia,ib;
	double da,db;
	int i;
	ia=0;ib=0;
	da=db=grid.width+grid.height;
	for(i=0;i<grid.map.vcount;i++){
		double x=grid.map.vertices[i].id%(grid.width+1);
		double y=(int)(grid.map.vertices[i].id/(grid.width+1));
		double d=sqrt((x-mx)*(x-mx)+(y-my)*(y-my));
		if(d<da){
			db=da;
			ib=ia;
			da=d;
			ia=i;
		}else if(d<db){
			db=d;
			ib=i;
		}
	}
	Component c;
	c.type=WIRE;
	c.A=MIN(grid.map.vertices[ia].id,grid.map.vertices[ib].id);
	c.B=MAX(grid.map.vertices[ia].id,grid.map.vertices[ib].id);
	add_component(c);
	gtk_widget_queue_draw_area(widget,0,0,width,height);
	return TRUE;
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
	gtk_widget_add_events(area,GDK_BUTTON_PRESS_MASK);
	g_signal_connect(G_OBJECT(area),"button-press-event",G_CALLBACK(press_callback),NULL);
	g_signal_connect(G_OBJECT(area),"draw",G_CALLBACK(draw_callback),NULL);
	GtkWidget* window=(GtkWidget*)gtk_builder_get_object(builder,"window");
	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	printf("done\n");//gtk_widget_show(window);
}
