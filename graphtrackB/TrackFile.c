#include "TrackFile.h"
#include <stdio.h>
void loadTrack(TrackData* track,MotionData* pos,const char* file)
{
	FILE* f=fopen(file,"r");
	fscanf(f,"%g,%g",&(pos->pos),&(pos->vel));
	fscanf(f,"%g\n%i",&(track->g),&(track->num));
	int i;
	fclose(f);
}
void saveTrack(TrackData* track,MotionData* pos,const char* file)
{
	FILE* f=fopen(file,"w");
	fprintf(f,"%g,%g\n",pos->pos,pos->vel);
	fprintf(f,"%g\n",track->g);
	fprintf(f,"%i\n",track->num);
	int i;
	for(i=0;i<track->num-1;i++){
		fprintf(f,"%g\n",track->widths[i]);
	}
	for(i=0;i<track->num;i++){
		fprintf(f,"%g\n",track->heights[i]);
	}
	fclose(f);
}
