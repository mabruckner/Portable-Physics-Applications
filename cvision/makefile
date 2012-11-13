CircuitVision: CircuitVision.o Circuit.o
	gcc -Wall -g $^ -lgsl -lgslcblas -lm -o $@

CircuitVision.o: CircuitVision.c Circuit.h
	gcc -Wall -g -c $< -o $@

Circuit.o: Circuit.c Circuit.h CircuitFunc.h
	gcc -Wall -g -c $< -o $@
