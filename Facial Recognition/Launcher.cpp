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
#include <time.h>
#include <fstream>
#include "resource.h"
#include "GestureEvent.h"
#include "Utils.h"
#include "Launcher.h"

//C:\Program Files (x86)\OpenCV\data\haarcascades\haarcascade_frontalface_alt.xml

static int timer;

static void Log(char* message){
    ofstream stream;
    stream.open("log.txt", ios::app);
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[21];
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime(buffer, 100, "[%x %X] ", timeinfo);
    stream << buffer <<  message << endl;
    stream.close();
}

static void Thread( void* pParams )
{
    srand((int)time(NULL));
    Sleep(*((int*)pParams));
    if(rand() % 2){
        Log("Nod expected");
        while( MessageBox(NULL, L"Please nod your head", L"Nod", MB_SYSTEMMODAL) == IDOK);
        Log("Nod received");
    }
    else{
        Log("Shake expected");
        while(MessageBox(NULL, L"Please shake your head", L"Shake", MB_SYSTEMMODAL) == IDOK);
        Log("Shake received");
    }
    timer = (10 + rand() % 5) * 1000;
    uintptr_t hand = _beginthread( Thread, 0, &timer );
    _endthread();
}

Launcher::Launcher(char *logDir)
{
    // Create new camera capture
    cam = new CamCapture();
    nreceiver;
    sreceiver;
    nodEvent;
    shakeEvent;
    nreceiver.hookEvent(&nodEvent);
    sreceiver.hookEvent(&shakeEvent);
    // Init new trackers
    haar = new HaarDetector();
    //SkinDetector* skin = new SkinDetector();
    lk = new LKTracker();
    motionTracker = new MotionTracker();
    gestureTracker = new GestureTracker();
    srand((int)time(NULL));
    utils = new Utils(logDir);
}

Launcher::~Launcher(void)
{
}

int 
Launcher::run()
{
    timer = (30 + rand() % 15) * 1000;
    uintptr_t hand = _beginthread( Thread, 0, &timer );
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
    Log("End");
    return 0;
}

int main(int argc, char* argv[])
{
    Launcher* launch = new Launcher((argv[0]) ? argv[0] : NULL);
    return launch->run();
    delete launch;
}

#ifdef _EiC
main(1,"cameraViewer.c");
#endif