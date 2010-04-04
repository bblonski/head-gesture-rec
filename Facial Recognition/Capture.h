// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _CAPTURE_H
#define _CAPTURE_H

#include "OpenCVIncludes.h"
#include "Utils.h"

class Capture
{

public:
	virtual IplImage* getFrame() = 0;
    virtual ~Capture(void){};
};

#endif