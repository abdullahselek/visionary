cmake_minimum_required(VERSION 3.0)
include(../cmake/DownloadProject.cmake)
download_project(PROJ       googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             master
        UPDATE_DISCONNECTED 1
        )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake/)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(../src/)

# Add test cpp file
add_executable(visionary-test main.cpp tests-motiondetector.cpp mock-motion-detector.h utils.h)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(visionary-test gtest gmock_main ${OpenCV_LIBS})
add_test(NAME visionary-test COMMAND visionary-test)
