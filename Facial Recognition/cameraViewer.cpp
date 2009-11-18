/**
 * Camera Viewer beta prototype.
 *
 * This program compares two different facial detection algorithms.  One uses
 * a classifier file to identify faces and the other uses color selection.
 * To track with color selection, select an area in with Skin Detect window
 * using the mouse.
 * To exit, press the esc key.
 *
 * Known Issue: getting/setting fps does not work in openCV 1.1a.
 *
 * @author Brian Blonski
 * @version 1.$Rev$
 **/

#include "resource.h"

//C:\Program Files (x86)\OpenCV\data\haarcascades\haarcascade_frontalface_alt.xml

/* Entry Point for Program */
int main(int argc, char* argv[])
{
	/* Create new camera capture */
	CamCapture *cam = new CamCapture();

	/* Determine Haar cascade location */
	char* _cascadeName = new char[100];
	memset(_cascadeName, 0, 100);
	strcat_s(_cascadeName, 100, HAARCASCADE_DIR);
	strcat_s(_cascadeName, 100, HAARCASCADE_FRONTALFACE);
	CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*)cvLoad( _cascadeName);
	delete _cascadeName;

	/* Init new trackers */
	HaarTracker* haar = new HaarTracker(cascade);
	SkinTracker* skin = new SkinTracker();
	LKTracker* lk = new LKTracker();

	/* Tracking loop */
	while(true)
	{
		try
		{
			/* Get frame frome camera */
			IplImage *tmp = cam->getFrame();
			if(tmp == NULL)
				break;

			cvShowImage(MAIN_WINDOW, tmp);
			lk->detect(tmp);
			/*
			CvRect* r = haar->detect(tmp);
			if(r)
				skin->select(r);
			skin->detect(tmp);
			*/
			cvReleaseImage(&tmp);
			//free(r);
		}catch (...)
		{
			cout << "Error";
		}
	}
	cvReleaseHaarClassifierCascade(&cascade);
	delete haar;
	delete skin;
	delete cam;
    return 0;
}

#ifdef _EiC
main(1,"cameraViewer.c");
#endif