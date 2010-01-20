#include "MotionTracker.h"

MotionTracker::MotionTracker(void)
{
	motion = CENTER;
}

MotionTracker::~MotionTracker(void)
{
}


MotionTracker::HeadMotion
MotionTracker::detect(CvPoint2D32f** points, int numPoints)
{
	if(nextPoints == NULL)
	{
		nextPoints = points;
		return motion;
	}
	prevPoints = nextPoints;
	nextPoints = points;
	for(int i=0; i<numPoints; i++)
	{
		//determine direction
	}
}

MotionTracker::HeadMotion
MotionTracker::getMotion()
{
	return motion;
}