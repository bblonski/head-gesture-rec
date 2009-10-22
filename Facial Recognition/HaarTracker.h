#ifndef _HAAR_TRACKER_H
#define _HAAR_TRACKER_H

#define HAARCASCADE_FRONTALFACE "C:\\Program Files (x86)\\OpenCV\\data\\haarcascades\\haarcascade_frontalface_alt.xml"

#include "Tracker.h"
#include "Utils.h"

class HaarTracker : public Tracker
{
	private:
	CvMemStorage* storage;
	CvHaarClassifierCascade* cascade;
	CvHaarClassifierCascade* nested_cascade;
	char* cascade_name;
	int use_nested_cascade;
	Utils* util;

public:
	HaarTracker(void);
	~HaarTracker(void);
	CvRect* detect(IplImage *image);
	void select(CvRect* r){};
};
#endif
