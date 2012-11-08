#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>

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
0.0,0.0,0.0,12.0
};
	double b_data[]={1.0,2.0,3.0,4.0};

	gsl_matrix_view m=gsl_matrix_view_array(a_data,4,4);
	gsl_vector_view b=gsl_vector_view_array(b_data,4);
	gsl_vector * x=gsl_vector_alloc(4);
	int s;
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
	gsl_permutation_free(p);
	gsl_vector_free(x);
	return 0;
}
