// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _HAAR_DETECTOR_H
#define _HAAR_DETECTOR_H

#include "Detector.h"
#include "Utils.h"
#include <stdlib.h>
#include <stdio.h>

class HaarDetector : public Detector
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
	vector<CvPoint> points;

	void init();

public:
	HaarDetector(CvHaarClassifierCascade* param, CvHaarClassifierCascade* pNestedCascade);
	HaarDetector();
	~HaarDetector(void);
	CvRect* detect(const IplImage *frame);
	void select(CvRect* r){};	
	vector<CvPoint> getPoints(void);

};
#endif
