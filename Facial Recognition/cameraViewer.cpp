// $Id$
/**
 * Project: Camera Viewer beta.
 *
 * Description: Tracks head gestures with multiple feature tracking techniques.
 *
 * @author Brian Blonski
 * @version 1.$Rev$
 * @date $Date$
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

			r = haar->detect(tmp);

			lk->detect(tmp);

			if(r && runonce)
			{
				skin->select(r);
				lk->select(r);
				runonce = false;
			}
			//if(lk->getNumPoints() < 5){
			//faces = haar->getPoints();
			//for (int i = 0 ; i < faces.size(); i++ )
			//	lk->setPoint(faces[i].x, faces[i].y);
			//}
			
			skin->detect(tmp);
			
			cvReleaseImage(&tmp);
			free(r);
		//}catch (...)
		//{
		//	cerr << "Error";
		//}
	}
	
	delete haar;
	delete skin;
	delete cam;
    return 0;
}

#ifdef _EiC
main(1,"cameraViewer.c");
#endif