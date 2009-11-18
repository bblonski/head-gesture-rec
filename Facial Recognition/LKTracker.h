#ifndef _LK_TRACKER_H
#define _LK_TRACKER_H

#define LK_TRACKER_WINDOW				"LK TRACKER"

#include "tracker.h"

class LKTracker :
	public Tracker
{
private:
	//Constants
	static const int WIN_SIZE = 10, MAX_COUNT = 500;
	//Variables
	IplImage *image, *grey, *prevGrey, *pyramid, *prevPyramid, *swapImage;
	CvPoint2D32f* points[2], *swapPoints;
	char* status;
	int count, flags;
	CvPoint point;
	bool hasPoint, initialized;
	//Functions
	void init(IplImage* image);
	void autoFindPoints();
	void setCount();
	void onMouse(int event, int x, int y);

public:
	CvRect* detect(IplImage *image);
	void setPoint(int x, int y);
	static void mouseCallback(int event, int x, int y, int flags, void* param);
	void select(CvRect *r);
	LKTracker(void);
	~LKTracker(void);
};

#endif
