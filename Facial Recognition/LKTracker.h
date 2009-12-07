#ifndef _LK_TRACKER_H
#define _LK_TRACKER_H

#define LK_TRACKER_WINDOW				"LK TRACKER"

#include "OpenCVIncludes.h"

class LKTracker
{
private:
	//Constants
	static const int WIN_SIZE = 10, MAX_COUNT = 30;
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
	CvRect* detect(const IplImage *image);
	void setPoint(int x, int y);
	static void mouseCallback(int event, int x, int y, int flags, void* param);
	void select(CvRect *r);
	int getNumPoints();
	LKTracker(void);
	~LKTracker(void);
};

#endif
