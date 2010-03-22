// $Id$
// Copyright (c) 2010 by Brian Blonski
#include "Resource.h"
#include "GestureEvent.h"

/// Name to display in the Main Window
const char* const CamCapture::MAIN_WINDOW = "Main";
const char* const CamCapture::VIDEO_FILE_NAME = "test.avi";

/// Constructor for CamCapture
CamCapture::CamCapture(void) : writer(NULL), util(new Utils()), 
capture(cvCaptureFromCAM(0))
{
    cvNamedWindow(MAIN_WINDOW, 1);
    // if capture fails, display connect camera message
    if( !capture )
    {
        util->noCamMsg();
    }
}

/// Deconstructor for CamCapture
CamCapture::~CamCapture(void)
{
    delete util;
    if( writer )
        cvReleaseVideoWriter(&writer);
    cvReleaseCapture( &capture );
    cvDestroyWindow(MAIN_WINDOW);
}

/**
\brief
Grabs a frame from the camera and displays it in a window.

\returns
Image from the camera.

Write detailed description for getFrame here.

*/
IplImage* CamCapture::getFrame()
{
    IplImage* frame = 0; // Original frame taken from camera
    IplImage* image = 0; // Copy of image from the frame taken from the camera
    int c; // key press

    // grab the frame
    frame = cvQueryFrame( capture );
    if( !frame )
        return NULL;
    if( !writer)
        writer = cvCreateVideoWriter(VIDEO_FILE_NAME, CV_FOURCC('I','Y','U','V'), 
        10, cvGetSize(frame));
    cvWriteFrame(writer, frame);
    cvShowImage(MAIN_WINDOW, frame);

    // create image size of frame
    if( !image )
    {
        image = cvCreateImage( cvGetSize(frame), 8, 1);
        image->origin = frame->origin;
    }

    // copy frame contents into image

    //cvCopy(frame, image, 0);

    cvCvtColor( frame, image, CV_BGR2GRAY );

    // wait for esc key
    c = cvWaitKey(1);
    if( (char) c == 27 )
    {
        // cleanup
        cvReleaseImage(&image);
        return NULL;
    }
    return image;
}