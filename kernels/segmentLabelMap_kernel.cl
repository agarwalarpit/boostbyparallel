
#ifdef cl_khr_fp64
    #pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)
    #pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
    //#error "Double precision floating point not supported by OpenCL implementation."
#endif

#include "XnTypes.h"

#define g_nXRes 640
#define g_nYRes 480

void findDistToSegment(QVector3D &myPoint, int label); 
double distToCylinder(QVector3D &myPoint, QVector3D &origin, QVector3D &upperFaceCenter, double alpha); 
void helperFunction(int newX, int newY, int newZ); 
void findSegmentLabel(SimplePoint *ptr, int labelSuggestion); 

__kernel 
void segmentLabelMap_kernel(  __global int **map, int fovH, int fovV, unsigned short *pDepth)                    
{                                                               
    //Get our global thread ID                                  
    const unsigned int id = get_global_id(0);                                  

	int nX = (int) id/640; 
	int nY = id % 640; 
	int nZ = pDepth[id]
	
	int newX, newY, newZ; 
	newX = (nX - g_nXRes/2)* fovH /g_nXRes*nZ;
	newY = -(nY - g_nYRes/2)* fovV /g_nYRes*nZ;
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

int findSegmentLabel(SimplePoint *ptr, int labelSuggestion) {

	QVector3D myPoint(ptr->x, ptr->y, ptr->z);
	int myLabel = labelSuggestion; 
	double minDist = findDistToSegment(myPoint, labelSuggestion); 

	if (minDist == 0) {
		return myLabel; 
	}

	double curDist; 
	for (int i=0; i<10; i++){
		if (i == labelSuggestion) continue; 

		curDist = findDistToSegment(myPoint, i); 
		if (minDist > curDist) {
			myLabel = i; 
			minDist = curDist; 
		}

		if (minDist == 0) break; 
	}
	return myLabel; 
}

void findDistToSegment(QVector3D &myPoint, int label) {

	double dist = 0; 
	QVector3D origin, upperFaceCenter; 

	switch(label) {
		case 0:
			dist = distToCyllinder(myPoint,skeletonQVec[XN_SKEL_NECK], skeletonQVec[XN_SKEL_HEAD], 0.2); break; 
		case 1: 
			origin = 0.5*(skeletonQVec[XN_SKEL_LEFT_HIP] + skeletonQVec[XN_SKEL_RIGHT_HIP]);
			upperFaceCenter = 0.5*(skeletonQVec[XN_SKEL_LEFT_SHOULDER] + skeletonQVec[XN_SKEL_RIGHT_SHOULDER]);
			dist = distToCylinder(myPoint, origin, skeletonQVec[XN_SKEL_NECK], 0.2);
			break;
		case 2:
			dist = distToCylinder(myPoint, skeletonQVec[XN_SKEL_LEFT_SHOULDER], skeletonQVec[XN_SKEL_LEFT_ELBOW], 0.2);
			break; 
		case 3:
			dist = distToCylinder(myPoint, skeletonQVec[XN_SKEL_LEFT_HAND], skeletonQVec[XN_SKEL_LEFT_ELBOW], 0.2);
			break;
		case 4:
			dist = distToCylinder(myPoint, skeletonQVec[XN_SKEL_RIGHT_SHOULDER], skeletonQVec[XN_SKEL_RIGHT_ELBOW], 0.2);
			break; 
		case 5:
			dist = distToCylinder(myPoint, skeletonQVec[XN_SKEL_RIGHT_HAND], skeletonQVec[XN_SKEL_RIGHT_ELBOW], 0.2);
			break; 
		case 6:
			dist = distToCylinder(myPoint, skeletonQVec[XN_SKEL_LEFT_HIP], skeletonQVec[XN_SKEL_LEFT_KNEE], 0.2);
			break;
		case 7:
			dist = distToCylinder(myPoint, skeletonQVec[XN_SKEL_LEFT_FOOT], skeletonQVec[XN_SKEL_LEFT_KNEE], 0.2);
			break; 
		case 8:
			dist = distToCylinder(myPoint, skeletonQVec[XN_SKEL_RIGHT_HIP], skeletonQVec[XN_SKEL_RIGHT_KNEE], 0.2);
			break; 
		case 9:
			dist = distToCylinder(myPoint, skeletonQVec[XN_SKEL_RIGHT_FOOT], skeletonQVec[XN_SKEL_RIGHT_KNEE], 0.2);
			break; 
	};

	return dist; 
}

double distToCylinder(QVector3D & myPoint, QVector3D & origin, QVector3D & upperFaceCenter, double alpha)
{
	QVector3D central = upperFaceCenter - origin;
	
	//Parameters for the cylinder
	double H = central.length();
	QVector3D hUnitVec = central.normalized();
	double R = alpha*H;
	
	//Find the coordinates in cylinder system
	double h = QVector3D::dotProduct(myPoint-origin, hUnitVec);
	double r = myPoint.distanceToLine(origin, hUnitVec);

	double distH, distR;

	if(h<0) {
		distH = h;
	}
	else if( h<= H) {
		distH = 0;
	}
	else {
		distH = h - H;
	}

	if(r<R)
		distR = 0;
	else
		distR = r-R;

	return distR*distR + distH*distH;
}

