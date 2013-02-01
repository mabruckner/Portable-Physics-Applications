#ifndef TRACKLOGIC_H
#define TRACKLOGIC_H

#define USE_VEL_MAG

typedef struct TrackData
{
	int num;
	float* widths;//num-1 entries
	float* heights;//num entries
	float g;
} TrackData;

typedef struct MotionData
{
	float pos;
	float vel;
	float acc;
} MotionData;
void advance(TrackData* track,MotionData* data,float in);

#endif
