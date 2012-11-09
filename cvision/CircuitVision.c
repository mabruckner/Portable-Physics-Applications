#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>

#include "Circuit.h"

gsl_vector * solve(gsl_matrix* A,gsl_vector* b)
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
}

int main(int argc,char** argv)
{
	printf("ITS... ALIVE!!!\n");
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
	gsl_vector * x=solve(&m.matrix,&b.vector);//gsl_vector_alloc(4);
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
	gsl_matrix* A;
	gsl_vector* B;
	gsl_vector_fprintf(stdout,x,"%g");
	gsl_vector_free(x);
	Component com[2];
	Vertex vert[2];
	vert[0].id=0;
	vert[1].id=1;
	com[0].A=0;
	com[0].B=1;
	com[1].A=1;
	com[1].B=0;
	Circuit c;
	c.components=com;
	c.ccount=2;
	c.vertices=vert;
	c.vcount=2;
	to_matrix(&c,&A,&B);
	print_matrix(A);
	gsl_matrix_free(A);
	gsl_vector_free(B);
	return 0;
}
