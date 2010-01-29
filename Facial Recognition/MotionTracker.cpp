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
    // first initialization
    if(nextPoints == NULL)
    {
        nextPoints = points;
        return headLocation; // should be CENTER
    }
    prevPoints = nextPoints;
    nextPoints = points;
    for(int i=0; i<numPoints; i++)
    {
        // calculate direction of movement on x-axis
        if( points[0][i].x > points[1][i].x + X_THRESHOLD )
        { // go left?
            left++;
        }else if (points[0][i].x < points[1][i].x + X_THRESHOLD )
        { // go right?
            right++;
        }else
        { // no horizontal movement
            center_x++;
        }
        // calculate direction of movement on y-axis
        if( points[0][i].y > points[1][i].y + Y_THRESHOLD)
        { // go up?
            up++;
        }else if( points[0][i].y < points[1][i].y + Y_THRESHOLD)
        { // go down?
            down++;
        }else
        { // no vertical movement
            center_y++;
        }

        //determine direction
    }
    return headLocation;
}

MotionTracker::HeadMotion
MotionTracker::getMotion()
{
    return headLocation;
}