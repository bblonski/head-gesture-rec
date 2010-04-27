// $Id: Launcher.h 89 2010-04-26 00:02:11Z bblonski $
// Copyright (c) 2010 by Brian Blonski
#ifndef _NAIVE_LAUNCHER_H
#define _NAIVE_LAUNCHER_H

#include "Resource.h"
#include "GestureEvent.h"
#include "Utils.h"
#include <time.h>
#include <fstream>
#include "Launcher.h"

using namespace System::IO;

class NaiveLauncher
{
private:
    NodReceiver nreceiver;
    ShakeReceiver sreceiver;
    Launcher* launch;
public:
    int run(void);
    void stop();
    NaiveLauncher(void);
    ~NaiveLauncher(void);
};

#endif