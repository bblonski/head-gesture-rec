// $Id$
// Copyright (c) 2010 by Brian Blonski
/**
* Project: Camera Viewer beta.
*
* Description: Tracks head gestures with multiple feature tracking techniques.
*
* @author Brian Blonski
* @version 1.$Rev$
* @date $Date$
**/
#define _CRT_SECURE_NO_WARNINGS

#include "Launcher.h"

static void Log(char* message)
{
    ofstream stream;
    stream.open("log.txt", ios::app);
    char buffer[100];
    Utils::getTime(buffer);
    stream << buffer <<  message << endl;
    stream.close();
}

Launcher::Launcher(void)
{
    running = true;
}

Launcher::~Launcher(void)
{
}

int 
Launcher::run()
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
    while(running)
    {
        try
        {
        // Get frame frome camera
        IplImage *tmp = cam->getFrame();
        if(tmp == NULL)
            break;

        while(r == NULL)
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
        }catch (...)
        {
            Log("Error");
        }
    }

    // cleanup
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