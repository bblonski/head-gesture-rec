// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _OPEN_CV_INCLUDES_H
#define _OPEN_CV_INCLUDES_H

#ifndef _EiC
#include "cv.h"
#include "highgui.h"
#endif

#include <stdio.h>
#include <ctype.h>
#include <string>

#ifdef _WINDOWS_
    #include <direct.h>
#else
    #include <unistd.h>
    #define _getcwd getcwd
#endif

using namespace std; 

#endif
