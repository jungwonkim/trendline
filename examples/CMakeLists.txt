include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_C_FLAGS "-O0")

add_executable(saxpy saxpy.c)
add_executable(sgemv sgemv.c)
add_executable(sgemm sgemm.c)

add_executable(daxpy daxpy.c)
add_executable(dgemv dgemv.c)
add_executable(dgemm dgemm.c)

add_executable(dgemm-marker dgemm-marker.c)
target_link_libraries(dgemm-marker trendline pthread)
