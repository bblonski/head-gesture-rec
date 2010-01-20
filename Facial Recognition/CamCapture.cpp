// $Id$
// Copyright (c) 2010 by Brian Blonski
#include "CamCapture.h"
#include "Resource.h"

const char* const CamCapture::MAIN_WINDOW = "Main";

CamCapture::CamCapture(void)
{
	util = new Utils();
	capture = cvCaptureFromCAM( 0 );
	cvNamedWindow(MAIN_WINDOW, 1);
	//if capture fails, display connect camera message
    if( !capture )
    {
		util->noCamMsg();
    }
}

CamCapture::~CamCapture(void)
{
	cvReleaseCapture( &capture );
	cvDestroyWindow(MAIN_WINDOW);
}

/* Grabs a frame from the camera and displays it in a window. */
IplImage* CamCapture::getFrame()
{
	IplImage* frame = 0;
	IplImage* image = 0;
	int c;

	//grab the frame
	frame = cvQueryFrame( capture );
	if( !frame )
		return NULL;

	//create image size of frame
	if( !image )
	{
		image = cvCreateImage( cvGetSize(frame), 8, 3 );
		image->origin = frame->origin;
	}

	//copy frame contents into image
	cvCopy( frame, image, 0 );

	//wait for esc key
	c = cvWaitKey(10);
	if( (char) c == 27 )
	{
		cvReleaseImage(&image);
		return NULL;
	}
	return image;
}