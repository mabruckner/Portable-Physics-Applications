CircuitVision: CircuitVision.o Circuit.o UI.o Dialogs.o Viewer.o
	gcc -Wall -g $^ -lgsl -lgslcblas -lm `pkg-config --libs gtk+-3.0 gthread-2.0` -lGL -lglut -lGLEW -o $@

CircuitVision.o: CircuitVision.c Circuit.h
	gcc -Wall -g -c $< `pkg-config --cflags gtk+-3.0 gthread-2.0` -o $@

Circuit.o: Circuit.c Circuit.h CircuitFunc.h
	gcc -Wall -g -c $< -o $@
UI.o: UI.c UI.h UIFunc.h
	gcc -Wall -g -c $< `pkg-config --cflags gtk+-3.0` -o $@

Dialogs.o: Dialogs.c Dialogs.h UIFunc.h
	gcc -Wall -g -c $< `pkg-config --cflags gtk+-3.0` -o $@

Viewer.o: Viewer.c Viewer.h Render.c
	gcc -Wall -g -c $< `pkg-config --cflags gtk+-3.0` -lGL -lglut -o $@

clean:
	rm *.o
	rm CircuitVision
