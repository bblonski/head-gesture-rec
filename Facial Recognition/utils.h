#ifndef _UTILS_H
#define _UTILS_H

#include "OpenCVIncludes.h"

class Utils
{
private:
	int xCoordLocation;
	int yCoordLocation;
public:
	Utils(int xCoord, int yCoord);
	Utils(void);
	~Utils(void);
	IplImage *printCoordinates(IplImage *image, double x, double y);
	IplImage *printMsg(IplImage *image, char* string);
	void noCamMsg(void);
};

#endif
