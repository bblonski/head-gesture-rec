// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _UTILS_H
#define _UTILS_H

#include "OpenCVIncludes.h"

class Utils
{
private:
    char* logDir;
public:
    static const char* const LOGFILE;

	Utils(char* logDir);
	Utils(void);
	~Utils(void);
	static IplImage *printCoordinates(IplImage *image, double x, double y, CvPoint pt);
    static IplImage *printMsg(IplImage *image, char* string, CvPoint pt);
};

#endif
