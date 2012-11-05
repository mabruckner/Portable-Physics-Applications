GraphTrack: GraphTrack.o Track.o
	gcc -Wall -g $^ -o $@

GraphTrack.o: GraphTrack.c Track.h
	gcc -Wall -g -c $< -o $@

Track.o: Track.c Track.h
	gcc -Wall -g -c $< -o $@
