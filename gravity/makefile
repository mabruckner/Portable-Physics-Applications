gravity: gravity.o Algorithms.o Point.o
	g++ -Wall -g $^ -lGL -lglut -lGLEW -o $@
	./gravity

gtk: gtktest.c Point.c
	gcc -Wall -g $^ `pkg-config --cflags --libs gtk+-3.0` -o $@ 

gravity.o: gravity.cpp Point.h Algorithms.h
	g++ -Wall -g -c $< -lGL -lglut -lGLEW -o $@

Algorithms.o: Algorithms.cpp Point.h Algorithms.h
	g++ -Wall -g -c $< -o $@

Point.o: Point.cpp Point.h
	g++ -Wall -g -c $< -o $@

clean:
	rm *.o
	rm gravity
