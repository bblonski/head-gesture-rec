// $Id$
// Copyright (c) 2010 by Brian Blonski
#include "SkinDetector.h"
#include "OpenCVIncludes.h"

const char* const SkinDetector::SKIN_FILTER_WINDOW = "Skin Filter";

SkinDetector::SkinDetector(void) : vmin(65), vmax(256), smin(0), hdims(16),
backprojectMode(0), image(0), hsv(0), hue(0), mask(0), backproject(0), 
histImage(0), trackObject(0), showHist(0), selectObject(0)
{
    cvNamedWindow(SKIN_FILTER_WINDOW, 1 );
    cvCreateTrackbar("Vmin", SKIN_FILTER_WINDOW, &vmin, 256, 0);
    cvCreateTrackbar("Vmax", SKIN_FILTER_WINDOW, &vmax, 256, 0);
    cvCreateTrackbar("Smin", SKIN_FILTER_WINDOW, &smin, 256, 0);
    cvSetMouseCallback(SKIN_FILTER_WINDOW,
        &SkinDetector::mouseCallback, this );
}

SkinDetector::~SkinDetector(void)
{
    if(image)
    {
        cvReleaseImage(&image);
        cvReleaseImage(&hsv);
        cvReleaseImage(&hue);
        cvReleaseImage(&mask);
        cvReleaseImage(&backproject);
        cvReleaseHist(&hist);
        cvReleaseImage(&histImage);
    }
    cvDestroyWindow(SKIN_FILTER_WINDOW);
}

/**
* mouseCallback sets the onMouse event as a mouse callback function.
*/
void
SkinDetector::mouseCallback(int event, int x, int y, int flags, void *param)
{
    ((SkinDetector*)param)->onMouse(event, x, y);
}

void
SkinDetector::select(CvRect* r)
{
    if(r != NULL)
        selectFrame = *r;
    if(selectFrame.width > 0 && selectFrame.height > 0)
        trackObject = -1;
}

void
SkinDetector::onMouse(int event, int x, int y)
{
    if(!image)
        return;

    if(image->origin)
        y = image->height - y;

    //Select area when mousebuttn is held down
    if(selectObject)
    {
        selectFrame.x = MIN(x,origin.x);
        selectFrame.y = MIN(y,origin.y);
        selectFrame.width = selectFrame.x + CV_IABS(x - origin.x);
        selectFrame.height = selectFrame.y + CV_IABS(y - origin.y);

        selectFrame.x = MAX(selectFrame.x, 0);
        selectFrame.y = MAX(selectFrame.y, 0);
        selectFrame.width = MIN(selectFrame.width, image->width);
        selectFrame.height = MIN(selectFrame.height, image->height);
        selectFrame.width -= selectFrame.x;
        selectFrame.height -= selectFrame.y;
    }

    switch(event)
    {
    case CV_EVENT_LBUTTONDOWN:
        origin = cvPoint(x, y);
        selectFrame = cvRect(x, y, 0, 0);
        selectObject = 1;
        break;
    case CV_EVENT_LBUTTONUP:
        selectObject = 0;
        if(selectFrame.width > 0 && selectFrame.height > 0)
            trackObject = -1;
        break;
    }
}

void
SkinDetector::init(const IplImage *frame)
{
    float hranges_arr[] = {0, 180};
    float *hranges = hranges_arr;
    /* allocate all the buffers */
    image = cvCreateImage(cvGetSize(frame), 8, 3);
    image->origin = frame->origin;
    hsv = cvCreateImage(cvGetSize(frame), 8, 3);
    hue = cvCreateImage(cvGetSize(frame), 8, 1);
    mask = cvCreateImage(cvGetSize(frame), 8, 1);
    backproject = cvCreateImage(cvGetSize(frame), 8, 1);
    hist = cvCreateHist(1, &hdims, CV_HIST_ARRAY, &hranges, 1);
}

/* Detect the area that matches the seleteced color sample.
* based off OpenCV sample code 
*/
CvRect* 
SkinDetector::detect(const IplImage* frame)
{
    if(!image)
    {
        init(frame);
    }

    cvCopy(frame, image, 0);
    image->origin = frame->origin;
    if(1 == image->origin) // 1 means the image is inverted
    {
        cvFlip(image, 0, 0);
        image->origin = 0;
    }

    //Track if color selection made with mouse callback
    if(trackObject)
    {
        //If first instance of object tracking
        if(trackObject < 0)
        {
            startTracking(image);
        }
        track();
    }

    //Invert colors if selecting
    if(selectObject && selectFrame.width > 0 && selectFrame.height > 0)
    {
        cvSetImageROI(image, selectFrame);
        cvXorS(image, cvScalarAll(255), image, 0);
        cvResetImageROI(image);
    }

    cvShowImage(SKIN_FILTER_WINDOW, image);
    return &selectFrame;
}

void
SkinDetector::updateHueImage()
{
    // Convert to HSV color model
    cvCvtColor(image, hsv, CV_BGR2HSV);

    // Mask out-of-range values
    cvInRangeS(hsv, cvScalar(0, smin, MIN(vmin,vmax), 0),
        cvScalar(180, 256, MAX(vmin,vmax) ,0), mask);

    // Extract the hue channel
    cvSplit(hsv, hue, 0, 0, 0);
}

void 
SkinDetector::track()
{
    CvConnectedComp trackComp;
    // Create a new hue image
    updateHueImage();

    /* calculates the backprojection from the hue */
    cvCalcBackProject(&hue, backproject, hist);
    cvAnd(backproject, mask, backproject, 0);

    shrinkTrackingBox(20);

    /* Finds object center, size, and orientation */
    cvCamShift(backproject, trackFrame, 
        cvTermCriteria(CV_TERMCRIT_EPS|CV_TERMCRIT_ITER, 10, 1 ), &trackComp, 
        &trackBox );

    // Update face location and angle
    trackFrame = trackComp.rect;
    if(!image->origin)
        trackBox.angle = -trackBox.angle;
    //draw ellipse around color area
    cvEllipseBox(image, trackBox, CV_RGB(255,0,0), 3, CV_AA, 0);
    image = Utils::printCoordinates(image, trackFrame.x + 0.5*trackFrame.width,
        trackFrame.y + 0.5*trackFrame.height, cvPoint(20,200));
}

void 
SkinDetector::startTracking(IplImage * pImg)
{
    float maxVal = 0.f;
    // Create a new hue image
    updateHueImage();
    //Perform color analysis
    cvSetImageROI(hue, selectFrame);
    cvSetImageROI(mask, selectFrame);
    cvCalcHist(&hue, hist, 0, mask);
    cvGetMinMaxHistValue(hist, 0, &maxVal, 0, 0);
    cvConvertScale(hist->bins, hist->bins, maxVal ? 255.0 / maxVal : 0, 0);
    cvResetImageROI(hue);
    cvResetImageROI(mask);

    trackFrame = selectFrame;

    trackObject = 1;
}

/// Shrinks tracking frame by specified amount
void 
SkinDetector::shrinkTrackingBox(const int amount)
{
    // shrink tracking box so it doesn't grow
    if(min(trackFrame.height, trackFrame.width) > amount)
    {
        trackFrame.height -= amount;
        trackFrame.width -= amount;
        trackFrame.x += amount/2;
        trackFrame.y += amount/2;
    }
}
