#ifndef _GESTURE_TRACKER_H
#define _GESTURE_TRACKER_H

#include "MotionTracker.h"

typedef enum HeadGesture { NONE, NOD, SHAKE } HeadGesture;

class GestureTracker
{
private:
    int gestureCount;
    static const int GESTURE_ARRAY_LENGTH = 5;
    static const int GESTURE_TIMEOUT = 10;
    HeadMotion gestures[5];
    HeadGesture detect(HeadMotion[]);
public:
    GestureTracker(void);
    ~GestureTracker(void);
    HeadGesture track(HeadMotion motion);
};

#endif