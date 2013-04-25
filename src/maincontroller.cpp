#include "maincontroller.h"
#include "image_manipulation.h"
#include "gpu_info.h"
#include "cllibrary.h"
#include "vecOp.h"

using namespace std; 

int main ()
{
	CLLibrary *cll_object = new CLLibrary(); 
	cll_object->createContext(cll_object->platformIds[0]); 
	std::cout << "Context created" << std::endl;
	cll_object->createQueue();
	
	const char* filename = "../kernels/vecAdd.cl";
	cll_object->program = cll_object->buildProgram(filename); 
	cll_object->createKernel("vecAdd"); 
	
	
	size_t globalSize, localSize;
    
    // Number of work items in each local work group
    localSize = 64;
 
	int *h_a; 
	int *h_b; 
	int *h_c; 

	int n = 10; 
	size_t bytes = n * sizeof(int); 

/** This initialization of input vectors h_a, h_b is not required in the real applications. 
It would be done by the calling function. However, h_c has to be initliazed in this function. 
**/ 
	h_a = (int *) malloc(bytes); 
	h_b = (int *) malloc(bytes); 
	h_c = (int *) malloc(bytes); 
    
	for(int i=0; i<n; i++) {
		h_a[i] = i; 
		h_b[i] = 2*i; 
		h_c[i] = 0;
	}


/** Operation object handler's definition. This function is the handler function, all the different 
kinds of inputs, various matrices, and the dimensions, would be input on this function. The decision 
would be taken hereafter, and the results would be returned from this function. 
**/
	VectorOperation *vecOp = new VectorOperation(); 
	vecOp->initializeBuffers(cll_object->context, bytes); 

	cll_object->error = clEnqueueWriteBuffer(cll_object->queue, vecOp->a, CL_TRUE, 0,
                                   bytes, h_a, 0, NULL, NULL);
    cll_object->error |= clEnqueueWriteBuffer(cll_object->queue, vecOp->b, CL_TRUE, 0,
                                   bytes, h_b, 0, NULL, NULL);


	 // Set the arguments to our compute kernel
    cll_object->error  = clSetKernelArg(cll_object->kernel, 0, sizeof(cl_mem), &vecOp->a);
    cll_object->error |= clSetKernelArg(cll_object->kernel, 1, sizeof(cl_mem), &vecOp->b);
    cll_object->error |= clSetKernelArg(cll_object->kernel, 2, sizeof(cl_mem), &vecOp->c);
    cll_object->error |= clSetKernelArg(cll_object->kernel, 3, sizeof(unsigned int), &n);

	// Number of total work items - localSize must be devisor
    globalSize = ceil(n/(float)localSize)*localSize;

	// Execute the kernel over the entire range of the data set  
    cll_object->error = clEnqueueNDRangeKernel(cll_object->queue, cll_object->kernel, 1, NULL, &globalSize, &localSize,
                                                              0, NULL, NULL);

   cll_object->CheckError(cll_object->error); 	
	// Wait for the command queue to get serviced before reading back results
    clFinish(cll_object->queue);

	 // Read the results from the device
    clEnqueueReadBuffer(cll_object->queue, vecOp->c, CL_TRUE, 0, bytes, h_c, 0, NULL, NULL );
	
	double sum = 0;
	cout << std::endl; 

    for(int i=0; i<n; i++) {
		cout << "Matrix c element @ " << i << " is: " << h_c[i] << endl; 
        sum += h_c[i];
	}
    printf("final result: %f\n", sum/(double)n);
 
    //release host memory
    free(h_a);
    free(h_b);
    free(h_c);

	// release OpenCL resources
	vecOp->~VectorOperation(); 
	//	cll_object->~CLLibrary(); 
	
	free(vecOp); 
	free(cll_object); 

    return 0;
		
}
