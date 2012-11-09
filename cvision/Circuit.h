//current is from A to B
#include <gsl/gsl_linalg.h>

typedef struct
{
	char type;
	int A,B;
	void* data;
	char* name;
	double current;
} Component;
typedef struct
{
	int id;
	char* name;
	double voltage;
} Vertex;
typedef struct
{
	Component* components;
	Vertex* vertices;
	int ccount;
	int vcount;
} Circuit;
void to_matrix(Circuit * c,gsl_matrix** A,gsl_vector** b);
void print_matrix(gsl_matrix* m);
