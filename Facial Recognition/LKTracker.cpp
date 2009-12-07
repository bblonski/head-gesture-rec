#include "LKTracker.h"

// Constructor
LKTracker::LKTracker(void)
{
	cvNamedWindow(LK_TRACKER_WINDOW, CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback(LK_TRACKER_WINDOW, &LKTracker::mouseCallback, this); 
	points[0] = (CvPoint2D32f*)cvAlloc(MAX_COUNT*sizeof(points[0][0]));
    points[1] = (CvPoint2D32f*)cvAlloc(MAX_COUNT*sizeof(points[0][0]));
    status = (char*)cvAlloc(MAX_COUNT);
    flags = 0;
	image = grey = prevGrey = pyramid = prevPyramid = swapImage = 0;
	hasNewPoint = false;
	numPoints = 0;
	initialized = true;
	ROI = 0;
}

// Deconstructor
LKTracker::~LKTracker(void)
{
	cvDestroyWindow(LK_TRACKER_WINDOW);
}

// Initializes the image
void
LKTracker::init(const IplImage* frame)
{
	image = cvCreateImage( cvGetSize(frame), 8, 3 );
    image->origin = frame->origin;
    grey = cvCreateImage( cvGetSize(frame), 8, 1 );
    prevGrey = cvCreateImage( cvGetSize(frame), 8, 1 );
    pyramid = cvCreateImage( cvGetSize(frame), 8, 1 );
    prevPyramid = cvCreateImage( cvGetSize(frame), 8, 1 );
}

// Mouse callback for setting tracking points
void
LKTracker::onMouse(int event, int x, int y)
{
	if(!image)
		return;

    if( image->origin )
        y = image->height - y;

    if( event == CV_EVENT_LBUTTONDOWN )
    {
        setPoint(x,y);
    }
}

// Selects a tracking point at the center of the given rectangle
void
LKTracker::select(CvRect *r)
{
	if(!image)
		return;
	ROI = new CvRect(*r);
	// Shrink ROI because box tends to be larger than the face
	// which results in including lots of background points.
	// min size r should be 80x80
	ROI->width -= 20;
	ROI->height -= 20;
	ROI->x += 10;
	ROI->y += 10;
	initialized = false;
}

// Sets a tracking point at the given x-y coordinates
void
LKTracker::setPoint(int x, int y)
{
	point = cvPoint(x,y);
	hasNewPoint = true;
}

// Determines the current number of valid points
void 
LKTracker::setCount()
{
	int index, newNumPoints;
	// Calculates the optical flow between the grey images
	cvCalcOpticalFlowPyrLK( 
		prevGrey,		// Previous image
		grey,			// Current image
		prevPyramid,	// Pyramid of previous image
		pyramid,		// Pyramid of current image
		points[0],		// Array of points indicating the features that need to be found
		points[1],		// Array of calculated NEW points of the features
		numPoints,		// Number of features to track
		cvSize(WIN_SIZE,WIN_SIZE), // Size of search window
		3,				// Level - 4 pyramids
		status,			// Array containing 1 is the cooresponding element is found, else 0
		0,				// Array of doubles containing difference between original and moved points
		cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03), 
		flags );
	flags |= CV_LKFLOW_PYR_A_READY;	// Pyramid for first frame has already been calculated
	for( index = newNumPoints = 0; index < numPoints; index++ )
	{
		// If have new points, add new point
		if( hasNewPoint )
		{
			// Calculate distance from other points
			double dx = point.x - points[1][index].x;
			double dy = point.y - points[1][index].y;

			// Skip if point is too close to another point
			if( dx*dx + dy*dy <= 25 )
			{
				hasNewPoint = false;
				continue;
			}
		}

		// Remove missing points
		if( !status[index] )
			continue;
		points[1][newNumPoints++] = points[1][index];

		// Draw each point
		cvCircle( image, cvPointFrom32f(points[1][index]), 3, CV_RGB(0,255,0), -1, 8,0);
	}
	numPoints = newNumPoints;
}

// Returns the current number of tracking points
int
LKTracker::getNumPoints(){
	return numPoints;
}

// Automatically find good points to track
void 
LKTracker::autoFindPoints()
{
    /* automatic initialization */
	int i;	
	// FIXME Initialize only once
	IplImage* eig = cvCreateImage( cvGetSize(grey), 32, 1 );
	IplImage* temp = cvCreateImage( cvGetSize(grey), 32, 1 );
	// FIXME Move to constants?
	const double quality = 0.01;
	const double min_distance = 10;

	numPoints = MAX_COUNT;

	// Set ROI to only the face region (needs to be set on all images)
	cvSetImageROI(grey, *ROI);
	cvSetImageROI(eig, *ROI);
	cvSetImageROI(temp, *ROI);

	cvGoodFeaturesToTrack( 
		grey,				// Input image
		eig,				// Temp image
		temp,				// Another temp image
		points[1],			// Output of detected corners
		&numPoints,			// Output of number of detected corners
		quality,			// Min accepted quality
		min_distance,		// Min distance between accepted corners
		NULL,				// Mask - Region of interest
							// consider using getSubRect to refine search area
		3,					// Size of averaging block
		0,					// Use harris if nonzero
		0.04 );				// Parameter only if harris!=0
	// reset ROI
	cvResetImageROI(grey);
	// Move detected point locations relative to the ROI
	for(i=0;i<numPoints;i++)
	{
		points[1][i].x += ROI->x;
		points[1][i].y += ROI->y;
	}

	cvFindCornerSubPix( grey, points[1], numPoints,
		cvSize(WIN_SIZE,WIN_SIZE), cvSize(-1,-1),
		cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
	cvReleaseImage( &eig );
	cvReleaseImage( &temp );
	hasNewPoint = false;
}

// Detect features on a new frame
CvRect*
LKTracker::detect(const IplImage *frame)
{
	if(!image)
	{
		// init image 
		init(frame);
	}
	// copy frame to image
	cvCopy(frame, image, 0);
	// Convert image to greyscale
	cvCvtColor(image, grey, CV_BGR2GRAY);
	if(!initialized)
	{
		autoFindPoints();
	}else if(numPoints > 0) // If has points to track
	{
		setCount();
	}

	// If has new point to add and does not have max points
	if( hasNewPoint && numPoints < MAX_COUNT )
	{
		// Add new point
		points[1][numPoints++] = cvPointTo32f(point);
		// Refine corner location
		cvFindCornerSubPix( 
			grey,		// Image input
			points[1] + numPoints - 1,	// Initial corner input and refined corner output 
			1,			// Number of corners
			cvSize(WIN_SIZE,WIN_SIZE), // Half the size length of the search window
			cvSize(-1,-1), // Do not use zero_zone
			cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
		hasNewPoint = false;
	}

	CV_SWAP( prevGrey, grey, swapImage );
	CV_SWAP( prevPyramid, pyramid, swapImage );
	CV_SWAP( points[0], points[1], swapPoints );
	initialized = true;
	cvShowImage( LK_TRACKER_WINDOW, image );
	return NULL;
}

// mouseCallback sets the onMouse event as a mouse callback function.
void
LKTracker::mouseCallback(int event, int x, int y, int flags, void *param)
{
	((LKTracker*)param)->onMouse(event, x, y);
}