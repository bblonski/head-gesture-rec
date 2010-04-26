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

static void Log(char* message)
{
    ofstream stream;
    stream.open("log.txt", ios::app);
    char buffer[100];
    Utils::getTime(buffer);
    stream << buffer <<  message << endl;
    stream.close();
}

NaiveLauncher::NaiveLauncher(char* Logdir)
{
    nreceiver;
    sreceiver;
    nodEvent;
    shakeEvent;
    nreceiver.hookEvent(&nodEvent);
    sreceiver.hookEvent(&shakeEvent);
    srand((int)time(NULL));
}

NaiveLauncher::~NaiveLauncher(void)
{
}

int 
NaiveLauncher::run()
{
    // Create new camera capture
    cam = new CamCapture();
    // Init new trackers
    haar = new HaarDetector();
    lk = new LKTracker();
    motionTracker = new MotionTracker();
    gestureTracker = new GestureTracker();

    CvRect* r = NULL;
    int runonce = true;
    Log("starting...");
    // Tracking loop
    while(true)
    {
        /*try
        {*/
        // Get frame frome camera
        IplImage *tmp = cam->getFrame();
        if(tmp == NULL)
            break;

        if(!r)
        {
            r = haar->detect(tmp);
        }

        lk->detect(tmp);

        if(r && runonce)
        {
            lk->select(r);
            runonce = false;
        }
        HeadGesture gesture = gestureTracker->track(lk->getPoints(), lk->getNumPoints());
        if(gesture == nod){
            printf("NOD DETECTED!\n");
            Log("Nod");
            __raise nodEvent.gEvent();
        }
        else if(gesture == shake)
        {
            printf("SHAKE DETECTED!\n");
            Log("Shake");
            __raise shakeEvent.gEvent();
        }

        cvReleaseImage(&tmp);

        // wait for esc key
        char c = cvWaitKey(1);
        if((char) c == 27)
        {
            // exit loop
            break;
        }
        cvReleaseImage(&tmp);
        //}catch (...)
        //{
        //	cerr << "Error";
        //}
    }

    // cleanup
    nreceiver.unhookEvent(&nodEvent);
    sreceiver.unhookEvent(&shakeEvent);
    if(r)
        free(r);
    delete haar;
    delete cam;
    delete lk;
    delete motionTracker;
    delete gestureTracker;
    Log("End");
    return 0;
}

#ifdef _EiC
main(1,"cameraViewer.c");
#endif