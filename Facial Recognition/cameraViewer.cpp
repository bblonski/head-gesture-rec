/**
 * Camera Viewer beta prototype.
 *
 * This program compares two different facial detection algorithms.  One uses
 * a classifier file to identify faces and the other uses color selection.
 * To track with color selection, select an area in with Skin Detect window
 * using the mouse.
 * The program must be given a command line argument to load the face classifier
 * for classifier identification to work.
 * To exit, press the esc key.
 *
 * Known Issue: getting/setting fps does not work in openCV 1.1a.
 *
 * Contains modified code from the OpenCV samples.
 *
 * @author Brian Blonski
 * @version 1.0b
 **/

#include "resource.h"

//C:\Program Files (x86)\OpenCV\data\haarcascades\haarcascade_frontalface_alt.xml

/* Entry Point for Program */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CamCapture *cam = new CamCapture();
	//cascade_name = lpCmdLine;
	HaarTracker* haar = new HaarTracker();
	SkinTracker* skin = new SkinTracker();

	while(true)
	{
		try
		{
			IplImage *tmp = cam->getFrame();
			if(tmp == NULL)
				break;
			cvShowImage(MAIN_WINDOW, tmp);
			CvRect* r = haar->detect(tmp);
			if(r)
				skin->select(r);
			skin->detect(tmp);
			cvReleaseImage(&tmp);
			delete(r);
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