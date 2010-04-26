// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _LAUNCHER_H
#define _LAUNCHER_H

#include "Resource.h"
#include "GestureEvent.h"
#include "Utils.h"
#include <time.h>
#include <fstream>

class Launcher
{
private:
    //char* log;
    Capture* cam;
    //NodReceiver nreceiver;
    //ShakeReceiver sreceiver;
   
    Detector* haar;
    PointTracker* lk;
    MotionTracker* motionTracker;
    GestureTracker* gestureTracker;
public:
    GestureEvent nodEvent;
    GestureEvent shakeEvent;
    int run(void);
    Launcher(void);
    ~Launcher(void);
};

#endif