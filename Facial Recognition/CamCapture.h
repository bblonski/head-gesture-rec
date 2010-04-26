// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _CAM_CAPTURE_H
#define _CAM_CAPTURE_H

#include "OpenCVIncludes.h"
#include "Capture.h"
#include "Utils.h"

class CamCapture : public Capture
{
private:
    static const char* const MAIN_WINDOW;
    CvVideoWriter* writer;
	CvCapture* capture;
    double lastCheckTime;
public:
    static const char* const VIDEO_FILE_NAME;
	CamCapture(void);
	~CamCapture(void);
	IplImage* getFrame();
    void noCamMsg();
};

#endif
