// $Id: tracker.h 52 2010-01-20 05:25:36Z Brian Blonski $
// Copyright (c) 2010 by Brian Blonski
#ifndef _DETECTOR_H
#define _DETECTOR_H	

#include "OpenCVIncludes.h"

class Detector
{	

public:
	virtual CvRect* detect(IplImage *image) = 0;
	virtual void select(CvRect* r) = 0;
};

#endif
