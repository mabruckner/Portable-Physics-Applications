#include <gtk/gtk.h>
#include "Circuit.h"
#include "UI.h"

static Circuit map;
static GtkBuilder * builder;
static void init_buttons()
{

}
void init_UI()
{
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder,"builder.ui",NULL);
	GtkWidget* window=gtk_builder_get_object(builder,"window");
	GtkWidget* button=gtk_builder_get_object(builder,"button1");
	GtkWidget* image=gtk_image_new_from_file("wire.bmp");
	gtk_button_set_image(button,image);
	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
}
