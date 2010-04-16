// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _LAUNCHER_H
#define _LAUNCHER_H

class Launcher
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
    Launcher(char*);
    Launcher(void);
    ~Launcher(void);
};

#endif