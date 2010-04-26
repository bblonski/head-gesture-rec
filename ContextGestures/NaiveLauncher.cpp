// $Id: Launcher.cpp 89 2010-04-26 00:02:11Z bblonski $
// Copyright (c) 2010 by Brian Blonski
/**
* Project: Camera Viewer beta.
*
* Description: Tracks head gestures with multiple feature tracking techniques.
*
* @author Brian Blonski
* @version 1.$Rev: 89 $
* @date $Date: 2010-04-25 17:02:11 -0700 (Sun, 25 Apr 2010) $
**/
#define _CRT_SECURE_NO_WARNINGS

#include "NaiveLauncher.h"
using namespace System::IO;


static void Log(char* message)
{
    ofstream stream;
    stream.open("log.txt", ios::app);
    char buffer[100];
    Utils::getTime(buffer);
    stream << buffer <<  message << endl;
    stream.close();
}

NaiveLauncher::NaiveLauncher()
{
}

NaiveLauncher::~NaiveLauncher(void)
{
    char dir[FILENAME_MAX];
    Utils::getTime(dir);
    System::String^ logDir = gcnew System::String(dir);
    logDir = logDir->Replace(":", "-");
    logDir = logDir->Replace("/", "-");
    Directory::CreateDirectory(logDir);
    System::String^ logFile = logDir + "/log.avi";
    File::Move("log.avi", logFile);
    logFile = logDir + "/log.txt";
    File::Move("log.txt", logFile);
}

int 
NaiveLauncher::run()
{
    launch = new Launcher();
    nreceiver.hookEvent(&launch->nodEvent);
    sreceiver.hookEvent(&launch->shakeEvent);
    int result = launch->run();
    nreceiver.unhookEvent(&launch->nodEvent);
    sreceiver.unhookEvent(&launch->shakeEvent);
    delete launch;
    return result;
}

void
NaiveLauncher::stop()
{
    launch->running = 0;
}

int
NaiveLauncher::isRunning()
{
    if(launch)
        return launch->running;
    else
        return 0;
}

#ifdef _EiC
main(1,"cameraViewer.c");
#endif