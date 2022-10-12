#ifndef TRENDLINE_SRC_COMMAND_H
#define TRENDLINE_SRC_COMMAND_H

#define TRENDLINE_COMMAND_STAT       1
#define TRENDLINE_COMMAND_RECORD     2
#define TRENDLINE_COMMAND_CSV        3

namespace trendline {

class Command {
public:
  Command(int argc, char** argv);
  virtual ~Command();

  virtual int Init() = 0;
  virtual int Run() = 0;

  int type() { return type_; }

public:
  static Command* CreateCommand(const char* cmd, int argc, char** argv);

protected:
  int argc_;
  char** argv_;

private:
  int type_;

};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_COMMAND_H */
