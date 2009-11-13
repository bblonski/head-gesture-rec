#ifndef _LK_TRACKER_H
#define _LK_TRACKER_H

#define LK_TRACKER_WINDOW				"LK TRACKER"

#include "tracker.h"

class LKTracker :
	public Tracker
{
private:
	IplImage *img, *grey, *prevGrey, *pyramid, prevPyramid, swap;
	static const int WIN_SIZE = 10;
	static const int MAX_COUNT = 500;
	CvPoint2D32f* points, *swapPoints;
	char* status;
	int count;
	int initiated;
	CvPoint point;

public:
	void onMouse(int event, int x, int y);
	CvRect* detect(IplImage *image);
	static void mouseCallback(int event, int x, int y, int flags, void* param);
	LKTracker(void);
	~LKTracker(void);
};

#endif
