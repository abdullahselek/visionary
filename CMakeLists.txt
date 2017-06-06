cmake_minimum_required(VERSION 3.0)
project(visionary)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
