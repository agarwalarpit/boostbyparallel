
/***
Author: Arpit Agarwal 
Input: 2 vectors of size 'n'. 
Output: Vector c, where every element of vector c is the individual sum of items in vector a, and vector b. 
****/ 

__kernel 
void vecAdd(  __global double *a, __global double *b, __global double *c, const unsigned int n)                    
{                                                               
    //Get our global thread ID                                  
    int id = get_global_id(0);                                  

    //Make sure we do not go out of bounds
    if (id < n) {
		c[id] = operator(a[id], b[id]);
	}                                
}      

void operator(int a, int b) {
	return (a + b);
}