#ifndef _GESTURE_TRACKER_H
#define _GESTURE_TRACKER_H

#include "MotionTracker.h"

typedef enum HeadGesture { none, up1, down1, up2, down2, shake, 
                           left1, right1, left2, right2,  nod} HeadGesture;

class GestureTracker
{
private:
    int gestureCount;
    static const int GESTURE_TIMEOUT = 10;
    HeadGesture state;
public:
    GestureTracker(void);
    ~GestureTracker(void);
    HeadGesture track(HeadMotion motion);
};

#endif