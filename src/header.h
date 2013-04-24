#ifndef _HEADER_
#define _HEADER_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h> 

#ifdef __APPLE__
        #include "OpenCL/opencl.h"
#else
        #include "CL/cl.h"
#endif

typedef enum {False, True} BOOL; 

struct Image
{
        std::vector<char> pixel;
        int width, height;
};

using namespace std;

#endif
