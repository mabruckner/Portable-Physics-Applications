#ifndef TRACKFILE_H
#define TRACKFILE_H

#include "TrackLogic.h"

void loadTrack(TrackData* track,MotionData* pos,const char* file);
void saveTrack(TrackData* track,MotionData* pos,const char* file);

#endif
