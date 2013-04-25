#include "cllibrary.h"

#define QUEUE_ON_GPU 1
#define QUEUE_ON_CPU 0

void CLLibrary::createQueue() {
	queue = clCreateCommandQueue(context, deviceIds[0], 0, &error);
	CheckError(error);
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
	string flags_string = "-D FILTER_SIZE=1"; 
	clBuildProgram(program, deviceIdCount, deviceIds.data(), flags_string.c_str(), NULL, NULL);
	return program; 
}

void CLLibrary::createContext(cl_platform_id platform_id) {

	// http://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/clCreateContext.html
	const cl_context_properties contextProperties [] = {
		CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties> (platform_id),
            0, 0
    };
		
	error = CL_SUCCESS;
    context = clCreateContext (contextProperties, deviceIdCount, deviceIds.data (), NULL, NULL, &error);
    CheckError (error);
    std::cout << "Context created" << std::endl;
}

void CLLibrary::CheckError(cl_int in_error, std::string err_message) {
	if (in_error != CL_SUCCESS) {
		cerr << err_message << ": " << in_error << endl;
	   	exit(1); 
	}
}

void CLLibrary::CheckError (cl_int in_error)
{
	if (in_error == CL_SUCCESS) {
		return;  
	}

	switch(in_error) {
		case CL_INVALID_PLATFORM:
		{
			std::cerr << "Invalid platform. Error: " << error << std::endl; 
			std::exit(1); 
		}
		case CL_INVALID_DEVICE_TYPE:
		{
			std::cerr << "Invalide device type found. Error: " << error << std::endl; 
			std::exit(1); 
		}
		case CL_INVALID_VALUE:
		{
			std::cerr << "Invalide value obtained. Error: " << error << std::endl; 
			std::exit(1); 
		}
		case CL_DEVICE_NOT_FOUND:
		{
			std::cerr << "Device not found for OpenCL. Error: " << error << std::endl; 
			std::exit(1); 
		}
		default:
		{
			std::cerr << "Some error: " << error << std::endl; 
			std::exit(1); 
		}
	}
}

CLLibrary::~CLLibrary() {
	//Delete all the vectors and dynamically allocated variables.
//	delete program; 
//	delete kernel; 
//	delete queue; 
//	delete context; 
}

CLLibrary::CLLibrary() {
	platformIdCount = 0;
	deviceIdCount = 0;	
	error = clGetPlatformIDs(0, NULL, &platformIdCount);
	CheckError(error, "clGetPlatformIDs:No opencl platforms found"); 
	error = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU, 0, NULL, &deviceIdCount); 
	CheckError(error, "clGetDeviceIDs: No OpenCL compatible devices found"); 	

	std::vector<cl_platform_id> tempPlatformIds (platformIdCount);
	std::vector<cl_device_id> tempDeviceIds (deviceIdCount);
	platformIds = tempPlatformIds; 
	deviceIds = tempDeviceIds; 
	
	clGetPlatformIDs(platformIdCount, platformIds.data (), NULL);
	clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_CPU, deviceIdCount, deviceIds.data(), NULL); 	
	print_platform_info(platformIds); 
	print_device_info(deviceIds); 
}
