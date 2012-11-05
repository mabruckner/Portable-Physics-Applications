#ifndef TRACK_H
#define TRACK_H

struct State
{
	float pos;
	float vel;
};
typedef struct State State;
struct Track
{
	float* heights;
	int nheights;
	float spaces;
	State init;
	float g;
};
typedef struct Track Track;
State* calc(Track* track,float interval,int num);

#endif
