// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _POINT_TRACKER_H
#define _POINT_TRACKER_H	

#include "OpenCVIncludes.h"

class PointTracker
{	

public:
	virtual void detect(const IplImage *image) = 0;
	virtual void select(CvRect* r) = 0;
	virtual int getNumPoints() = 0;
	virtual CvPoint2D32f** getPoints() = 0;
    virtual ~PointTracker(){};
};

#endif
