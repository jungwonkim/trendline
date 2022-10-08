#ifndef YAMP_SRC_THREAD_H
#define YAMP_SRC_THREAD_H

#include <semaphore.h>
#include <pthread.h>

namespace yamp {

class Thread {
public:
  Thread();
  virtual ~Thread();

  void Start();
  virtual void Stop();
  virtual void Sleep();
  virtual void Invoke();

protected:
  virtual void Run() = 0;

protected:
  static void* ThreadFunc(void* argp);

protected:
  pthread_t thread_;
  volatile bool running_;
  sem_t sem_;
};

} /* namespace yamp */

#endif /* YAMP_SRC_THREAD_H */
