gravity: gravity.o Algorithms.o
	g++ -Wall -g $^ -lGL -lglut -lGLEW -o $@
	./gravity

gravity.o: gravity.cpp Point.h Algorithms.h
	g++ -Wall -g -c $< -lGL -lglut -lGLEW -o $@

Algorithms.o: Algorithms.cpp Point.h Algorithms.h
	g++ -Wall -g -c $< -o $@

clean:
	rm *.o
	rm gravity
