#ifndef _SKIN_TRACKER_H
#define _SKIN_TRACKER_H

#define SKIN_FILTER_WINDOW				"Skin Filter"

#include "Tracker.h"
#include "Utils.h"

class SkinTracker :
	public Tracker
{
private:
	IplImage *hsv, *hue, *mask, *backproject, *histImage,
		*image;
	CvHistogram *hist;
	char* cascade_name;
	int backprojectMode, selectObject, trackObject,
		showHist, vmin, vmax, smin, hdims;
	CvPoint origin;
	CvRect selectFrame;
	CvRect trackFrame;
	CvBox2D trackBox;
	Utils* util;

	//functions
	void updateHueImage();
	void shrinkTrackingBox(int ammount);
	void init(IplImage* frame);

public:
	SkinTracker(void);
	~SkinTracker(void);
	static void mouseCallback(int event, int x, int y, int flags, void* param);
	void onMouse(int event, int x, int y);
	CvRect* detect(IplImage *pImg);
	void startTracking(IplImage *pImg);
	void track();
	void select(CvRect* r);

};

#endif
