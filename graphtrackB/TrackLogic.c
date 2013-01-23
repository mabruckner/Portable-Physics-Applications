#include "TrackLogic.h"
#include <math.h>

void advance(TrackData* track,float* x,float* vel,float in,float g)
{
	//warning! risk of segfault for certain values
	float time=0;
	//float dh=track->heights[current+1]-track->heights[current];
	//float va=(track->widths[current]*dh*g)/(track->widths[current]*track->widths[current]+dh*dh);
	while(time<in){
		int current,i;
		float sum=0.0;
		for(i=0;i<track->num-1&&sum<*x;i++)sum+=track->widths[i];
		current=--i;
		if(sum==*x&&*vel>0.0){current+=1;sum+=track->widths[current];}
		if(sum==*x&&*vel==0.0)return;
		float dh=track->heights[current+1]-track->heights[current];
		float va=(track->widths[current]*dh*g)/(track->widths[current]*track->widths[current]+dh*dh);
		float et=in-time;
		float test=(-*vel-(float)sqrt((double)((*vel)*(*vel)-2*va*(*x-sum+track->widths[current]))))/va;
		et=test<et&&test>0 ? test : et;
		//test=(-*vel+(float)sqrt((double)((*vel)*(*vel)-2*va*(*x-sum+track->widths[current]))))/va;
		test=-2*(*x-sum+track->widths[current])/(*vel+(float)sqrt((double)((*vel)*(*vel)-2*va*(*x-sum+track->widths[current]))));
		et=test<et&&test>0 ? test : et;
		test=(-*vel-(float)sqrt((double)((*vel)*(*vel)-2*va*(*x-sum))))/va;
		et=test<et&&test>0 ? test : et;
		//test=(-*vel+(float)sqrt((double)((*vel)*(*vel)-2*va*(*x-sum))))/va;
		test=-2*(*x-sum)/(*vel+(float)sqrt((double)((*vel)*(*vel)-2*va*(*x-sum))));
		et=test<et&&test>0 ? test : et;
		*x+=.5*va*et*et+(*vel)*et;
		*vel+=va*et;
		time+=et;
	}
}
