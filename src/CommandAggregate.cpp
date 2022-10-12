#include "CommandAggregate.h"
#include "Debug.h"
#include "Data.h"
#include "Type.h"
#include "PMU.h"
#include "Sampler.h"
#include "Timer.h"
#include "Platform.h"
#include "Printer.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

namespace trendline {

CommandAggregate::CommandAggregate(int argc, char** argv) : Command(argc, argv) {
  aggr_ = 1;
  skip0_ = 0;
  skip1_ = 0;

  fp_ = stderr;
  data_ = new Data();
}

CommandAggregate::~CommandAggregate() {
  delete data_;
}

int CommandAggregate::Init() {
  return InitOptions();
}

int CommandAggregate::Run() {
  char* filename = argv_[optind + 1];
  _info("filename[%s] aggr[%d] skip_begin[%d] skip_end[%d]", filename, aggr_, skip0_, skip1_);
  FILE* fp = fopen(filename, "r");

  trendline_row row;

  int nevents = 0;
  int lines = 0;
  char* line = NULL;
  size_t len = 0;
  while (getline(&line, &len, fp) != -1) {
    if (strncmp("TIME", line, 4) == 0) {
      nevents = 0;
      for (int i = 0; i < len; i++) if (line[i] == ',') nevents++;
      fprintf(fp_, "%s", line);
      lines = 0;
      Data::ClearRow(&row);
    } else {
      char* s = NULL;
      char* rest = line;
      row.time = strtod(strtok_r(rest, ",", &rest), NULL);
      for (int i = 0; i < nevents; i++) {
        row.data[i] += atoi(strtok_r(rest, ",", &rest));
      }
      if (++lines % aggr_ == 0) {
        fprintf(fp_, "%.5f", row.time);
        for (int j = 0; j < nevents; j++) {
          fprintf(fp_, ",%lld", row.data[j]);
        }
        fprintf(fp_, "\n");
        Data::ClearRow(&row);
      }
    }
  }

  fclose(fp);

  fflush(fp_);
  return TRENDLINE_OK;
}

int CommandAggregate::InitOptions() {
  int opt;
  while ((opt = getopt(argc_, argv_, "a:s:o")) != -1) {
    switch (opt) {
      case 'a':
        aggr_ = atoi(optarg);
        break;
      case 's': {
        char* rest = optarg;
        char* skip = strtok_r(rest, ",", &rest);
        skip0_ = skip ? atoi(skip) : 0;
        skip = strtok_r(rest, ",", &rest);
        skip1_ = skip ? atoi(skip) : 0;
        break;
      }
      case 'o':
        csv_ = true;
        break;
      default:
        return TRENDLINE_ERR;
    }
  }
  return TRENDLINE_OK;
}

} /* namespace trendline */
