cmake_minimum_required(VERSION 3.11.0)
project(jchess_engine)

enable_testing()
include(CTest)

message("${CTEST_SOURCE_DIRECTORY}")
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/test)