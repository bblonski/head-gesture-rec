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
	CamCapture(void);
	~CamCapture(void);
	IplImage* getFrame();
};

#endif
