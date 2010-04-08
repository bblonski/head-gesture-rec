// $Id$
// Copyright (c) 2010 by Brian Blonski
/**
* Project: Camera Viewer beta.
*
* Description: Tracks head gestures with multiple feature tracking techniques.
*
* @author Brian Blonski
* @version 1.$Rev: 47 $
* @date $Date: 2009-12-07 01:37:27 -0800 (Mon, 07 Dec 2009) $
**/

#include "resource.h"
#include "GestureEvent.h"
#include "Launcher.h"
#include <time.h>

//C:\Program Files (x86)\OpenCV\data\haarcascades\haarcascade_frontalface_alt.xml

static int timer;

static void Thread( void* pParams )
{
    srand((int)time(NULL));
    Sleep(*((int*)pParams));
    if(rand() % 2)
        MessageBox(NULL, L"Please nod your head", L"Nod", NULL);
    else
        MessageBox(NULL, L"Please shake your head", L"Shake", NULL);
    timer = (10 + rand() % 5) * 1000;
    uintptr_t hand = _beginthread( Thread, 0, &timer );
    _endthread();
}

// Entry Point for Program
//int main(int argc, char* argv[])
int 
Launcher::run()
{
    // Create new camera capture
    Capture *cam = new CamCapture();
    NodReceiver nreceiver;
    ShakeReceiver sreceiver;
    GestureEvent nodEvent;
    GestureEvent shakeEvent;
    nreceiver.hookEvent(&nodEvent);
    sreceiver.hookEvent(&shakeEvent);
    // Init new trackers
    Detector* haar = new HaarDetector();
    //SkinDetector* skin = new SkinDetector();
    PointTracker* lk = new LKTracker();
    MotionTracker* motionTracker = new MotionTracker();
    GestureTracker* gestureTracker = new GestureTracker();
    srand((int)time(NULL));
    timer = (30 + rand() % 15) * 1000;
    uintptr_t hand = _beginthread( Thread, 0, &timer );   

    CvRect* r = NULL;
    int runonce = true;

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
            __raise nodEvent.gEvent();
        }
        else if(gesture == shake)
        {
            printf("SHAKE DETECTED!\n");
            __raise shakeEvent.gEvent();
        }

        cvReleaseImage(&tmp);

        // wait for esc key
        char c = cvWaitKey(1);
        if( (char) c == 27 )
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
    //delete skin;
    delete cam;
    delete lk;
    delete motionTracker;
    delete gestureTracker;
    return 0;
}

int main(int argc, char* argv[])
{
    Launcher* launch = new Launcher();
    return launch->run();
    delete launch;
}

#ifdef _EiC
main(1,"cameraViewer.c");
#endif