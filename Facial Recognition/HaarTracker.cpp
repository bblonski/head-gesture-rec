#include "HaarTracker.h"
#include "Utils.h"

HaarTracker::HaarTracker(CvHaarClassifierCascade *pCascade)
{
	cvNamedWindow(HAAR_CLASSIFIER_WINDOW, 1 );
	util = new Utils(20, 200);
	//Load the classifier
	cascade = pCascade;
}

HaarTracker::~HaarTracker(void)
{
	cvDestroyWindow(HAAR_CLASSIFIER_WINDOW);
}

CvRect*
HaarTracker::detect(IplImage *frame)
{
	CvRect* r = new CvRect();
    // Create a new frame based on the input frame
    IplImage* temp = cvCreateImage( cvSize(frame->width,frame->height), 8, 3 );

    // Create two points to represent corners of the face bounding box
    CvPoint pt1, pt2;
    int i;
	storage = cvCreateMemStorage(0);
    // Clear the memory storage which was used before
	cvClearMemStorage( storage );

	// Check whether the cascade has loaded successfully. Else report and error and quit
    if( !cascade )
    {
		frame = util->printMsg(frame, "ERROR: Could not load classifier cascade\n" );
        throw -1;
    }

    // Find whether the cascade is loaded, to find the faces. If yes, then:
    if( cascade )
    {

        // There can be more than one face in an image. So create a growable sequence of faces.
        // Detect the objects and store them in the sequence
        CvSeq* faces = cvHaarDetectObjects( frame, cascade, storage,
                                            1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize(80, 80) );

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
			frame = util->printCoordinates(frame, r->x + 0.5*r->width, r->y + 0.5*r->height);

            // Draw the rectangle in the input image
            cvRectangle( frame, pt1, pt2, CV_RGB(255,0,0), 3, 8, 0 );
        }
		nestedCascade = (CvHaarClassifierCascade*)cvLoad("C:\\Program Files (x86)\\OpenCV\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml");
		if(faces->total > 0 && nestedCascade)
		{
			CvMat small_img_roi;
            CvPoint center;
			CvScalar color = {{0,255,0}};
            int radius, j;
            cvGetSubRect( frame, &small_img_roi, *r );
            CvSeq* nested_objects = cvHaarDetectObjects( &small_img_roi, nestedCascade, storage,
                                        1.1, 2);
            for( j = 0; j < (nested_objects ? nested_objects->total : 0); j++ )
            {
                CvRect* nr = (CvRect*)cvGetSeqElem( nested_objects, j );
                center.x = cvRound((r->x + nr->x + nr->width*0.5));
                center.y = cvRound((r->y + nr->y + nr->height*0.5));
                radius = cvRound((nr->width + nr->height)*0.25);
                cvCircle( frame, center, radius, CV_RGB(0,0,255), 3, 8, 0 );
            }
        }

    }
	
	cvShowImage(HAAR_CLASSIFIER_WINDOW, frame);
    // Release the temp image created.
    cvReleaseImage( &temp );
	cvReleaseMemStorage( &storage );
	return r;
}

