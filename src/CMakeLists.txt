cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake/)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES ../main.cpp)

add_executable(visionary ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
#target_link_libraries(OpenCV ${OpenCV_LIBS})
