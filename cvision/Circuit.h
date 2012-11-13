#ifndef CIRCUIT_H
#define CIRCUIT_H
//current is from A to B
#define WIRE 0
#define BATTERY 1
#define RESISTOR 2
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
int update_circuit(Circuit * c);

#endif
