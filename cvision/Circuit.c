#include <stdio.h>

#include "Circuit.h"

void to_matrix(Circuit* c,gsl_matrix** A_ptr,gsl_vector** b_ptr)
{
	int w=c->ccount*2;
	(*A_ptr)=gsl_matrix_calloc(w,w);
	(*b_ptr)=gsl_vector_calloc(w);
	gsl_matrix * A=*A_ptr;
	gsl_vector * b=*b_ptr;
	if(A==NULL||b==NULL){
		printf("ERROR, UNABLE TO ALLOCATE MEMORY FOR MATRIX CONVERSION\n");
		A=NULL;
		b=NULL;
		return;
	}
	int i;
	int j;
	for(i=0;i<c->ccount;i++)
	{
		Component* edge=c->components+i;
		for(j=0;j<c->vcount-1;j++){
			if(edge->A==c->vertices[j].id){
				gsl_matrix_set(A,j,i,-1.0);
			}
			if(edge->B==c->vertices[j].id){
				gsl_matrix_set(A,j,i,1.0);
			}
		}
	}
	gsl_matrix_view loops_view=gsl_matrix_submatrix(A,c->ccount,c->vcount,c->ccount-c->vcount+1,c->ccount);
	gsl_matrix* loops=&loops_view.matrix;
	for(i=0;i<loops->size1;i++){
		for(j=0;j<loops->size2;j++)
		{
			int k;
		}
	}
	print_matrix(loops);
}
void print_matrix(gsl_matrix* m)
{
	int i,j;
	for(i=0;i<m->size1;i++)
	{
		printf("[ ");
		for(j=0;j<m->size2;j++)
		{
			printf("%6.3g ",gsl_matrix_get(m,i,j));
		}
		printf("]\n");
	}
}
