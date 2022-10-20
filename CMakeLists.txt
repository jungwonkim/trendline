cmake_minimum_required(VERSION 2.8)

option(BUILD_EXAMPLES "Build example applications" ON)

project(TRENDLINE)

add_subdirectory(src)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)
