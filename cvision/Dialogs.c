#include "UIFunc.h"
#include "Dialogs.h"
#include <math.h>
gchar* format_value(GtkScale* scale,gdouble value,gpointer user_data)
{
	Component* c=(Component*)user_data;
	switch(c->type){
		case BATTERY:
			return g_strdup_printf("%0.1fV",value);
		case RESISTOR:
			return g_strdup_printf("%0.1f\u2126",value);
	}
	return "";
}
void edit_dialog(Component* component)
{
	if(component->type==WIRE)return;
	//GtkAdjustment* adjustment=gtk_adjustment_new(*(double*)component->data,component->type==BATTERY ? -20 : 0, 20,10,10,0);
	GtkWidget* scale=gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,component->type==BATTERY ? -20 : 0,20,.1);
	gtk_range_set_value(scale,*(double*)component->data);
	g_signal_connect(scale,"format-value",G_CALLBACK(format_value),(gpointer)component);
	GtkWidget* dialog=gtk_dialog_new_with_buttons("EDIT",GTK_WINDOW(gtk_builder_get_object(builder,"window")),GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,GTK_STOCK_OK,GTK_RESPONSE_ACCEPT,GTK_STOCK_CANCEL,GTK_RESPONSE_REJECT,NULL);
	gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),GTK_WIDGET(scale));
	gtk_widget_show(scale);
	gint result=gtk_dialog_run(GTK_DIALOG(dialog));
	switch(result){
		case GTK_RESPONSE_ACCEPT:
			*(double*)component->data=gtk_range_get_value(scale);
	}
	gtk_widget_destroy(GTK_WIDGET(dialog));
}

