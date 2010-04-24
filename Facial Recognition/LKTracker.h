// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _LK_TRACKER_H
#define _LK_TRACKER_H

#define LK_TRACKER_WINDOW				"LK TRACKER"

#include "OpenCVIncludes.h"
#include "PointTracker.h"

class LKTracker : public PointTracker
{
private:
	//Constants
	static const int WIN_SIZE = 5, MAX_COUNT = 25;
	//Variables
	IplImage *image, *grey, *prevGrey, *pyramid, *prevPyramid, *swapImage;
	CvPoint2D32f* points[2], *swapPoints;
	char* status;
	int numPoints, flags;
	CvPoint point;
	CvRect* ROI;
	bool hasNewPoint, initialized;
	//Functions
	void init(const IplImage* image);
	void autoFindPoints();
	void setCount();
	void onMouse(int event, int x, int y);

public:
	void detect(const IplImage *image);
	void setPoint(int x, int y);
	static void mouseCallback(int event, int x, int y, int flags, void* param);
	void select(CvRect *r);
	int getNumPoints();
	CvPoint2D32f** getPoints();
	LKTracker(void);
	~LKTracker(void);
};

#endif
