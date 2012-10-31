make: gtk gravity

gtk: gtktest.o Point.o
	gcc -Wall -g $^ `pkg-config --cflags --libs gtk+-3.0` -o $@ 

gravity: gravity.o Algorithms.o Point.o
	gcc -Wall -g  $^ -o $@ -lm

gravity.o: gravity.c Algorithms.h Point.h
	gcc -Wall -g  -c $< -o $@ -lm

Algorithms.o: Algorithms.c Algorithms.h Point.h
	gcc -Wall -g -c $< -o $@ 

gtktest.o: gtktest.c Point.h
	gcc -Wall -g -c $< `pkg-config --cflags --libs gtk+-3.0` -o $@ 

Point.o: Point.c Point.h
	gcc -Wall -g -c $< -o $@ 

clean:
	rm -f *.o
	rm gtk
	rm gravity
