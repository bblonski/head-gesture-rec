#include "LKTracker.h"

LKTracker::LKTracker(void)
{
	cvNamedWindow(LK_TRACKER_WINDOW, CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback("LK_TRACKER_WINDOW", &LKTracker::mouseCallback, this); 
	points = new CvPoint2D32f[2];

}

LKTracker::~LKTracker(void)
{
	cvDestroyWindow(LK_TRACKER_WINDOW);
}


void
LKTracker::onMouse(int event, int x, int y)
{

}

CvRect*
LKTracker::detect(IplImage *image)
{
	return new CvRect();
}

/**
 * mouseCallback sets the onMouse event as a mouse callback function.
 */
void
LKTracker::mouseCallback(int event, int x, int y, int flags, void *param)
{
	((LKTracker*)param)->onMouse(event, x, y);
}