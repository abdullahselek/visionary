cmake_minimum_required(VERSION 3.0)
include(../cmake/DownloadProject.cmake)
download_project(PROJ       googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             master
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
include_directories(../source/)

# Add test cpp file
add_executable(visionary-test main.cpp)
target_link_libraries(visionary-test gtest gmock_main)
add_test(visionary-test visionary-test COMMAND Test)
