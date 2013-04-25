CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(boostbyparallel)

# First find all the related packages. 
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)
FIND_PACKAGE(OpenCL REQUIRED)

# Next, all the directories to be inlcuded. 
INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

# Then set the flags and properties of the project. 
SET(CMAKE_CXX_FLAGS "-g -Wall")
SET(CORELIBS ${OPENCL_LIBRARY} M)
SET(PROGRAMS cllibrary gpu_info vecOp)
#AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} PROGRAMS)

foreach(program ${PROGRAMS})
	ADD_LIBRARY(${program} ${program}.cpp)
endforeach(program)

SET(PROGLIBS cllibrary gpu_info vecOp)

# Now that everything is set, we now make the executables and link the libraries. 
ADD_EXECUTABLE(boostbyparallel maincontroller.cpp)
TARGET_LINK_LIBRARIES(boostbyparallel ${CORELIBS} ${PROGLIBS}) 

