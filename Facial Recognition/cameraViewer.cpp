// $Id$
// Copyright (c) 2010 by Brian Blonski
/**
 * Project: Camera Viewer beta.
 *
 * Description: Tracks head gestures with multiple feature tracking techniques.
 *
 * @author Brian Blonski
 * @version 1.$Rev: 47 $
 * @date $Date: 2009-12-07 01:37:27 -0800 (Mon, 07 Dec 2009) $
**/

#include "resource.h"

//C:\Program Files (x86)\OpenCV\data\haarcascades\haarcascade_frontalface_alt.xml

// Entry Point for Program
int main(int argc, char* argv[])
{
	// Create new camera capture
	CamCapture *cam = new CamCapture();

	// Init new trackers
	HaarTracker* haar = new HaarTracker();
	//SkinTracker* skin = new SkinTracker();
	LKTracker* lk = new LKTracker();
    MotionTracker* motionTracker = new MotionTracker();
    GestureTracker* gestureTracker = new GestureTracker();
	
	CvRect* r = NULL;
	vector<CvPoint> faces;
	int runonce = true;


	// Tracking loop
	while(true)
	{
		/*try
		{*/
			// Get frame frome camera
			IplImage *tmp = cam->getFrame();
			if(tmp == NULL)
				break;

			cvShowImage(CamCapture::MAIN_WINDOW, tmp);

            if(runonce)
			    r = haar->detect(tmp);

			lk->detect(tmp);

			if(r && runonce)
			{
				lk->select(r);
				runonce = false;
            }
            HeadGesture gesture = gestureTracker->track(motionTracker->detect(lk->getPoints(), lk->getNumPoints()));
            if(gesture == nod)
                printf("NOD DETECTED!\n");
            else if(gesture == shake)
                printf("SHAKE DETECTED!\n");
			
			cvReleaseImage(&tmp);
            if(r)
			    free(r);
            r = NULL;
		//}catch (...)
		//{
		//	cerr << "Error";
		//}
	}
	
	delete haar;
	//delete skin;
	delete cam;
    delete lk;
    delete motionTracker;
    delete gestureTracker;
    return 0;
}

#ifdef _EiC
main(1,"cameraViewer.c");
#endif