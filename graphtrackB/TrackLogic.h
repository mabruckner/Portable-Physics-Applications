#ifndef TRACKLOGIC_H
#define TRACKLOGIC_H

typedef struct TrackData
{
	int num;
	float* widths;//num-1 entries
	float* heights;//num entries
} TrackData;
void advance(TrackData* track,float* x,float* vel,float in,float g);

#endif
