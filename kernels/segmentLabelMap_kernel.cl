
#ifdef cl_khr_fp64
    #pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)
    #pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
    //#error "Double precision floating point not supported by OpenCL implementation."
#endif

#define g_nXRes 640
#define g_nYRes 480

void helperFunction(int newX, int newY, int newZ); 

__kernel 
void segmentLabelMap_kernel(  __global int **map, unsigned short *pDepth)                    
{                                                               
    //Get our global thread ID                                  
    const unsigned int id = get_global_id(0);                                  

	int nX = (int) id/640; 
	int nY = id % 640; 
	int nZ = pDepth[id]
	
	int newX, newY, newZ; 
	newX = (nX - g_nXRes/2)*localCam.fovH/g_nXRes*nZ;
	newY = -(nY - g_nYRes/2)*localCam.fovV/g_nYRes*nZ;
	newZ = nZ; 

	map[nY][nX] = helperFunction(newX, newY, newZ); 
}

void helperFunction(int newX, int newY, int newZ) {
	SimplePoint newPoint; 
	newPoint.x = newX; 
	newPoint.y = newY; 
	newPoint.z = newZ; 

	return findSegmentLabel(&newPoint, 0); 
}
