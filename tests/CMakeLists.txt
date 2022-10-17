include_directories(${PROJECT_SOURCE_DIR}/src)

macro(trendline_test arg)
    add_executable(${arg} ${arg}.cpp)
    target_link_libraries(${arg} trendline pthread)
endmacro(trendline_test)

add_subdirectory(01_pmu)

