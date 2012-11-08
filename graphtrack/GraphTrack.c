#include "Track.h"

#include <stdio.h>

int main(int argv, char** argc)
{
	Track track;
	float heights[5]={0.0,6.0,4.0,6.0,12.0};
	track.heights=heights;
	track.nheights=5;
	track.spaces=1.0;
	State init;
	init.pos=2.5;
	init.vel=0.0;
	track.init=init;
	track.g=10.0;
	State * graph=calc(&track,0x0.1p0,50);
	int i,j;
	printf("|-------------------|-------------------|-------------------|-------------------|\n");
	for(i=0;i<50;i++){
		for(j=0;j<graph[i].pos*20;j++){
			
			printf("-");
		}
		printf("*\n");
	}
	printf("\n");
	for(i=0;i<50;i++){
		for(j=-100;j<graph[i].vel*20;j++){
			printf("-");
		}
		printf("*\n");
	}
	return 0;
}
