#ifndef _CAM_CAPTURE_H
#define _CAM_CAPTURE_H

#include "Tracker.h"
#include "Utils.h"

class CamCapture
{
private:
	CvCapture* capture;
	Utils* util;
public:
	static const char* const MAIN_WINDOW;
	CamCapture(void);
	~CamCapture(void);
	IplImage* getFrame();
};

#endif
