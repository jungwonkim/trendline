#ifndef YAMP_SRC_PLATFORM_H
#define YAMP_SRC_PLATFORM_H

namespace yamp {

class Timer;

class Platform {
private:
  Platform();
  ~Platform();

public:
  int Init(int* argc, char*** argv);
  int Finalize();
  int Run();

  Timer* timer() { return timer_; }
  double Now();

public:
  static Platform* GetPlatform();

private:
  int* argc_;
  char*** argv_;
  bool init_;
  bool finalize_;

  Timer* timer_;

private:
  static Platform* singleton_;

};

} /* namespace yamp */

#endif /* YAMP_SRC_PLATFORM_H */
