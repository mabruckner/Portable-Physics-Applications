CircuitVision: CircuitVision.o Circuit.o UI.o
	gcc -Wall -g $^ -lgsl -lgslcblas -lm `pkg-config --libs gtk+-3.0` -o $@

CircuitVision.o: CircuitVision.c Circuit.h
	gcc -Wall -g -c $< `pkg-config --cflags gtk+-3.0` -o $@

Circuit.o: Circuit.c Circuit.h CircuitFunc.h
	gcc -Wall -g -c $< -o $@
UI.o: UI.c UI.h
	gcc -Wall -g -c $< `pkg-config --cflags gtk+-3.0` -o $@
