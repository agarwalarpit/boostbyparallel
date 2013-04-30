CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
add_executable( convolution Convolution.cpp )

# First find all the related packages.
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)
FIND_PACKAGE(OpenCL REQUIRED)
SET(CMAKE_CXX_FLAGS "-g -Wall")

target_link_libraries( convolution ${OPENCL_LIBRARIES} )
