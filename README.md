BoostByParallel
===============

The plugins provided by the APIs of this code will boost the performance of matrix operations by using OpenCL. 


<h1> Introduction </h1> 
The framework designed is to use the underlying GPU hardware available on your computer, to boost the performance of any piece of code, where parallelization is possible. API support for C/C++ would be provided first, and support for python will follow.  

The framework is undergoing development, is in the pre-alpha phase, and is available as per the University of Illinois/NCSA Open Source License. 

Author: ASquared.  

<h1> How to run on mac/linux os </h1> 
The framework can now be build on a mac/linux machine, using the cmake tool. Please make sure that the following libraries/tools are already installed: 
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
		vector-c: vector-a[i] + vector-b[i] 

At the end, average of all elements of vector-c will also be printed out. 

<h1> How to run (Windows with VS-10) </h1> 
The framework was started using the Visual Studio IDE, hence the build directory. Additional support and information will be provided soon, on how to run and setup the framework on any computer with the required hardware support. For those who are running Visual Studio 10, on a 64 bit machine, they can do the following steps: 

		1. Clone the boostbyparallel directory on to the destination folder on your local machine. 
		2. Run the clTut.sln file. This will open up visual studio.
		3. Don't forget to change the filepath for the vecAdd.cl file, in src/main.cpp 
		3. Click on debug, or press F5 to run the code. 

Kernels for the parallelization software are provided in the folder named, *./kernels*. 

 
 
