// $Id$
// Copyright (c) 2010 by Brian Blonski
#include "Resource.h"
#include "GestureEvent.h"
#ifdef _WINDOWS_
#include <windows.h>
#else
#include <sys/time.h>
#endif

/// Name to display in the Main Window
const char* const CamCapture::MAIN_WINDOW = "Main";
const char* const CamCapture::VIDEO_FILE_NAME = "log.avi";

/// Constructor for CamCapture
CamCapture::CamCapture(void) : writer(NULL), 
capture(cvCaptureFromCAM(0))
{
#if SHOW_WINDOWS
    cvNamedWindow(MAIN_WINDOW, 1);
#endif
    // if capture fails, display connect camera message
    if(!capture)
    {
        noCamMsg();
    }
#ifdef _WINDOWS_
    SYSTEMTIME st;
    GetSystemTime(&st);
    lastCheckTime = st.wSecond + st.wMilliseconds * 1e-3;
#else
    struct timeval time;
    gettimeofday(&time, NULL);
    lastCheckTime = time.tv_sec + time.tv_usec*1e-3;
#endif
}

/// Deconstructor for CamCapture
CamCapture::~CamCapture(void)
{
    if(writer)
        cvReleaseVideoWriter(&writer);
    cvReleaseCapture(&capture);
#if SHOW_WINDOWS
    cvDestroyWindow(MAIN_WINDOW);
#endif
}

/**
\brief
Grabs a frame from the camera and displays it in a window.

\returns
Image from the camera.

Write detailed description for getFrame here.

*/
IplImage* 
CamCapture::getFrame()
{
    IplImage* frame = 0; // Original frame taken from camera
    IplImage* image = 0; // Copy of image from the frame taken from the camera

    if(frame)
        cvReleaseImage(&frame);
    // grab the frame
    frame = cvQueryFrame(capture);
    if(!frame)
        return NULL;
    // create image size of frame
    if(!image)
    {
        image = cvCreateImage(cvGetSize(frame), 8, 1);
        image->origin = frame->origin;
    }

    // copy frame contents into image
    //cvCopy(frame, image, 0);
    cvCvtColor(frame, image, CV_BGR2GRAY);

    frame = Utils::printTime(frame, cvPoint(20, 20));

#ifdef _WINDOWS_
    SYSTEMTIME st;
    GetSystemTime(&st);
    double currentTime = st.wSecond + st.wMilliseconds * 1e-3;
#else
    struct timeval time;
    gettimeofday(&time, NULL);
    double currentTime = time.tv_sec + time.tv_usec * 1e-3;
#endif
    double fps = 1/(currentTime - lastCheckTime);
    lastCheckTime = currentTime;
    char fpsDisplay[1000];
    sprintf_s(fpsDisplay, "%.2f", fps);
    frame = Utils::printMsg(frame, fpsDisplay, cvPoint(frame->width - 50, 20));

    if(!writer)
        writer = cvCreateVideoWriter(VIDEO_FILE_NAME, 
                CV_FOURCC('I','Y','U','V'), 20, cvGetSize(frame));
    cvWriteFrame(writer, frame);

#if SHOW_WINDOWS
    cvShowImage(MAIN_WINDOW, frame);
#endif

    return image;
}

void 
CamCapture::noCamMsg()
{
    CvFont font;
    int textX = 20;
    int textY = 50;
    int textOffset = 10;
    CvPoint pt = cvPoint(textX, textY);
    // 320x240 blank image
    IplImage* msg = cvCreateImage(cvSize(320, 240), 8, 3);
    // initialize the font
    cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 0.3, 0.3, 0, 1, CV_AA);
    // starting point of text
    cvZero(msg);
    // write message to the image
    cvPutText(msg, "No Camera Detected.", pt, &font, CV_RGB(250, 250, 250));
    pt = cvPoint(textX, textY + textOffset);
    cvPutText(msg, "Please connect camera and restart the program.", pt, &font, 
        CV_RGB(250, 250, 250));
    pt = cvPoint(textX, textY + 2*textOffset);
    cvPutText(msg, "Press any key to exit.", pt, &font, CV_RGB(250, 250, 250));
    // display the image in the container
    cvNamedWindow("Error", 1);
    cvShowImage("Error", msg);
    // wait till user presses a key
    cvWaitKey(0);
    cvReleaseImage(&msg);
#if SHOW_WINDOW
    cvDestroyWindow("Error");
#endif
    exit(-1);
}