// $Id$
// Copyright (c) 2010 by Brian Blonski
#include "Utils.h"

const char* const Utils::LOGFILE = "log.txt";

Utils::Utils(char* logDir)
{
}

Utils::Utils(void)
{
}

Utils::~Utils(void)
{
}

/* prints the x and y coordinates */
IplImage* Utils::printMsg(IplImage *image, char* string, CvPoint pt)
{
    CvFont font;
    //initialize the font
    cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX,
        0.3, 0.3, 0, 1, CV_AA);
    //write text to image
    cvPutText(image, string, pt, &font, CV_RGB( 250, 250, 250) );
    return image;
}

/* prints the x and y coordinates */
IplImage* Utils::printCoordinates(IplImage *image, double x, double y, CvPoint pt)
{
    CvFont font;
    int _TextOffset = 10;
    char *xCoord = (char*)malloc(20);
    if(xCoord == NULL) return NULL;
    char *yCoord = (char*)malloc(20);
    if(yCoord == NULL) return NULL;
    //initialize the font

    cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX,
        0.3, 0.3, 0, 1, CV_AA);
    //write x-y coordinates to strings
    sprintf(xCoord, "x = %g", x);
    sprintf(yCoord, "y = %g", y);
    //write text to image
    cvPutText(image, xCoord, pt, &font, CV_RGB( 250, 250, 250) );
    pt = cvPoint( pt.x, pt.y + _TextOffset);
    cvPutText(image, yCoord, pt, &font, CV_RGB(250, 250, 250) );
    free(xCoord);
    free(yCoord);
    return image;
}

void Utils::noCamMsg()
{
    CvFont font;
    int textX = 20;
    int textY = 50;
    int textOffset = 10;
    CvPoint pt = cvPoint( textX, textY );
    //320x240 blank image
    IplImage* msg = cvCreateImage(cvSize(320, 240), 8, 3);
    //initialize the font

    cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX,
        0.3, 0.3, 0, 1, CV_AA);
    //starting point of text
    cvZero(msg);
    //write message to the image
    cvPutText(msg, "No Camera Detected.", pt, &font, CV_RGB( 250, 250, 250) );
    pt = cvPoint( textX, textY + textOffset);
    cvPutText(msg, "Please connect camera and restart the program.", pt, &font, CV_RGB(250, 250, 250) );
    pt = cvPoint( textX, textY + 2*textOffset);
    cvPutText(msg, "Press any key to exit.", pt, &font, CV_RGB( 250, 250, 250) );
    //display the image in the container
    cvNamedWindow( "Error", 1 );
    cvShowImage("Error", msg);
    //wait till user presses a key
    cvWaitKey(0);
    cvReleaseImage(&msg);
    cvDestroyWindow("Error");
    exit(-1);
}