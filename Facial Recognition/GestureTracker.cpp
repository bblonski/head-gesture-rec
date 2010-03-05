#include "GestureTracker.h"

GestureTracker::GestureTracker(void) : gestureCount(0), state(none)
{
}

GestureTracker::~GestureTracker(void)
{
}

HeadGesture
GestureTracker::track(HeadMotion motion)
{
    if(gestureCount > GESTURE_TIMEOUT || state == nod || state == shake)
    {
        state = none;
        gestureCount = 0;
    }

    switch(motion)
    {
    case LEFT:
        if(state == none)
            state = left1;
        else if(state == right1)
            state = left2;
        else if(state == right2)
            state = shake;
        else if(state == left1 || state == left2)
            gestureCount++;
        else
            state = none;
        break;
    case RIGHT:
        if(state == none)
            state = right1;
        else if(state == left1)
            state = right2;
        else if(state == left2)
            state = shake;
        else if(state == right1 || state == right2)
            gestureCount++;
        else
            state = none;
        break;
    case CENTER:
        gestureCount++;
        break;
    case UP:
        if(state == none)
            state = up1;
        else if(state == down1)
            state = up2;
        else if(state == down2)
            state = nod;
        else if(state == up1 || state == up2)
            gestureCount++;
        else
            state = none;
        break;
    case DOWN:
        if(state == none)
            state = down1;
        else if(state == up1)
            state = down2;
        else if(state == up2)
            state = nod;
        else if(state == down2 || state == down2)
            gestureCount++;
        else
            state = none;
        break;
    }
    return state;
}
