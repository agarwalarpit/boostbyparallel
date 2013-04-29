#ifndef _HEADER_
#define _HEADER_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h> 
#include <algorithm>    // std::for_each

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
