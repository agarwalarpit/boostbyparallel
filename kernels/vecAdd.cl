
#ifdef cl_khr_fp64
    #pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)
    #pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
    //#error "Double precision floating point not supported by OpenCL implementation."
#endif

__kernel 
void vecAdd(  __global int *a, __global int *b, __global int *c, const unsigned int n)                    
{                                                               
    //Get our global thread ID                                  
    const unsigned int id = get_global_id(0);                                  

    //Make sure we do not go out of bounds
    if (id < n) {
		c[id] = a[id] + b[id]; // operator(a[id], b[id]);
	}                                
} 
