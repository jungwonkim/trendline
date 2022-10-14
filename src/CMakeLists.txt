set(APP tl)

set(TRENDLINE_SOURCES
  Command.cpp
  CommandAggregate.cpp
  CommandStat.cpp
  CommandRecord.cpp
  Data.cpp
  Main.cpp
  Platform.cpp
  PMU.cpp
  Printer.cpp
  Sampler.cpp
  Thread.cpp
  Timer.cpp
)

add_executable(${APP} ${TRENDLINE_SOURCES})

add_compile_options(-Wall -Wextra)
set(CMAKE_CXX_FLAGS "-Wall")

target_link_libraries(${APP} "-pthread")

install(TARGETS ${APP} DESTINATION bin)
