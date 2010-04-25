// $Id$
// Copyright (c) 2010 by Brian Blonski
#include "Utils.h"

const char* const Utils::LOGFILE = "log.txt";

/* prints the x and y coordinates */
IplImage* 
Utils::printMsg(IplImage *image, char* string, CvPoint pt)
{
    CvFont font;
    //initialize the font
    cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 0.3, 0.3, 0, 1, CV_AA);
    //write text to image
    cvPutText(image, string, pt, &font, CV_RGB(250, 250, 0));
    return image;
}

/* prints the x and y coordinates */
IplImage* 
Utils::printCoordinates(IplImage *image, double x, double y, CvPoint pt)
{
    CvFont font;
    int _TextOffset = 10;
    char xCoord[20];
    char yCoord[20];
    //initialize the font

    cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 0.3, 0.3, 0, 1, CV_AA);
    //write x-y coordinates to strings
    sprintf(xCoord, "x = %g", x);
    sprintf(yCoord, "y = %g", y);
    //write text to image
    cvPutText(image, xCoord, pt, &font, CV_RGB(250, 250, 250));
    pt = cvPoint(pt.x, pt.y + _TextOffset);
    cvPutText(image, yCoord, pt, &font, CV_RGB(250, 250, 250));
    return image;
}

IplImage* 
Utils::printTime(IplImage *image, CvPoint pt)
{
    CvFont font;
    //initialize the font
    char buffer[100];
    Utils::getTime(buffer);
    cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 0.3, 0.3, 0, 1, CV_AA);
    //write text to image
    cvPutText(image, buffer, pt, &font, CV_RGB(250, 250, 0));
    return image;
}

void
Utils::getTime(char* dest)
{
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime(dest, 100, "[%x %X] ", timeinfo);
}