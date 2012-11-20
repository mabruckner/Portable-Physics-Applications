#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "UIFunc.h"
#include "UI.h"


static cairo_surface_t *surface;
double mouseX;
double mouseY;

static double gutter=20;

void draw_component(cairo_t *cr,PangoContext* pc,double unit,double x1,double y1,double x2,double y2,Component* com)
{
	PangoLayout* pn=pango_layout_new(pc);
	char buffer[20];
	sprintf(buffer,"%.3gA",com->current);
	cairo_move_to(cr,(x1+x2)/2,(y1+y2)/2);
	pango_layout_set_text(pn,buffer,-1);
	cairo_save(cr);
	cairo_translate(cr,(x1+x2)/2,(y1+y2)/2);
	double ang=atan2(y2-y1,x2-x1);
	if((ang>90&&ang<270)){
		ang-=180;
	}
	int w=0;
	int h=0;
	pango_layout_get_pixel_size(pn,&w,&h);
	cairo_rotate(cr,ang);
	cairo_move_to(cr,-w/2,10);
	pango_cairo_update_layout(cr,pn);
	pango_cairo_show_layout(cr,pn);
	
	cairo_restore(cr);
	if(com->type==WIRE)
	{
		cairo_move_to(cr,x1,y1);
		cairo_line_to(cr,x2,y2);
		cairo_stroke(cr);
		return;
	}
	if(com->type==RESISTOR)
	{
		//char buffer[20];
		//sprintf(buffer,"%g\u2126 %gA",*(double*)com->data,com->current);
		cairo_move_to(cr,x1,y1);
		cairo_save(cr);
		cairo_translate(cr,(x1+x2)/2,(y1+y2)/2);
		/*cairo_move_to(cr,unit*.2,unit*.2);
		PangoLayout* pn=pango_layout_new(pc);
		pango_layout_set_text(pn,buffer,-1);
		pango_cairo_update_layout(cr,pn);
		pango_cairo_show_layout(cr,pn);*/
		cairo_scale(cr,unit,unit);
		cairo_rotate(cr,atan2(y2-y1,x2-x1));
		cairo_line_to(cr,-.25,0);
		cairo_line_to(cr,-.1875,.125);
		cairo_line_to(cr,-.0625,-.125);
		cairo_line_to(cr,.0625,.125);
		cairo_line_to(cr,.1875,-.125);
		cairo_line_to(cr,.25,0);
		cairo_restore(cr);
		cairo_line_to(cr,x2,y2);
		cairo_stroke(cr);

		cairo_save(cr);
		cairo_translate(cr,(x1+x2)/2,(y1+y2)/2);
		cairo_rotate(cr,ang);
		sprintf(buffer,"%g\u2126",*(double*)com->data);
		pango_layout_set_text(pn,buffer,-1);
		pango_layout_get_pixel_size(pn,&w,&h);
		cairo_move_to(cr,-w/2,-h-10);
		pango_cairo_update_layout(cr,pn);
		pango_cairo_show_layout(cr,pn);
		cairo_restore(cr);
		cairo_new_path(cr);
		return;
	}
	if(com->type==BATTERY)
	{
		if(*(double*)com->data==0){
			cairo_save(cr);
			
			const double dash[]={10};
			cairo_set_dash(cr,dash,1,0);
			cairo_move_to(cr,x1,y1);
			cairo_line_to(cr,x2,y2);
			cairo_stroke(cr);
			cairo_restore(cr);
		}else{
			if(*(double*)com->data<0){
				double tmp=x1;
				x1=x2;
				x2=tmp;
				tmp=y1;
				y1=y2;
				y2=tmp;
			}
			cairo_move_to(cr,x1,y1);
			cairo_save(cr);
			cairo_translate(cr,(x1+x2)/2,(y1+y2)/2);
			cairo_scale(cr,unit,unit);
			cairo_rotate(cr,atan2(y2-y1,x2-x1));
			cairo_line_to(cr,-.05,0);
			cairo_move_to(cr,-.05,.25);
			cairo_line_to(cr,-.05,-.25);
			cairo_move_to(cr,.05,.15);
			cairo_line_to(cr,.05,-.15);
			cairo_move_to(cr,-.15,-.25);
			cairo_line_to(cr,-.25,-.25);
			cairo_move_to(cr,-.2,-.2);
			cairo_line_to(cr,-.2,-.3);
			cairo_move_to(cr,.05,0);
			cairo_restore(cr);
			cairo_line_to(cr,x2,y2);
			cairo_stroke(cr);
		}
		
		return;
	}
}
static gboolean draw_callback(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	guint width=gtk_widget_get_allocated_width(widget);
	guint height=gtk_widget_get_allocated_height(widget);
	double sw,sh,spacing;
	//PangoLayout* pn=gtk_widget_create_pango_layout(widget,"HELLO? IS THIS WORKING?(\u2126)");
	PangoContext* pc=gtk_widget_get_pango_context(widget);
	PangoLayout* pn=pango_layout_new(pc);
	sw=((double)width-2*gutter)/grid.width;
	sh=((double)height-2*gutter)/grid.height;
	spacing=MIN(sw,sh);
	cairo_set_source_rgb(cr,0,0,255);
//	cairo_arc(cr,mouseX,mouseY,5,0,2*G_PI);
	cairo_translate(cr,(double)width/2,(double)height/2);
	cairo_translate(cr,-(double)grid.width/2.0*spacing,-(double)grid.height/2.0*spacing);
	int i,j;
	cairo_set_source_rgb(cr,0,0,0);
	for(i=0;i<grid.map.ccount;i++)
	{
		Component* c=grid.map.components+i;
		int A=c->A;
		int B=c->B;
		draw_component(cr,pc,spacing,spacing*(A%(grid.width+1)),spacing*(A/(grid.width+1)),spacing*(B%(grid.width+1)),spacing*(B/(grid.width+1)),c);
	}
	cairo_set_source_rgb(cr,0,0,0);
	char buffer[20];
	for(i=0;i<=grid.width;i++)
	{
		for(j=0;j<=grid.height;j++)
		{
			sprintf(buffer,"%gV",grid.map.vertices[i+j*(grid.width+1)].voltage);
			pango_layout_set_text(pn,buffer,-1);
			int w,h;
			pango_layout_get_pixel_size(pn,&w,&h);
			cairo_arc(cr,i*spacing,j*spacing,w/2,0,2*G_PI);
			cairo_set_source_rgb(cr,1.0,1.0,1.0);
			cairo_fill_preserve(cr);
			cairo_set_source_rgb(cr,0.0,0.0,0.0);
			cairo_stroke(cr);
			cairo_move_to(cr,i*spacing-w/2,j*spacing-h/2);
			pango_cairo_update_layout(cr,pn);
			pango_cairo_show_layout(cr,pn);
			cairo_new_path(cr);
		}
	}
	//pango_cairo_show_layout(cr,pn);
return FALSE;
}
void calculate()
{
	int i;
	for(i=0;i<grid.map.ccount;i++){
		grid.map.components[i].current=0;
	}
	for(i=0;i<grid.map.vcount;i++){
		grid.map.vertices[i].voltage=0;
	}
	if(grid.map.ccount==0){
		return;
	}
	Circuit C;
	C.vertices=calloc(grid.map.ccount*2,sizeof(Vertex));
	if(C.vertices==NULL){
		//ERROR, HANDLE HERE
		return;
	}
	C.vcount=0;
	for(i=0;i<grid.map.ccount;i++)
	{
		int A=grid.map.components[i].A;
		int B=grid.map.components[i].B;
		printf("%i,%i\n",A,B);
		int j,k;
		for(j=0;j<C.vcount;j++){
			if(A==C.vertices[j].id){
				break;
			}
		}
		if(j==C.vcount){
			for(k=0;k<grid.map.vcount;k++){
				if(grid.map.vertices[k].id==A){
					printf("A%i\n",k);
					C.vertices[C.vcount++]=grid.map.vertices[k];
				}
			}
		}
		for(j=0;j<C.vcount;j++){
			if(B==C.vertices[j].id){
				break;
				printf("B==%i(%i)\n",C.vertices[j].id,j);
			}
		}
		printf("?:%i,%i\n",C.vcount,j);
		if(j==C.vcount){
			for(k=0;k<grid.map.vcount;k++){
				if(grid.map.vertices[k].id==B){
					printf("B%i\n",k);
					C.vertices[C.vcount++]=grid.map.vertices[k];
				}
			}
		}
	}
	C.ccount=grid.map.ccount;
	C.components=grid.map.components;
	printf("vcount: %i\nccount:%i\n",C.vcount,C.ccount);
	if(update_circuit(&C)<0){
		//error, handle here
		free(C.vertices);
		return;
	}
	for(i=0;i<C.vcount;i++){
		int j;
		for(j=0;j<grid.map.vcount;j++){
			if(grid.map.vertices[j].id==C.vertices[i].id){
				grid.map.vertices[j].voltage=C.vertices[i].voltage;
			}
		}
	}
	free(C.vertices);
}
void init_grid(int width,int height)
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
void add_component(Component c)
{
	int i;
	for(i=0;i<grid.map.ccount;i++){
		if(grid.map.components[i].A==c.A&&grid.map.components[i].B==c.B)remove_component(i);
	}

	grid.map.components[grid.map.ccount]=c;
	grid.map.ccount++;
}
void remove_component(int i)
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
	int A=MIN(grid.map.vertices[ia].id,grid.map.vertices[ib].id);
	int B=MAX(grid.map.vertices[ia].id,grid.map.vertices[ib].id);

	if(draw_state==PLACE_WIRE){
		Component c;
		c.type=WIRE;
		c.A=A;
		c.B=B;
		add_component(c);
	}
	if(draw_state==PLACE_RESISTOR){
		Component c;
		c.type=RESISTOR;
		c.A=A;
		c.B=B;
		c.data=calloc(1,sizeof(double));
		*(double*)c.data=10;
		add_component(c);
	}
	if(draw_state==PLACE_BATTERY){
		Component c;
		c.type=BATTERY;
		c.A=A;
		c.B=B;
		c.data=calloc(1,sizeof(double));
		*(double*)c.data=5;
		add_component(c);
	}if(draw_state==DELETE){
		for(i=0;i<grid.map.ccount;i++){
			if((grid.map.components[i].A==A)&&(grid.map.components[i].B==B)){
				remove_component(i);
				break;
			}
		}
	}
	calculate();
	gtk_widget_queue_draw_area(widget,0,0,width,height);
	return TRUE;
}
static void reset_grid()
{
}
static void init_buttons()
{

}
void toggle_callback(GtkToggleToolButton* widget,gpointer data)
{
	if(gtk_toggle_tool_button_get_active(widget)==FALSE)return FALSE;
	if(widget==gtk_builder_get_object(builder,"wirebutton"))draw_state=PLACE_WIRE;
	if(widget==gtk_builder_get_object(builder,"resistorbutton"))draw_state=PLACE_RESISTOR;
	if(widget==gtk_builder_get_object(builder,"batterybutton"))draw_state=PLACE_BATTERY;
	if(widget==gtk_builder_get_object(builder,"deletebutton"))draw_state=DELETE;
	if(widget==gtk_builder_get_object(builder,"editbutton"))draw_state=EDIT;
}
void calc_callback(GtkToolButton* widget,gpointer data)
{
	calculate();
}
void init_UI()
{
	init_grid(5,5);
	printf("beginning\n");
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder,"builder.ui",NULL);
	GtkWidget* area=(GtkWidget*)gtk_builder_get_object(builder,"circuitarea");
	gtk_widget_add_events(area,GDK_BUTTON_PRESS_MASK);
	g_signal_connect(G_OBJECT(area),"button-press-event",G_CALLBACK(press_callback),NULL);
	g_signal_connect(G_OBJECT(area),"draw",G_CALLBACK(draw_callback),NULL);
	GtkWidget* window=(GtkWidget*)gtk_builder_get_object(builder,"window");
	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);


	GtkWidget* button=gtk_builder_get_object(builder,"wirebutton");
	g_signal_connect(button,"toggled",toggle_callback,NULL);
	button=gtk_builder_get_object(builder,"resistorbutton");
	g_signal_connect(button,"toggled",toggle_callback,NULL);
	button=gtk_builder_get_object(builder,"batterybutton");
	g_signal_connect(button,"toggled",toggle_callback,NULL);
	button=gtk_builder_get_object(builder,"deletebutton");
	g_signal_connect(button,"toggled",toggle_callback,NULL);
	button=gtk_builder_get_object(builder,"editbutton");
	g_signal_connect(button,"toggled",toggle_callback,NULL);
	button=gtk_builder_get_object(builder,"calculate");
	g_signal_connect(button,"clicked",calc_callback,NULL);
	printf("done\n");//gtk_widget_show(window);
}
