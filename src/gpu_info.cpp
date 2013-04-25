#include "gpu_info.h"

using namespace std; 

void print_device_info(vector<cl_device_id> deviceIds) {
	for_each(deviceIds.begin(), deviceIds.end(), GetDeviceName); 
}

void print_platform_info(vector<cl_platform_id> platformIds) {
	for_each(platformIds.begin(), platformIds.end(), GetPlatformName);
}	

std::string GetPlatformName (cl_platform_id id)
{
        size_t size = 0;
        clGetPlatformInfo (id, CL_PLATFORM_NAME, 0, NULL, &size);

        std::string result;
        result.resize (size);
        clGetPlatformInfo (id, CL_PLATFORM_NAME, size,
                const_cast<char*> (result.data ()), NULL);

		cout << "Platform: " << result << endl; 
        return result;
}

std::string GetDeviceName (cl_device_id id)
{
        size_t size = 0;
        clGetDeviceInfo (id, CL_DEVICE_NAME, 0, NULL, &size);

        std::string result;
        result.resize (size);
        clGetDeviceInfo (id, CL_DEVICE_NAME, size,
                const_cast<char*> (result.data ()), NULL);

		cout << "Device: " << result << endl; 
        return result;
}
