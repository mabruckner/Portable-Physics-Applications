#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "TrackLogic.h"
#include "TrackRender.h"
#include "PlotRender.h"
	TrackData t;
	MotionData pos;
	float x=1;
	float v=0;
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
g_signal_connect(object,signal_name,G_CALLBACK(drawHandler),NULL);
	}else if(strcmp("draw_pos_graph",handler_name)==0){
g_signal_connect(object,signal_name,G_CALLBACK(drawHandlerPos),NULL);
	}else if(strcmp("draw_vel_graph",handler_name)==0){
g_signal_connect(object,signal_name,G_CALLBACK(drawHandlerVel),NULL);
	}
}
gboolean timeout(GtkWidget *widget)
{
		advance(&t,&pos,.1);
		setPos(pos.x);
	gtk_widget_queue_draw(widget);
	return TRUE;
}
int main(int argc,char** argv)
{printf("%g\n\n",sqrt(-1));
	float w[]={2,2,2,2,2,2,2,2,2,2};
	float h[]={12.5,8.0,4.5,2.0,0.5,0.0,0.5,2.0,4.5,8.0,12.5};
	t.num=11;
	t.widths=w;
	t.heights=h;
	setTrack(&t);
	int i;
	pos.g=-4;
	pos.x=1;
	pos.vel=0;
	MotionData tmp=pos;
	setGoalTrack(&t,&pos);
		setPos(pos.x);
	/*for(i=0;i<100;i++){
		advance(&t,&x,&v,1,-4);
		printf("%i\t%g\t%g\n",i,x,v);
	}*/

	gtk_init(&argc,&argv);
	GtkBuilder* builder=gtk_builder_new();
	gtk_builder_add_from_file(builder,"graphtrack.ui",NULL);
	gtk_builder_connect_signals_full(builder,connectFunc,NULL);
	GtkWidget* widget=gtk_builder_get_object(builder,"trackarea");
	/*GdkRGBA color;
	color.red=0xFFFF;
	color.green=0x0000;
	color.blue=0x0000;
	color.alpha=0xFFFF;
	gtk_widget_override_background_color(widget,GTK_STATE_FLAG_NORMAL,&color);*/
	printf("%p\n",gtk_widget_get_style_context(widget));

	GError** error=NULL;
	GtkCssProvider* style=gtk_css_provider_new();
	gtk_css_provider_load_from_path(style,"style.css",error);
	if(error==NULL)printf("STYLE LOADED!\n");
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),style,GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	g_timeout_add(50,timeout,widget);

	gtk_main();
	return 0;
}
