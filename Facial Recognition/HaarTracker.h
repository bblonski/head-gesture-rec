#ifndef _HAAR_TRACKER_H
#define _HAAR_TRACKER_H

#define HAAR_CLASSIFIER_WINDOW	"Haar Classifier"
#define HAARCASCADE_DIR			"C:\\Program Files (x86)\\OpenCV\\data\\haarcascades\\"
#define HAARCASCADE_FRONTALFACE "haarcascade_frontalface_alt.xml"
#define HAARCASCADE_EYE			"haarcascade_eye.xml"
#define HAARCASCADE_PROFILE		"haarcascade_profileface.xml"

#include "Tracker.h"
#include "Utils.h"

class HaarTracker : public Tracker
{
	private:
	CvMemStorage* storage;
	CvHaarClassifierCascade* cascade;
	CvHaarClassifierCascade* nested_cascade;
	int use_nested_cascade;
	Utils* util;

public:
	HaarTracker(void);
	HaarTracker(char* param);
	~HaarTracker(void);
	CvRect* detect(IplImage *image);
	void select(CvRect* r){};
};
#endif
