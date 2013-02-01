#include "TrackLogic.h"
#include <math.h>

void advance(TrackData* track,MotionData* pos,float in)
{
	//warning! risk of segfault for certain values
	float time=0;
	//float dh=track->heights[current+1]-track->heights[current];
	//float va=(track->widths[current]*dh*g)/(track->widths[current]*track->widths[current]+dh*dh);
	while(time<in){
		int current,i;
		float sum=0.0;
		for(i=0;i<track->num-1&&sum<pos->pos;i++)sum+=track->widths[i];
		current=--i;
		if(sum==pos->pos){
			if(pos->vel>0.0){
				current+=1;
				sum+=track->widths[current];
#ifndef USE_VEL_MAG
				float l1=sqrt(track->widths[current-1]*track->widths[current-1]+(track->heights[current-1]-track->heights[current])*(track->heights[current-1]-track->heights[current]));
				float l2=sqrt(track->widths[current]*track->widths[current]+(track->heights[current+1]-track->heights[current])*(track->heights[current+1]-track->heights[current]));
				float num=(l1*track->widths[current])/(l2*track->widths[current-1]);
				pos->vel*=num;//sqrt(track->widths[current-1]*track->widths[current-1]+(track->heights[current-1]-track->heights[current])*(track->heights[current-1]-track->heights[current]))*track->widths[current]/(sqrt(track->widths[current]*track->widths[current]+(track->heights[current+1]-track->heights[current])*(track->heights[current+1]-track->heights[current]))*track->widths[current]);
				printf("\t%g: %g,%g\n",num,l1,l2);
#endif
			}
			if(pos->vel==0.0)return;
#ifndef USE_VEL_MAG
			if(pos->vel<0.0){//ERRORS BE HERE
				float l1=sqrt(track->widths[current+1]*track->widths[current+1]+(track->heights[current+1]-track->heights[current+2])*(track->heights[current+1]-track->heights[current+2]));
				float l2=sqrt(track->widths[current]*track->widths[current]+(track->heights[current+1]-track->heights[current])*(track->heights[current+1]-track->heights[current]));
				float num=(l1*track->widths[current])/(l2*track->widths[current+1]);
				pos->vel*=num;
				printf("\t%g: %g,%g\n",num,l1,l2);
			}
#endif
		}
		//if(sum==*x&&*vel>0.0){current+=1;sum+=track->widths[current];}
		//if(sum==*x&&*vel==0.0)return;
		float dh=track->heights[current+1]-track->heights[current];
		float va=(track->widths[current]*dh*track->g)/(track->widths[current]*track->widths[current]+dh*dh);
		float et=in-time;
#ifndef USE_VEL_MAG
		float vel=pos->vel;
#else
		float vel=pos->vel*track->widths[current]/sqrt(track->widths[current]*track->widths[current]+dh*dh);
		float a=(track->g*dh)/sqrt(track->widths[current]*track->widths[current]+dh*dh);
#endif
		float np=pos->pos+.5*va*et*et+(vel)*et;
		float test=(-vel-(float)sqrt((double)((vel)*(vel)-2*va*(pos->pos-sum+track->widths[current]))))/va;
		if(test<et&&test>0){
			et=test;
			np=sum-track->widths[current];
		}
		//et=test<et&&test>0 ? test : et;
		//test=(-*vel+(float)sqrt((double)((*vel)*(*vel)-2*va*(*x-sum+track->widths[current]))))/va;
		test=-2*(pos->pos-sum+track->widths[current])/(vel+(float)sqrt((double)((vel)*(vel)-2*va*(pos->pos-sum+track->widths[current]))));
		if(test<et&&test>0){
			et=test;
			np=sum-track->widths[current];
		}
		//et=test<et&&test>0 ? test : et;
		test=(-vel-(float)sqrt((double)((vel)*(vel)-2*va*(pos->pos-sum))))/va;
		if(test<et&&test>0){
			et=test;
			np=sum;
		}
		//et=test<et&&test>0 ? test : et;
		//test=(-*vel+(float)sqrt((double)((*vel)*(*vel)-2*va*(*x-sum))))/va;
		test=-2*(pos->pos-sum)/(vel+(float)sqrt((double)((vel)*(vel)-2*va*(pos->pos-sum))));
		if(test<et&&test>0){
			et=test;
			np=sum;
		}
		//et=test<et&&test>0 ? test : et;
		//*x+=.5*va*et*et+(*vel)*et;
		pos->pos=np;
		vel+=va*et;
#ifndef USE_VEL_MAG
		pos->vel=vel;
#else
		pos->vel+=a*et;//vel*sqrt(track->widths[current]*track->widths[current]+dh*dh)/track->widths[current];
		pos->acc=a;
#endif
		time+=et;
	}
}
