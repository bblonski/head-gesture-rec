#ifndef _MOTION_TRACKER_H
#define _MOTION_TRACKER_H

#include "OpenCVIncludes.h"

class MotionTracker
{
private:
	CvPoint2D32f* prevPoints[2];
	CvPoint2D32f* nextPoints[2];
public:
	MotionTracker(void);
	~MotionTracker(void);
	void detect(CvPoint2D32f**, int);
};
#endif
