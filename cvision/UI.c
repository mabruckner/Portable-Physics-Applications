#include <gtk/gtk.h>
#include <stdio.h>
#include "Circuit.h"
#include "UI.h"
typedef struct
{
	Circuit map;
	int width;
	int height;
	double* data;
	int datalength;
}Grid;
static Grid grid;
static char draw_state;

static cairo_surface_t *surface;
static GtkBuilder * builder;

static gboolean draw_callback(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	guint width;
	guint height;
	cairo_set_source_rgb(cr,0,0,0);
	cairo_arc(cr,250,250,250,0,2*G_PI);
	cairo_stroke(cr);
return FALSE;
}
static void init_buttons()
{

}
void init_UI()
{
	printf("beginning\n");
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder,"builder.ui",NULL);
	GtkWidget* area=(GtkWidget*)gtk_builder_get_object(builder,"circuitarea");
	g_signal_connect(G_OBJECT(area),"draw",G_CALLBACK(draw_callback),NULL);
	GtkWidget* window=(GtkWidget*)gtk_builder_get_object(builder,"window");
	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	printf("done\n");//gtk_widget_show(window);
}
