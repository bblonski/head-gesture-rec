// $Id$
// Copyright (c) 2010 by Brian Blonski
#include "MotionTracker.h"
#include <iostream>

MotionTracker::MotionTracker(void): X_THRESHOLD(0.5), Y_THRESHOLD(0.2)
{
    headLocation = CENTER;
}

MotionTracker::~MotionTracker(void)
{
}


HeadMotion
MotionTracker::detect(CvPoint2D32f** points, int numPoints)
{
    left = right = center_x = center_y = up = down = 0;
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
        }else if (points[0][i].x < points[1][i].x - X_THRESHOLD )
        { // go right?
            right++;
        }else
        { // no horizontal movement
            center_x++;
        }
        // calculate direction of movement on y-axis
        if( points[0][i].y > points[1][i].y + Y_THRESHOLD)
        { // go up
            down++;
        }else if( points[0][i].y < points[1][i].y - Y_THRESHOLD)
        { // go down
            up++;
        }else
        { // no vertical movement
            center_y++;
        }
    }
    //determine direction
    if(left > max(right, center_x) && center_y > max(up, down))
        headLocation = LEFT;
    else if( right > max(left, center_x) && center_y > max(up, down))
        headLocation = RIGHT;
    else if( up > max(down, center_y) && center_x > max(left, right))
        headLocation = UP;
    else if( down > max(up, center_y) && center_x > max(left, right))
        headLocation = DOWN;
    else
        headLocation = CENTER;
#ifdef _DEBUG
    if( headLocation == CENTER)
        cout << "CENTER\n";
    else if (headLocation == UP)
        cout << "UP\n";
    else if (headLocation == DOWN)
        cout << "DOWN\n";
    else if (headLocation == LEFT)
        cout << "LEFT\n";
    else
        cout << "RIGHT\n";
#endif

    return headLocation;
}

HeadMotion
MotionTracker::getMotion()
{
    return headLocation;
}