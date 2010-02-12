#include "GestureTracker.h"

GestureTracker::GestureTracker(void)
{
    gestureCount = 0;
}

GestureTracker::~GestureTracker(void)
{
}

HeadGesture
GestureTracker::track(HeadMotion motion)
{
    if( ++gestureCount > GESTURE_TIMEOUT)
        return NONE;
    if(motion != gestures[GESTURE_ARRAY_LENGTH])
    {
        for(int i=1; i<gestures[GESTURE_ARRAY_LENGTH]; i++)
            gestures[i-1] = gestures[i];
        gestures[GESTURE_ARRAY_LENGTH] = motion;
    }
    return NONE;
}

HeadGesture
GestureTracker::detect(HeadMotion headGesture[])
{
    switch(headGesture[0])
    {
    case LEFT:
        ;
    case RIGHT:
        ;
    case CENTER:
        ;
    case UP:
        ;
    case DOWN:
        ;
    }
    return NONE;
}


