#include <stdio.h>
#include <gtk/gtk.h>

#include "UI.h"
#include "Circuit.h"


/*gsl_vector * solve(gsl_matrix* A,gsl_vector* b)
{
	printf("A =\n");
	print_matrix(A);
	printf("\nb =\n");
	gsl_vector_fprintf(stdout,b,"[%g]");
	gsl_permutation * p=gsl_permutation_alloc(b->size);
	int s;
	gsl_linalg_LU_decomp(A,p,&s);
	print_matrix(A);
	double det=gsl_linalg_LU_det(A,s);
	if(det==0.0){
		printf("ERROR, NON-TRIVIAL SOLUTION\n");
		gsl_permutation_free(p);
		return NULL;
	}
	gsl_vector * x=gsl_vector_alloc(b->size);
	gsl_linalg_LU_solve(A,p,b,x);
	gsl_permutation_free(p);
	return x;
}*/

int main(int argc,char** argv)
{
	GtkWidget *window;
	gtk_init(&argc,&argv);
/*	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_widget_show(window);*/
	init_UI();
	gtk_main();
	/*printf("ITS... ALIVE!!!\n");
	int i;
	gsl_vector * v=gsl_vector_alloc(3);
	for(i=0;i<3;i++){
		gsl_vector_set(v,i,1.23+i);
	}
	for(i=0;i<3;i++){
		printf("v_%d = %g\n",i,gsl_vector_get(v,i));
	}
	gsl_vector_free(v);
	double a_data[]=
{
0.18,0.60,0.57,0.96,
0.41,0.24,0.99,0.58,
0.14,0.30,0.97,0.66,
0.51,0.13,0.19,0.85
};
	double b_data[]={1.0,2.0,3.0,4.0};

	gsl_matrix_view m=gsl_matrix_view_array(a_data,4,4);
	gsl_vector_view b=gsl_vector_view_array(b_data,4);
	gsl_vector * x=solve(&m.matrix,&b.vector);*///gsl_vector_alloc(4);
/*	int s;
	gsl_permutation * p=gsl_permutation_alloc(4);
	gsl_linalg_LU_decomp(&m.matrix,p,&s);
	printf("WELL?\n");
	double det=gsl_linalg_LU_det(&m.matrix,1);
	printf("DETERMINANT:%g\n",det);
	if(det==0.0){
		printf("WARNING!!! NO SOLUTION\n");
	}else{	
		gsl_linalg_LU_solve(&m.matrix,p,&b.vector,x);
		printf("X = \n");
		gsl_vector_fprintf(stdout,x,"%g");
	}
	gsl_permutation_free(p);*/
	double data[]={5,10};
	Component com[4];
	Vertex vert[4];
	vert[0].id=0;
	vert[1].id=1;
	vert[2].id=2;
	vert[3].id=3;
	com[0].A=0;
	com[0].B=1;
	com[1].A=1;
	com[1].B=2;
	com[2].A=2;
	com[2].B=3;
	com[3].A=3;
	com[3].B=0;
	com[0].type=BATTERY;
	com[0].data=data;
	com[1].type=WIRE;
	com[1].data=NULL;
	com[2].type=RESISTOR;
	com[2].data=data+1;
	com[3].type=WIRE;
	Circuit c;
	c.components=com;
	c.ccount=4;
	c.vertices=vert;
	c.vcount=4;
	update_circuit(&c);
	return 0;
}
