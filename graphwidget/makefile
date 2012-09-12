test:graphtest.o Graph.o
	g++ -Wall -g $^ `fltk-config --use-gl --cxxflags --ldflags` -o $@

graptest.o: graphtest.cpp
	g++ -Wall -g -c $< `fltk-config --use-gl --cxxflags --ldflags` -o $@

Graph.o: Graph.cpp Graph.h
	g++ -Wall -g -c $< `fltk-config --use-gl --cxxflags --ldflags` -o $@
