#include "CommandAggregate.h"
#include "Debug.h"
#include "Data.h"
#include "Type.h"
#include "Sampler.h"
#include "Timer.h"
#include "Platform.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

namespace trendline {

CommandAggregate::CommandAggregate(int argc, char** argv) : Command(argc, argv) {
  aggr_ = 1;
  skip0_ = 0;
  skip1_ = 0;

  csv_ = false;
  fp_ = stderr;
}

CommandAggregate::~CommandAggregate() {
}

int CommandAggregate::Init() {
  InitOptions();
  inputfile_ = argv_[optind + 1];
  if (!inputfile_) return TRENDLINE_ERR;
  InitPrinterOutput();
  return TRENDLINE_OK;
}

int CommandAggregate::InitPrinterOutput() {
  if (!csv_) return TRENDLINE_OK;
  char filename[256];
  size_t len_prefix = strlen(inputfile_) - strlen(TRENDLINE_LOG_FILENAME_EXT) - 1;
  strncpy(filename, inputfile_, len_prefix);
  sprintf(filename + len_prefix, "-a%d.%s", aggr_, TRENDLINE_LOG_FILENAME_EXT);
  fp_ = fopen(filename, "w");
  return fp_ ? TRENDLINE_OK : TRENDLINE_ERR;
}

int CommandAggregate::Run() {
  FILE* input = fopen(inputfile_, "r");

  trendline_row row;

  int nevents = 0;
  int lines = 0;
  char* line = NULL;
  size_t len = 0;
  while (getline(&line, &len, input) != -1) {
    if (strncmp("TIME", line, 4) == 0) {
      nevents = 0;
      for (size_t i = 0; i < len; i++) {
        if (line[i] == 0) break;
        if (line[i] == ',') nevents++;
      }
      fprintf(fp_, "%s", line);
      lines = 0;
      Data::ClearRow(&row);
    } else {
      if (++lines <= skip0_) continue;
      char* rest = line;
      char* end;
      row.time = strtod(strtok_r(rest, ",", &rest), NULL);
      for (int i = 0; i < nevents; i++) {
        row.data[i] += strtoull(strtok_r(rest, ",", &rest), &end, 10);
      }
      if (lines % aggr_ == 0) {
        fprintf(fp_, "%.5f", row.time);
        for (int j = 0; j < nevents; j++) {
          fprintf(fp_, ",%lu", row.data[j]);
        }
        fprintf(fp_, "\n");
        Data::ClearRow(&row);
      }
    }
  }

  fclose(input);

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
        skip1_ = skip ? atoi(skip) : skip0_;
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
