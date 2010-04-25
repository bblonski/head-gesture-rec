// $Id$
// Copyright (c) 2010 by Brian Blonski
#include "MotionTracker.h"
#include <iostream>

MotionTracker::MotionTracker(void): X_THRESHOLD(0.5), Y_THRESHOLD(0.5)
{
    headLocation = CENTER;
}

MotionTracker::~MotionTracker(void)
{
}


HeadMotion
MotionTracker::detect(CvPoint2D32f** points, int numPoints)
{
    double left = 0, right = 0, center_x = 0, center_y = 0, up = 0, down = 0;
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
        if(points[0][i].x > points[1][i].x + X_THRESHOLD)
        { // go left?
            left += points[0][i].x - points[1][i].x;
        }else if (points[0][i].x < points[1][i].x - X_THRESHOLD)
        { // go right?
            right += points[1][i].x - points[0][i].x;
        }else
        { // no horizontal movement
            center_x += X_THRESHOLD;
        }

        // calculate direction of movement on y-axis
        if(points[0][i].y > points[1][i].y + Y_THRESHOLD)
        { // go up
            down += points[0][i].y - points[1][i].y;
        }else if(points[0][i].y < points[1][i].y - Y_THRESHOLD)
        { // go down
            up += points[1][i].y - points[0][i].y;
        }else
        { // no vertical movement
            center_y += Y_THRESHOLD;
        }
    }
    //determine direction
    if(left > max(right, center_x) && max(left, center_y) > max(up, down))
        headLocation = LEFT;
    else if(right > max(left, center_x) && max(right, center_y) > max(up, down))
        headLocation = RIGHT;
    else if(up > max(down, center_y) && max(up, center_x) > max(left, right))
        headLocation = UP;
    else if(down > max(up, center_y) && max(down, center_x) > max(left, right))
        headLocation = DOWN;
    else
        headLocation = CENTER;

#ifdef _DEBUG
    if(headLocation == CENTER)
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