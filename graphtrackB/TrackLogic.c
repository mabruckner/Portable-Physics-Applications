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
		if(sum==*x){
			if(*vel>0.0){
				current+=1;
				sum+=track->widths[current];
				float l1=sqrt(track->widths[current-1]*track->widths[current-1]+(track->heights[current-1]-track->heights[current])*(track->heights[current-1]-track->heights[current]));
				float l2=sqrt(track->widths[current]*track->widths[current]+(track->heights[current+1]-track->heights[current])*(track->heights[current+1]-track->heights[current]));
				float num=(l1*track->widths[current])/(l2*track->widths[current-1]);
				*vel*=num;//sqrt(track->widths[current-1]*track->widths[current-1]+(track->heights[current-1]-track->heights[current])*(track->heights[current-1]-track->heights[current]))*track->widths[current]/(sqrt(track->widths[current]*track->widths[current]+(track->heights[current+1]-track->heights[current])*(track->heights[current+1]-track->heights[current]))*track->widths[current]);
				printf("\t%g: %g,%g\n",num,l1,l2);
			}
			if(*vel==0.0)return;
			if(*vel<0.0){//ERRORS BE HERE
				*vel*=sqrt(track->widths[current]*track->widths[current]+(track->heights[current]-track->heights[current+1])*(track->heights[current]-track->heights[current+1]))*track->widths[current]/(sqrt(track->widths[current+1]*track->widths[current+1]+(track->heights[current+1]-track->heights[current+2])*(track->heights[current+1]-track->heights[current+2]))*track->widths[current+1]);
				printf("\t%g\n",sqrt(track->widths[current]*track->widths[current]+(track->heights[current]-track->heights[current+1])*(track->heights[current]-track->heights[current+1]))*track->widths[current]/(sqrt(track->widths[current+1]*track->widths[current+1]+(track->heights[current+1]-track->heights[current+2])*(track->heights[current+1]-track->heights[current+2]))*track->widths[current+1]));
			}
		}
		//if(sum==*x&&*vel>0.0){current+=1;sum+=track->widths[current];}
		//if(sum==*x&&*vel==0.0)return;
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
