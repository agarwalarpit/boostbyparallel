BoostByParallel
===============

The plugins provided by the APIs of this code will boost the performance of matrix operations by using OpenCL. 


<h1> Introduction </h1> 
The framework designed is to use the underlying GPU hardware available on your computer, to boost the performance of any piece of code, where parallelization is possible. API support for C/C++ would be provided first, and support for python will follow.  

The framework is undergoing development, is in the pre-alpha phase, and is available as per the University of Illinois/NCSA Open Source License. 

Author: ASquared.  

<h1> How to run </h1> 
The framework can now be build on a mac/linux/windows machine, using the cmake tool. However, a GPU would be required with OpenCL support. 

Please make sure that the following libraries/tools are already installed: 
		
		1. OpenCL (With API support for NVIDIA GPU/AMD GPU/Intel GPU) 
		2. cmake
		3. <Please add here, if I am missing something>

The following steps are required to run the kernel code on the GPU, on your machine: 

		1. Clone the boostbyparallel directory on the destination folder on local machine. 
		2. cd boostbyparallel
		3. mkdir build
		4. cd build
		5. cmake ../src/
		6. make
		7. ./boostbyparallel 

If all the above steps go through, you'll run the sample kernel code on the GPU. 

<h2> Sample code explanation </h2> 
Takes as input 

		n = 10, 
		vector-a: 0, 1, 2, ..., 9. 
		vector-b: 0, 2, 4, ..., 18. 

Output vector c is expected to be: 

		vector-c[i] = vector-a[i] + vector-b[i] 

At the end, average of all elements of vector-c will also be printed out. 

Kernels for the parallelization software are provided in the folder named, *./kernels*. 

 
 
