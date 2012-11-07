#include "Track.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static int quadratic(float A,float B,float C,float Y,float* sol)
{
	if((B*B-4*A*(C-Y))<0)return 0;
	
	float n=sqrt(B*B-4*A*(C-Y));
	if(n==0.0){
		*sol=-B/(2*A);
		return 1;
	}
	float sa=(-B-n)/(2*A);
	float sb=(-B+n)/(2*A);
	if(sa>0)
	{
		*sol=sa;
	}else{
		*sol=sb;
	}
	return 2;
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
			float delta=gtime-ctime;
			int place=(int)(cstate.pos/track->spaces);
			if(cstate.pos/track->spaces==place)place--;
			if(place<0||place>track->nheights-1){ctime=gtime;break;}
			float acc=track->g*track->spaces/(track->heights[place]-track->heights[place+1]);
			printf("%f:%f\n",ctime,acc);
			float a=acc/2.0;
			float b=cstate.vel;
			float c=cstate.pos;
			float sola=0.0;
			float solb=0.0;
			float sol=-1.0;
			int top=quadratic(a,b,c,(place+1)*track->spaces,&sola);
			int bottom=quadratic(a,b,c,place*track->spaces,&solb);
			if(top>0&&sola>0&&sola<delta)sol=sola;
			if(bottom>0&&solb>0&&solb<delta&&solb<sola)sol=solb;
			if(sol>0){
				cstate.pos+=a*sol*sol+b*sol;
				cstate.vel+=a*sol*2;
				ctime+=delta;
				continue;
			}
			cstate.pos+=a*delta*delta+b*delta;
			cstate.vel+=a*delta*2;
			ctime+=delta;
		}
		
		out[i]=cstate;
	}
	return out;
}
