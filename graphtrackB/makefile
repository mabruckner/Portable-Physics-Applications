graphtrack: main.o TrackLogic.o TrackRender.o PlotRender.o
	gcc -Wall -g $^ `pkg-config --libs gtk+-3.0` -lm -o $@

main.o: main.c TrackLogic.h TrackRender.h PlotRender.h
	gcc -Wall -g -c $< `pkg-config --cflags gtk+-3.0` -o $@

TrackLogic.o: TrackLogic.c TrackLogic.h
	gcc -Wall -g -c $< -o $@

TrackRender.o: TrackRender.c TrackRender.h TrackLogic.h
	gcc -Wall -g -c $< `pkg-config --cflags gtk+-3.0` -o $@

PlotRender.o: PlotRender.c PlotRender.h TrackLogic.h
	gcc -Wall -g -c $< `pkg-config --cflags gtk+-3.0` -o $@
