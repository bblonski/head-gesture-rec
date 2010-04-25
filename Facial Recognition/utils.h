// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _UTILS_H
#define _UTILS_H

#include "OpenCVIncludes.h"
#include <time.h>

class Utils
{
public:
    // variables
    static const char* const LOGFILE;
    // fucntions
	static IplImage *printCoordinates(IplImage *image, double x, double y, CvPoint pt);
    static IplImage *printMsg(IplImage *image, char* string, CvPoint pt);
    static IplImage *printTime(IplImage *image, CvPoint pt);
    static void getTime(char* dest);
};

#endif
