// $Id$
// Copyright (c) 2010 by Brian Blonski
#include "CamCapture.h"
#include "Resource.h"

/// Name to display in the Main Window
const char* const CamCapture::MAIN_WINDOW = "Main";

/// Constructor for CamCapture
CamCapture::CamCapture(void)
{
	util = new Utils();
	capture = cvCaptureFromCAM( 0 ); // get images from first camera
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

	// create image size of frame
	if( !image )
	{
		image = cvCreateImage( cvGetSize(frame), 8, 3 );
		image->origin = frame->origin;
	}

	// copy frame contents into image
	cvCopy( frame, image, 0 );

	// wait for esc key
	c = cvWaitKey(10);
	if( (char) c == 27 )
	{
        // cleanup
		cvReleaseImage(&image);
		return NULL;
	}
	return image;
}