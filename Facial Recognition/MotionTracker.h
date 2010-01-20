/**
$ID$

Copyright (c) 2010 by Brian Blonski
 */
#ifndef _MOTION_TRACKER_H
#define _MOTION_TRACKER_H

#include "OpenCVIncludes.h"


/**
\brief
MotionTracker tracks the motion of a face.

MotionTracker finds the difference between two sets of CvPoints2D32f points.
The detect method is the main method of detecting motion.  It's parameter is a
set of points from the LKTracker using getPoints().


\remarks
Write remarks for MotionTracker here.

\see
LKTracker | LKTracker::getPoints()
 */
class MotionTracker
{
private:
	typedef enum HeadMotion { LEFT, RIGHT, UP, DOWN, CENTER } HeadMotion;
	CvPoint2D32f** prevPoints;
	CvPoint2D32f** nextPoints;
	HeadMotion motion;
public:
	MotionTracker(void);
	~MotionTracker(void);
	HeadMotion detect(CvPoint2D32f** points, int);
	HeadMotion getMotion();
};
#endif
