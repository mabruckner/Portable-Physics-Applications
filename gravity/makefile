gravity: gravity.o Algorithms.o
	g++ -Wall -g $^ -lGL -lglut -o $@

gravity.o: gravity.cpp Point.h Algorithms.h
	g++ -Wall -g -c $< -lGL -lglut -o $@

Algorithms.o: Algorithms.cpp Point.h Algorithms.h
	g++ -Wall -g -c $< -o $@

clean:
	rm *.o
	rm gravity
