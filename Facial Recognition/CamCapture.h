// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _CAM_CAPTURE_H
#define _CAM_CAPTURE_H

#include "OpenCVIncludes.h"
#include "Utils.h"

class CamCapture
{
private:
    static const char* const MAIN_WINDOW;
    static const char* const VIDEO_FILE_NAME;
    CvVideoWriter* writer;
	CvCapture* capture;
	Utils* util;
public:
	CamCapture(void);
	~CamCapture(void);
	IplImage* getFrame();
};

#endif
