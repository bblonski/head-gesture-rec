// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _TRACKER_H
#define _TRACKER_H	

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
