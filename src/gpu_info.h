#include "header.h"

#ifndef _GPU_INFO_
#define _GPU_INFO_

std::string GetPlatformName (cl_platform_id id); 
std::string GetDeviceName (cl_device_id id); 

#endif