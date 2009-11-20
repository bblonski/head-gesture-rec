#ifndef _HAAR_TRACKER_H
#define _HAAR_TRACKER_H

#include "Tracker.h"
#include "Utils.h"

class HaarTracker
{
private:
	static const char* const HAAR_CLASSIFIER_WINDOW;
	static const char* const HAARCASCADE_DIR;
	static const char* const HAARCASCADE_FRONTALFACE;
	static const char* const HAARCASCADE_EYE;
	static const char* const HAARCASCADE_PROFILE;

	IplImage *image;
	CvMemStorage* storage;
	CvHaarClassifierCascade* cascade;
	CvHaarClassifierCascade* nestedCascade;
	Utils* util;

	void init();

public:
	HaarTracker(CvHaarClassifierCascade* param, CvHaarClassifierCascade* pNestedCascade);
	HaarTracker();
	~HaarTracker(void);
	CvRect* detect(const IplImage *frame);
	void select(CvRect* r){};
};
#endif
