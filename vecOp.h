#include "header.h" 
#include "gpu_info.h"

#ifndef _VECOP_
#define _VECOP_

class VectorOperation {
public:

	cl_mem a;
	cl_mem b;
	cl_mem c;

	/** We have presently assumed, vector a, b and c of the same size = size_t bytes,
	mentioned in the function below **/ 
	void initializeBuffers(cl_context in_context, size_t bytes); 
	~VectorOperation(); 
};

#endif