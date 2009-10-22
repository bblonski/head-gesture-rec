#ifndef _TRACKER_H
#define _TRACKER_H

#define MAIN_WINDOW	"Main"		

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
