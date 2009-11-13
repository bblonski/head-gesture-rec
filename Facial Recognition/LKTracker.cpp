#include "LKTracker.h"

LKTracker::LKTracker(void)
{
	cvNamedWindow(LK_TRACKER_WINDOW, CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback("LK_TRACKER_WINDOW", &LKTracker::mouseCallback, this); 
	points[0] = (CvPoint2D32f*)cvAlloc(MAX_COUNT*sizeof(points[0][0]));
    points[1] = (CvPoint2D32f*)cvAlloc(MAX_COUNT*sizeof(points[0][0]));
    status = (char*)cvAlloc(MAX_COUNT);
    flags = 0;
}

LKTracker::~LKTracker(void)
{
	cvDestroyWindow(LK_TRACKER_WINDOW);
}

void
LKTracker::init(IplImage* frame)
{
	image = cvCreateImage( cvGetSize(frame), 8, 3 );
    image->origin = frame->origin;
    grey = cvCreateImage( cvGetSize(frame), 8, 1 );
    prevGrey = cvCreateImage( cvGetSize(frame), 8, 1 );
    pyramid = cvCreateImage( cvGetSize(frame), 8, 1 );
    prevPyramid = cvCreateImage( cvGetSize(frame), 8, 1 );
}


void
LKTracker::onMouse(int event, int x, int y)
{
	if(!image)
		return;

    if( image->origin )
        y = image->height - y;

    if( event == CV_EVENT_LBUTTONDOWN )
    {
        point = cvPoint(x,y);
        hasPoint = true;
    }
}

void 
LKTracker::SetCount()
{
	int i;
	int k;
	cvCalcOpticalFlowPyrLK( prevGrey, grey, prevPyramid, pyramid,
		points[0], points[1], count, cvSize(WIN_SIZE,WIN_SIZE), 3, status, 0,
		cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03), flags );
	flags |= CV_LKFLOW_PYR_A_READY;
	for( i = k = 0; i < count; i++ )
	{
		if( hasPoint )
		{
			double dx = point.x - points[1][i].x;
			double dy = point.y - points[1][i].y;

			if( dx*dx + dy*dy <= 25 )
			{
				hasPoint = 0;
				continue;
			}
		}

		if( !status[i] )
			continue;

		points[1][k++] = points[1][i];
		cvCircle( image, cvPointFrom32f(points[1][i]), 3, CV_RGB(0,255,0), -1, 8,0);
	}
	count = k;
}

void 
LKTracker::AutoFindPoints()
{
	/* automatic initialization */
	IplImage* eig = cvCreateImage( cvGetSize(grey), 32, 1 );
	IplImage* temp = cvCreateImage( cvGetSize(grey), 32, 1 );
	double quality = 0.01;
	double min_distance = 10;

	count = MAX_COUNT;
	cvGoodFeaturesToTrack( grey, eig, temp, points[1], &count,
		quality, min_distance, 0, 3, 0, 0.04 );
	cvFindCornerSubPix( grey, points[1], count,
		cvSize(WIN_SIZE,WIN_SIZE), cvSize(-1,-1),
		cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
	cvReleaseImage( &eig );
	cvReleaseImage( &temp );

	hasPoint = false;
}

CvRect*
LKTracker::detect(IplImage *frame)
{
	if(!image)
		init(frame);
	cvCopy(frame, image, 0);
	cvCvtColor(image, grey, CV_BGR2GRAY);
	if(!initialized)
	{
		AutoFindPoints();
	}else if(count > 0)
	{
		SetCount();
	}

	if( hasPoint && count < MAX_COUNT )
	{
	points[1][count++] = cvPointTo32f(point);
	cvFindCornerSubPix( grey, points[1] + count - 1, 1,
		cvSize(WIN_SIZE,WIN_SIZE), cvSize(-1,-1),
		cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
	hasPoint = false;
	}

	CV_SWAP( prevGrey, grey, swapImage );
	CV_SWAP( prevPyramid, pyramid, swapImage );
	CV_SWAP( points[0], points[1], swapPoints );
	initialized = true;
	cvShowImage( "LK_TRACKER_WINDOW", image );
	
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