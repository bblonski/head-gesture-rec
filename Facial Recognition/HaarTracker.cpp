#include "HaarTracker.h"


const char* const HaarTracker::HAAR_CLASSIFIER_WINDOW = "Haar Classifier";
const char* const HaarTracker::HAARCASCADE_DIR = "C:\\Program Files (x86)\\OpenCV2.0\\data\\haarcascades\\";
const char* const HaarTracker::HAARCASCADE_EYE = "haarcascade_eye_tree_eyeglasses.xml";
const char* const HaarTracker::HAARCASCADE_PROFILE = "haarcascade_profileface.xml";
const char* const HaarTracker::HAARCASCADE_FRONTALFACE = "haarcascade_frontalface_default.xml";

HaarTracker::HaarTracker()
{
	char cascadeName[100];
	// Determine Haar cascade location
	strcpy_s(cascadeName, HAARCASCADE_DIR);
	strcat_s(cascadeName, HAARCASCADE_FRONTALFACE);
	cascade = (CvHaarClassifierCascade*)cvLoad( cascadeName);
	// Determine Haar cascade location
	strcpy_s(cascadeName, HAARCASCADE_DIR);
	strcat_s(cascadeName, HAARCASCADE_EYE);
	nestedCascade = (CvHaarClassifierCascade*)cvLoad(cascadeName);
	init();
}
HaarTracker::HaarTracker(CvHaarClassifierCascade *pCascade, CvHaarClassifierCascade* pNestedCascade) : 
	cascade(pCascade), nestedCascade( pNestedCascade)
{
	init();
}

HaarTracker::~HaarTracker(void)
{
	cvDestroyWindow(HAAR_CLASSIFIER_WINDOW);
	cvReleaseHaarClassifierCascade(&cascade);
}

// Initializes class
void
HaarTracker::init()
{
	cvNamedWindow(HAAR_CLASSIFIER_WINDOW, CV_WINDOW_AUTOSIZE);
	util = new Utils(200, 200);
	image = NULL;
}

// Detects the location of the face using a haar cascade classifier
CvRect*
HaarTracker::detect(const IplImage* frame)
{
	CvRect* r = new CvRect();
	if(!image)
	{
		image = cvCreateImage(cvGetSize(frame), 8, 3);
		image->origin = frame->origin;
	}
	cvCopyImage(frame, image);
    // Create a new frame based on the input frame
    IplImage* temp = cvCreateImage(cvGetSize(image), 8, 3 );

    // Create two points to represent corners of the face bounding box
    CvPoint pt1, pt2;
    int i;
	storage = cvCreateMemStorage(0);
    // Clear the memory storage which was used before
	cvClearMemStorage( storage );

	// Check whether the cascade has loaded successfully. Else report and error and quit
    if( !cascade )
    {
		image = util->printMsg(image, "ERROR: Could not load classifier cascade\n" );
        throw -1;
    }

    // Find whether the cascade is loaded, to find the faces. If yes, then:
    if( cascade )
    {

        // There can be more than one face in an image. So create a growable sequence of faces.
        // Detect the objects and store them in the sequence
        CvSeq* faces = cvHaarDetectObjects( 
							image,
							cascade, 
							storage,
							1.1, 
							2, 
							CV_HAAR_DO_CANNY_PRUNING,
							cvSize(80, 80));

        // Loop the number of faces found.
        //for( i = 0; i < (faces ? faces->total : 0); i++ )
		// only loop on the first face
		for( i = 0; i < (faces && faces->total ? 1 : 0); i++ )
        {
           // Create a new rectangle for drawing the face
            memcpy(r,(CvRect*)cvGetSeqElem( faces, i ),sizeof(CvRect));

            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x;
            pt2.x = (r->x+r->width);
            pt1.y = r->y;
            pt2.y = (r->y+r->height);
			frame = util->printCoordinates(image, r->x + 0.5*r->width, r->y + 0.5*r->height);

            // Draw the rectangle in the input image
            cvRectangle( image, pt1, pt2, CV_RGB(255,0,0), 3, 8, 0 );
        }
		if (faces->total > 0 && nestedCascade)
		{
			CvMat small_img_roi;
			CvPoint center;
			CvScalar color = {{0, 255, 0}};
			int radius;
			int j;
			points.clear();
			cvGetSubRect(frame, &small_img_roi, *r);
			CvSeq* nestedObjects = cvHaarDetectObjects(&small_img_roi, nestedCascade, storage, 2, 2, CV_HAAR_DO_CANNY_PRUNING);
			for (j = 0; j < (nestedObjects ? nestedObjects->total : 0); j++)
			{
				CvRect *nr = (CvRect*)cvGetSeqElem(nestedObjects, j);
				center.x = cvRound((r->x + nr->x + nr->width * 0.5));
				center.y = cvRound((r->y + nr->y + nr->height * 0.5));
				radius = cvRound((nr->width + nr->height) * 0.25);
				cvCircle(image, center, radius, CV_RGB(0, 0, 255), 3, 8, 0);
				points.push_back(center);
			}
		}else
		{
			free(r);
			r = NULL;
		}

    }
	
	cvShowImage(HAAR_CLASSIFIER_WINDOW, image);
    // Release the temp image created.
    cvReleaseImage( &temp );
	cvReleaseMemStorage( &storage );
	return r;
}

// Returns an array of points for the locations of the subfeatures.
vector<CvPoint>
HaarTracker::getPoints()
{
	return points;
}

