set(APP yamp)

set(YAMP_SOURCES
  Data.cpp
  Main.cpp
  Platform.cpp
  PMU.cpp
  Printer.cpp
  Sampler.cpp
  Thread.cpp
  Timer.cpp
)

add_executable(${APP} ${YAMP_SOURCES})

target_link_libraries(${APP} "-pthread")

install(TARGETS yamp DESTINATION bin)
