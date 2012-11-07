#include "Track.h"

#include <math.h>
#include <stdlib.h>

static int quadratic(float A,float B,float C,float Y,float* sol)
{
	if((B*B-4*A*(C-Y))<0)return 0;
	
	float n=sqrt(B*B-4*A*(C-Y));
	if(n==0.0){
		*sol=-B/(2*A);
		return 1;
	}
}

State* calc(Track* track,float interval,int num)
{
	State* out=malloc(sizeof(State)*num);
	int i;
	State cstate=track->init;
	float ctime=0.0;
	for(i=0;i<num;i++){
		float gtime=i*interval;
		while(ctime!=gtime){
			int place=(int)(cstate.pos/track->spaces);
			if(place<0||place>track->nheights-1){ctime=gtime;break;}
			float acc=track->g*track->spaces/(track->heights[place]-track->heights[place+1]);
			float a=acc/2.0;
			float b=cstate.vel;
			float c=cstate.pos;
			cstate.pos+=a*interval*interval+b*interval;
			cstate.vel+=a*interval*2;
			ctime+=interval;
		}
		
		out[i]=cstate;
	}
	return out;
}
