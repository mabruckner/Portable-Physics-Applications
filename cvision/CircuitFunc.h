#include <gsl/gsl_linalg.h>
#include "Circuit.h"
void to_matrix(Circuit * c,gsl_matrix** A,gsl_vector** b);
void to_circuit(gsl_vector* b,Circuit * c);
void print_matrix(gsl_matrix* m);
void print_vector(gsl_vector* v);
