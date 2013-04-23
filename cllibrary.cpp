#include "cllibrary.h"

void CLLibrary::createQueue() {
	queue = clCreateCommandQueue(context, deviceIds[0], 0, &error);
}

void CLLibrary::createKernel(const char* name) {
	kernel = clCreateKernel(program, name, &error);
	CheckError(error); 
}

std::string CLLibrary::loadKernel (const char* name)
{
        std::ifstream in (name);
        std::string result (
                (std::istreambuf_iterator<char> (in)),
                std::istreambuf_iterator<char> ());
        return result;
}

void CLLibrary::createProgram (const std::string& source, cl_context context)
{
        // http://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/clCreateProgramWithSource.html
        size_t lengths [1] = { source.size () };
        const char* sources [1] = { source.data () };

        cl_int error = 0;
        program = clCreateProgramWithSource (context, 1, sources, lengths, &error);
        CheckError (error);
}

cl_program CLLibrary::buildProgram(const char* name) {
	createProgram(loadKernel(name), context); 
	/** TODO: The fourth argument is some random value filled in just now. Have to understand the importance of the argument later **/
	clBuildProgram(program, deviceIdCount, deviceIds.data(), "-D FILTER_SIZE=1", nullptr, nullptr);
	return program; 
}

void CLLibrary::createContext(cl_platform_id platform_id) {

	// http://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/clCreateContext.html
	const cl_context_properties contextProperties [] = {
		CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties> (platform_id),
            0, 0
    };
		
	error = CL_SUCCESS;
    context = clCreateContext (contextProperties, deviceIdCount, deviceIds.data (), nullptr, nullptr, &error);
    CheckError (error);
    std::cout << "Context created" << std::endl;
}

void CLLibrary::CheckError (cl_int in_error)
{
		if (in_error != CL_SUCCESS) {
				std::cerr << "OpenCL call failed with error " << error << std::endl;
				status = BOOL::False; 
				std::exit (1);
		} 
}

CLLibrary::~CLLibrary() {
	//Delete all the vectors and dynamically allocated variables.
	delete program; 
	delete kernel; 
	delete queue; 
	delete context; 
}

CLLibrary::CLLibrary() {
	platformIdCount = 0;
	clGetPlatformIDs(0, nullptr, &platformIdCount);
	if (platformIdCount == 0) {
            std::cerr << "No OpenCL platform found" << std::endl;
            status = BOOL::False;
    } else {
            std::cout << "Found " << platformIdCount << " platform(s)" << std::endl;
    }

	std::vector<cl_platform_id> tempPlatformIds (platformIdCount);
	platformIds = tempPlatformIds; 
	clGetPlatformIDs (platformIdCount, platformIds.data (), nullptr);
	for (cl_uint i = 0; i < platformIdCount; ++i) {
            std::cout << "\t (" << (i+1) << ") : " << GetPlatformName (platformIds [i]) << std::endl;
    }

	deviceIdCount = 0;
	clGetDeviceIDs (platformIds [0], CL_DEVICE_TYPE_CPU, 0, nullptr,
            &deviceIdCount);
	if (deviceIdCount == 0) {
            std::cerr << "No OpenCL devices found" << std::endl;
            status = BOOL::False;
    } else {
            std::cout << "Found " << deviceIdCount << " device(s)" << std::endl;
    }

	std::vector<cl_device_id> tempDeviceIds (deviceIdCount);
	deviceIds = tempDeviceIds; 
	clGetDeviceIDs (platformIds [0], CL_DEVICE_TYPE_ALL, deviceIdCount,
                deviceIds.data (), nullptr);

	for (cl_uint i = 0; i < deviceIdCount; ++i) {
            std::cout << "\t (" << (i+1) << ") : " << GetDeviceName (deviceIds [i]) << std::endl;
    }
}
