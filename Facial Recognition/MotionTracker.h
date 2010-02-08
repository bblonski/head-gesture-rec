// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _MOTION_TRACKER_H
#define _MOTION_TRACKER_H

#include "OpenCVIncludes.h"

/**
\brief
MotionTracker tracks the motion of a face.

MotionTracker finds the difference between two sets of CvPoints2D32f points.
The \ref detect method is the main method of detecting motion.  It's parameter is a
set of points from the LKTracker using getPoints().

\see
LKTracker | LKTracker::getPoints()
 */
class MotionTracker
{
private:
    const double X_THRESHOLD;
    const double Y_THRESHOLD;
    int left, right, up, down, center_x, center_y;
	/// The valid states for the location of the head.
	typedef enum HeadMotion { LEFT, RIGHT, UP, DOWN, CENTER } HeadMotion;
	CvPoint2D32f** prevPoints;  ///< The previous set of points.
	CvPoint2D32f** nextPoints;  ///< The Current set of points.
	HeadMotion headLocation;   	///< The current head location.
public:
	MotionTracker(void);
	~MotionTracker(void);
	HeadMotion detect(CvPoint2D32f** points, int);
	HeadMotion getMotion();
};
#endif
