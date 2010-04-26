// $Id: Launcher.h 89 2010-04-26 00:02:11Z bblonski $
// Copyright (c) 2010 by Brian Blonski
#ifndef _LAUNCHER_H
#define _LAUNCHER_H

#include "Resource.h"
#include "GestureEvent.h"
#include "Utils.h"
#include <time.h>
#include <fstream>

class NaiveLauncher
{
private:
    char* log;
    Capture* cam;
    NodReceiver nreceiver;
    ShakeReceiver sreceiver;
    GestureEvent nodEvent;
    GestureEvent shakeEvent;
    Detector* haar;
    PointTracker* lk;
    MotionTracker* motionTracker;
    GestureTracker* gestureTracker;
    Utils* utils;
public:
    int run(void);
    NaiveLauncher(char*);
    NaiveLauncher(void);
    ~NaiveLauncher(void);
};

#endif