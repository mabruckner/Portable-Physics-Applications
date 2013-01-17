#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "TrackLogic.h"
void draw(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	GtkStyleContext* context=gtk_widget_get_style_context(widget);
	gtk_render_frame(context,cr,10,10,gtk_widget_get_allocated_width(widget)-20,gtk_widget_get_allocated_height(widget)-20);printf("Drawing\n");
	gtk_render_arrow(context,cr,0.0,50,50,20);
}
void connectFunc(GtkBuilder* builder,GObject *object,const gchar *signal_name,const gchar *handler_name,GObject *connect_object,GConnectFlags flags,gpointer user_data)
{
	printf("%s - %s\n",signal_name,handler_name);
	if(strcmp("gtk_main_quit",handler_name)==0){
		g_signal_connect(object,signal_name,G_CALLBACK(gtk_main_quit),NULL);
	}else if(strcmp("draw_track",handler_name)==0){
g_signal_connect(object,signal_name,G_CALLBACK(draw),NULL);
	}
}
int main(int argc,char** argv)
{printf("%g\n\n",sqrt(-1));
	TrackData t;
	float w[]={10,10};
	float h[]={10.0,0.0,10.0};
	float x=7;
	float v=0.0;
	t.num=3;
	t.widths=w;
	t.heights=h;
	int i;
	for(i=0;i<100;i++){
		advance(&t,&x,&v,1,-4);
		printf("%i\t%g\t%g\n",i,x,v);
	}

	gtk_init(&argc,&argv);
	GtkBuilder* builder=gtk_builder_new();
	gtk_builder_add_from_file(builder,"graphtrack.ui",NULL);
	gtk_builder_connect_signals_full(builder,connectFunc,NULL);
	GtkWidget* widget=gtk_builder_get_object(builder,"trackarea");
	printf("%p\n",gtk_widget_get_style_context(widget));
	gtk_main();
	return 0;
}
