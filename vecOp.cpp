#include "vecOp.h" 

void VectorOperation::initializeBuffers(cl_context in_context, size_t bytes) {
	/** Here a, b and c vectors are initialized and memory is allocated to them**/
	a = clCreateBuffer(in_context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
    b = clCreateBuffer(in_context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
    c = clCreateBuffer(in_context, CL_MEM_WRITE_ONLY, bytes, NULL, NULL);

}

VectorOperation::~VectorOperation() {
	clReleaseMemObject(a);
	clReleaseMemObject(b);
    clReleaseMemObject(c);
}