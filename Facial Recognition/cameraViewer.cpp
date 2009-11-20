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

// Entry Point for Program
int main(int argc, char* argv[])
{
	// Create new camera capture
	CamCapture *cam = new CamCapture();

	// Init new trackers
	HaarTracker* haar = new HaarTracker();
	SkinTracker* skin = new SkinTracker();
	LKTracker* lk = new LKTracker();
	
	CvRect* r = NULL;
	// Tracking loop
	while(true)
	{
		try
		{
			// Get frame frome camera
			IplImage *tmp = cam->getFrame();
			if(tmp == NULL)
				break;

			cvShowImage(CamCapture::MAIN_WINDOW, tmp);
			lk->detect(tmp);
			if(!r)
				r = haar->detect(tmp);
			else
				haar->detect(tmp);

			if(r)
			{
				skin->select(r);
				lk->select(r);
			}

			skin->detect(tmp);
			
			cvReleaseImage(&tmp);
			free(r);
		}catch (...)
		{
			cout << "Error";
		}
	}
	delete haar;
	delete skin;
	delete cam;
    return 0;
}

#ifdef _EiC
main(1,"cameraViewer.c");
#endif