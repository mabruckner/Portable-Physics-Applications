#include <stdio.h>
#include <gtk/gtk.h>
#include <GL/freeglut.h>

#include "UI.h"
#include "Circuit.h"
#include "Viewer.h"

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
	//GtkWidget *window;

	gdk_threads_init();

	gtk_init(&argc,&argv);
/*	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_widget_show(window);*/
//	glutInit(&argc,argv);
//	g_thread_new("Viewer",init_Viewer,NULL);
	gdk_threads_enter();
	glutInit(&argc,argv);
	g_thread_new("Viewer",(gpointer)init_Viewer,NULL);
	printf("THREAD INIT\n");
	init_UI();
	gtk_main();
	gdk_threads_leave();
	return 0;
}
