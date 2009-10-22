#ifndef _TRACKER_H
#define _TRACKER_H

#define MAIN_WINDOW						"Main"
#define HAAR_CLASSIFIER_WINDOW			"Haar Classifier"
#define SKIN_FILTER_WINDOW				"Skin Filter"		

#include "OpenCVIncludes.h"

class Tracker
{	

public:
	Tracker(void);
	~Tracker(void);
	virtual CvRect* detect(IplImage *image) = 0;
	virtual void select(CvRect* r) = 0;
};

#endif
