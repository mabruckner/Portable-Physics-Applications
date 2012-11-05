#include "Track.h"

#include <stdio.h>

int main(int argv, char** argc)
{
	Track track;
	float heights[5]={10.0,1.0,5.0,4.0,10.0};
	track.heights=heights;
	track.nheights=5;
	track.spaces=1.0;
	State init;
	init.pos=3.0;
	init.vel=-1.0;
	track.init=init;
	track.g=1.0;
	State * graph=calc(&track,1.0,10);
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<graph[i].pos;j++){
			printf("-");
		}
		printf("*\n");
	}
	return 0;
}
