#include "maincontroller.h"
#include "gpu_info.h" 

#ifndef _CLLIBRARY_
#define _CLLIBRARY_

class CLLibrary {
public:
	cl_uint platformIdCount;
	std::vector<cl_platform_id> platformIds; 
	cl_uint deviceIdCount;
	std::vector<cl_device_id> deviceIds; 
	cl_int error; 
	cl_program program; 
	cl_kernel kernel; 
	cl_command_queue queue; 

	cl_context context;
	BOOL status; 

	CLLibrary(); 
	~CLLibrary(); 
	void createContext(cl_platform_id platform_id); 
	void CheckError (cl_int error); 
	void CheckError (cl_int error, string err_message);
  	std::string loadKernel (const char* name);
	void createProgram (const std::string& source, cl_context context);
	cl_program buildProgram(const char* name); 
	void createKernel(const char* name); 
	void createQueue(); 
};

#endif
