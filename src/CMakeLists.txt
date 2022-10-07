set(YAMP_SOURCES
  Data.cpp
  Main.cpp
  Printer.cpp
  Sampler.cpp
  Timer.cpp
)

add_executable(yamp ${YAMP_SOURCES})

install(TARGETS yamp DESTINATION bin)
