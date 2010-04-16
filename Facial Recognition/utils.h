// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _UTILS_H
#define _UTILS_H

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <time.h>
#include "OpenCVIncludes.h"

class Utils
{
private:
    char* logDir;
    static const char* const LOGFILE;
    ofstream logStream;
public:
	Utils(char* logDir);
	Utils(void);
	~Utils(void);
	static IplImage *printCoordinates(IplImage *image, double x, double y, CvPoint pt);
    static IplImage *printMsg(IplImage *image, char* string, CvPoint pt);
	void noCamMsg(void);
    void log(char*);
};

#endif
