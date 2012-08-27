spring: spring.cpp
	g++ -Wall -g spring.cpp `fltk-config --use-gl --cxxflags --ldflags` -o spring

dash: dash.o Spring_Window.o Spring_Container.o Spring_Calc.o Line_Chart.o
	g++ -Wall -g $^ `fltk-config --use-gl --cxxflags --ldflags` -o dash

dash.o: dash.cpp Spring_Container.h
	g++ -Wall -g `fltk-config --use-gl --cxxflags --ldflags` -c dash.cpp 

Spring_Container.o: Spring_Container.cpp Spring_Container.h Spring_Window.h Spring_Calc.h Line_Chart.h
	g++ -Wall -g `fltk-config --use-gl --cxxflags --ldflags` -c $<

Spring_Window.o: Spring_Window.cpp Spring_Window.h
	g++ -Wall -g `fltk-config --use-gl --cxxflags --ldflags` -c $<

Spring_Calc.o: Spring_Calc.cpp Spring_Calc.h
	g++ -Wall -g -c $<

Line_Chart.o: Line_Chart.cpp Line_Chart.h
	g++ -Wall -g `fltk-config --use-gl --cxxflags --ldflags` -c $<
