#pragma OPENCL EXTENSION cl_khr_fp64 : enable

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
