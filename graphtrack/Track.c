#include "Track.h"

#include <math.h>
#include <stdlib.h>

State* calc(Track* track,float interval,int num)
{
	State* out=malloc(sizeof(State)*num);
	int i;
	State cstate=track->init;
	float ctime;
	for(i=0;i<num;i++){
		
		out[i]=cstate;
	}
	return out;
}
