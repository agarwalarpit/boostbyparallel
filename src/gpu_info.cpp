#include "gpu_info.h"

using namespace std; 

std::string GetPlatformName (cl_platform_id id)
{
        size_t size = 0;
        clGetPlatformInfo (id, CL_PLATFORM_NAME, 0, nullptr, &size);

        std::string result;
        result.resize (size);
        clGetPlatformInfo (id, CL_PLATFORM_NAME, size,
                const_cast<char*> (result.data ()), nullptr);

        return result;
}

std::string GetDeviceName (cl_device_id id)
{
        size_t size = 0;
        clGetDeviceInfo (id, CL_DEVICE_NAME, 0, nullptr, &size);

        std::string result;
        result.resize (size);
        clGetDeviceInfo (id, CL_DEVICE_NAME, size,
                const_cast<char*> (result.data ()), nullptr);

        return result;
}