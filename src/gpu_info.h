#include "maincontroller.h"

#ifndef _GPU_INFO_
#define _GPU_INFO_

std::string GetPlatformName (cl_platform_id id); 
std::string GetDeviceName (cl_device_id id); 
void print_device_info(vector<cl_device_id> deviceIds); 
void print_platform_info(vector<cl_platform_id> platformIds); 

#endif
