#include <stdio.h>

#include "Circuit.h"
#include "CircuitFunc.h"

void to_matrix(Circuit* c,gsl_matrix** A_ptr,gsl_vector** b_ptr)
{
	int w=c->ccount+c->vcount;
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
	}//printf("LKJHDSLFKJSHD\n");
	gsl_matrix_view voltage_view=gsl_matrix_submatrix(A,c->vcount-1,c->ccount,c->ccount,c->vcount);
	gsl_matrix* voltage=&voltage_view.matrix;
	for(i=0;i<c->ccount;i++){
		for(j=0;j<c->vcount;j++){
			if(c->vertices[j].id==c->components[i].A)gsl_matrix_set(voltage,i,j,-1);
			if(c->vertices[j].id==c->components[i].B)gsl_matrix_set(voltage,i,j,1);
		}
		if(c->components[i].type==RESISTOR)
		{
			gsl_matrix_set(A,c->vcount+i-1,i,5/*resistance here*/);
		}
		if(c->components[i].type==BATTERY)
		{
			gsl_vector_set(b,c->vcount+i-1,10);
		}
	}//printf("KHLKSJDHFHGLKJ\n");
	gsl_matrix_set(A,w-1,w-1,1);
	print_matrix(voltage);
	print_vector(b);
}
void print_vector(gsl_vector* v)
{
	int i;
	for(i=0;i<v->size;i++)
	{
		printf("[%6.3g]\n",gsl_vector_get(v,i));
	}
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
void to_circuit(gsl_vector* b,Circuit* c)
{
	int i;
	for(i=0;i<c->ccount;i++)
	{
		c->components[i].current=gsl_vector_get(b,i);
	}
	for(i=0;i<c->vcount;i++)
	{
		c->vertices[i].voltage=gsl_vector_get(b,i+c->ccount);
	}
}
int update_circuit(Circuit* c)
{
	gsl_matrix* A;
	gsl_vector* b;
	to_matrix(c,&A,&b);
	int i,j;
	for(i=0;i<A->size1;i++){
		printf("[ ");
		for(j=0;j<A->size2;j++)
		{
			printf("%6.3g ",gsl_matrix_get(A,i,j));
		}
		printf("] [ %6.3g ]\n",gsl_vector_get(b,i));
	}
	gsl_permutation * p=gsl_permutation_alloc(b->size);
	int s;
	gsl_linalg_LU_decomp(A,p,&s);
	double det=gsl_linalg_LU_det(A,s);
	printf("\ndeterminant is %g\n",det);
	if(det==0.0){
		printf("ERROR, NON-TRIVIAL SOLUTION\nFREEING MEMORY AND HALTING COMPUTATION\n");
		gsl_vector_free(b);
		gsl_matrix_free(A);
		gsl_permutation_free(p);
		return -1;
	}
	gsl_vector* x =gsl_vector_alloc(b->size);
	gsl_linalg_LU_solve(A,p,b,x);
	printf("\nthe solution is:\n");
	print_vector(x);
	to_circuit(x,c);
	gsl_vector_free(x);
	gsl_matrix_free(A);
	gsl_vector_free(b);
	gsl_permutation_free(p);
	return 0;
}
