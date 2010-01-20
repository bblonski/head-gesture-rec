// $Id$
// Copyright (c) 2010 by Brian Blonski
#include "MotionTracker.h"

MotionTracker::MotionTracker(void)
{
	headLocation = CENTER;
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
		return headLocation;
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
	return headLocation;
}