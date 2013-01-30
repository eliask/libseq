CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(libseq)
subdirs(src)

# Make sure we have Boost
FIND_PACKAGE(Boost 1.35.0 REQUIRED)
MESSAGE(STATUS "Found Boost include directory at ${Boost_INCLUDE_DIRS}")

# Set our global include files search path
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

SET(CMAKE_CXX_FLAGS "-std=c++11")
