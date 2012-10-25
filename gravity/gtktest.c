#include <gtk/gtk.h>
#include "Point.c"

static void print_hello(GtkWidget *widget,gpointer data)
{
	g_print("HELLO_WORLD\n");
	g_print((const char*)data);
}

int main(int argc,char** argv)
{
	GtkWidget *window;
	GtkWidget *button;

	Point p;
	init_point(&p);

	gtk_init(&argc,&argv);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"HELLO WORLD");
	g_signal_connect(window,"destroy",G_CALLBACK (gtk_main_quit),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);

	button=gtk_button_new_with_label("HELLO WORLD");
	g_signal_connect(button,"clicked",G_CALLBACK(print_hello),(gpointer)("IT WORKS!\n"));

	gtk_container_add(GTK_CONTAINER(window),button);
	gtk_widget_show(button);
	gtk_widget_show(window);

	gtk_main();
	return 0;
}
