// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _GESTURE_TRACKER_H
#define _GESTURE_TRACKER_H

#include "MotionTracker.h"

typedef enum HeadGesture { none, up1, down1, up2, down2, shake, 
                           left1, right1, left2, right2,  nod} HeadGesture;

class GestureTracker
{
private:
    int gestureCount;
    static const int GESTURE_TIMEOUT = 15;
    HeadGesture state;
    MotionTracker* motionTracker;
public:
    GestureTracker(void);
    ~GestureTracker(void);
    HeadGesture track(CvPoint2D32f** points, int numPoints);
};

#endif