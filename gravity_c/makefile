gtk: gtktest.o Point.o
	gcc -Wall -g $^ `pkg-config --cflags --libs gtk+-3.0` -o $@ 

gtktest.o: gtktest.c Point.h
	gcc -Wall -g -c $< `pkg-config --cflags --libs gtk+-3.0` -o $@ 

Point.o: Point.c Point.h
	gcc -Wall -g -c $< -o $@ 

clean:
	rm -f *.o
	rm gtk
