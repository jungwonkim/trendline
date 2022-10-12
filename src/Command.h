#ifndef YAMP_SRC_COMMAND_H
#define YAMP_SRC_COMMAND_H

#define YAMP_COMMAND_STAT       1
#define YAMP_COMMAND_RECORD     2
#define YAMP_COMMAND_CSV        3

namespace yamp {

class Command {
public:
  Command();
  virtual ~Command();

  virtual int Init(int* argc, char*** argv) = 0;
  virtual int Run() = 0;

  int type() { return type_; }

public:
  static Command* CreateCommand(const char* cmd);

private:
  int type_;

};

} /* namespace yamp */

#endif /* YAMP_SRC_COMMAND_H */
