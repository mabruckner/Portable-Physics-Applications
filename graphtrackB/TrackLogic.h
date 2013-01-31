#ifndef TRACKLOGIC_H
#define TRACKLOGIC_H

typedef struct TrackData
{
	int num;
	float* widths;//num-1 entries
	float* heights;//num entries
} TrackData;

typedef struct MotionData
{
	float x;
	float vel;
	float g;
} MotionData;
void advance(TrackData* track,MotionData* data,float in);

#endif
