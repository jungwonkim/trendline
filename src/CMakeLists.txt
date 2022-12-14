option(BUILD_SHARED_LIBS "Build shared libs" OFF)

set(LIB trendline)
set(APP tl)

set(TRENDLINE_SOURCES
  CAPI.cpp
  Command.cpp
  CommandAggregate.cpp
  CommandCorrel.cpp
  CommandHelp.cpp
  CommandList.cpp
  CommandStat.cpp
  CommandRecord.cpp
  Data.cpp
  Platform.cpp
  PMU.cpp
  PMUICX.cpp
  PMUNeoverseV1.cpp
  PMUNeoverseN1.cpp
  Printer.cpp
  Sampler.cpp
  Thread.cpp
  Timer.cpp
)

set(TL_SOURCES
  ${TRENDLINE_SOURCES}
  Main.cpp
)

if (CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
  set(MAX_COUNTERS 6)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  set(MAX_COUNTERS 8)
else()
  message(FATAL_ERROR "NOT SUPPORT ${CMAKE_SYSTEM_PROCESSOR}")
endif()
configure_file(Config.h.in Config.h)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/src)

add_library(${LIB} ${TRENDLINE_SOURCES})
#add_executable(${APP} ${TL_SOURCES})
add_executable(${APP} Main.cpp)
target_link_libraries(${APP} ${LIB})

add_compile_options(-Wall -Wextra)
set(CMAKE_CXX_FLAGS "-Wall")

target_link_libraries(${APP} pthread)

install(TARGETS ${LIB} DESTINATION lib)
install(TARGETS ${APP} DESTINATION bin)
