#include "CommandCorrel.h"
#include "Debug.h"
#include "Data.h"
#include <math.h>
#include <unistd.h>
#include <stdint.h>

namespace trendline {

CommandCorrel::CommandCorrel(int argc, char** argv) : Command(argc, argv) {
  csv_ = false;
  fp_ = stderr;
  data_ = new Data();
  scale_ = 1000;
}

CommandCorrel::~CommandCorrel() {
  if (data_) delete data_;
}

int CommandCorrel::Init() {
  InitOptions();
  inputfile_ = argv_[optind + 1];
  if (!inputfile_) return TRENDLINE_ERR;
  InitPrinterOutput();
  _info("skip0[%d] skip1[%d]", skip0_, skip1_);
  return TRENDLINE_OK;
}

int CommandCorrel::InitOptions() {
  int opt;
  while ((opt = getopt(argc_, argv_, "s:o")) != -1) {
    switch (opt) {
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

int CommandCorrel::InitPrinterOutput() {
  if (!csv_) return TRENDLINE_OK;
  char filename[256];
  size_t len_prefix = strlen(inputfile_) - strlen(TRENDLINE_LOG_FILENAME_EXT) - 1;
  strncpy(filename, inputfile_, len_prefix);
  sprintf(filename + len_prefix, "-correl.%s", TRENDLINE_LOG_FILENAME_EXT);
  fp_ = fopen(filename, "w");
  return fp_ ? TRENDLINE_OK : TRENDLINE_ERR;
}

int CommandCorrel::Run() {
  FILE* input = fopen(inputfile_, "r");

  int nevents = 0;
  int lines = 0;
  char* line = NULL;
  size_t len = 0;
  while (getline(&line, &len, input) != -1) {
    if (strncmp("TIME", line, 4) == 0) {
      CalculatePearsons();
      nevents = 0;
      for (size_t i = 0; i < len; i++) {
        if (line[i] == 0) break;
        if (line[i] == ',') nevents++;
      }
      fprintf(fp_, "%s", line);
      memset(events_, 0, sizeof(events_));
      char* rest = line;
      strtok_r(rest, ",", &rest);
      for (int i = 0; i < nevents; i++) {
        char* e = strtok_r(rest, ",\n", &rest);
        strncpy(events_[i], e, strlen(e)); 
      }
      data_->Reset();
      data_->set_nevents(nevents);
      lines = 0;
    } else {
      if (++lines <= skip0_) continue;
      char* rest = line;
      char* end;
      data_->AddTime(strtod(strtok_r(rest, ",", &rest), NULL));
      for (int i = 0; i < nevents; i++) {
        data_->AddCount(i, strtoull(strtok_r(rest, ",", &rest), &end, 10) / scale_);
      }
      data_->Commit();
    }
  }
  CalculatePearsons();

  fclose(input);

  fflush(fp_);
  return TRENDLINE_OK;
}

int CommandCorrel::CalculatePearsons() {
  data_->DeleteTail(skip1_);
  int nrows = data_->nrows();
  if (nrows <= 0) return TRENDLINE_OK;

  int nevents = data_->nevents();
  u_int64_t sum[TRENDLINE_MAX_COUNTERS];
  u_int64_t avg[TRENDLINE_MAX_COUNTERS];

  for (int i = 0; i < nevents; i++) {
    sum[i] = 0ULL;
    avg[i] = 0ULL;
  }

  trendline_row* rows = data_->rows();
  for (int i = 0; i < nrows; i++) {
    trendline_row* r = rows + i;
    for (int j = 0; j < nevents; j++) sum[j] += r->data[j];
  }
  
  for (int i = 0; i < nevents; i++) avg[i] = sum[i] / nrows;

  int64_t* data_minus_diff  = new int64_t[nevents * nrows];
  u_int64_t* data_minus_diff_sq = new u_int64_t[nevents * nrows];
  u_int64_t* data_minus_diff_sq_sum = new u_int64_t[nevents];

  for (int i = 0; i < nevents; i++) {
    data_minus_diff_sq_sum[i] = 0ULL;
  }

  for (int i = 0; i < nrows; i++) {
    trendline_row* r = rows + i;
    for (int j = 0; j < nevents; j++) {
      int64_t diff = r->data[j] - avg[j];
      u_int64_t diff_sq = diff * diff;
      data_minus_diff[i * nevents + j] = diff;
      data_minus_diff_sq[i * nevents + j] = diff_sq;
      data_minus_diff_sq_sum[j] += diff_sq;
    }
  }

  for (int x = 0; x < nevents; x++) {
    fprintf(fp_, "%s", events_[x]);
    for (int y = 0; y < nevents; y++) {
      double cc = CalculatePearson(x, y, data_minus_diff, data_minus_diff_sq, data_minus_diff_sq_sum);
      if (x == nevents - 1 && y == nevents - 1) cc = -1.0;
      fprintf(fp_, ",%lf", cc);
    }
    fprintf(fp_, "\n");
  }

  delete data_minus_diff;
  delete data_minus_diff_sq;
  delete data_minus_diff_sq_sum;

  return TRENDLINE_OK;
}

double CommandCorrel::CalculatePearson(int x, int y, int64_t* diff, u_int64_t* diff_sq, u_int64_t* diff_sq_sum) {
  int nrows = data_->nrows();
  int nevents = data_->nevents();

  int64_t sum = 0LL;
  for (int i = 0; i < nrows; i++) {
    int64_t xy = diff[i * nevents + x] * diff[i * nevents + y];
    sum += xy;
  }

  double sqrtX = sqrt((double) diff_sq_sum[x]);
  double sqrtY = sqrt((double) diff_sq_sum[y]);

  return (double) sum / (sqrtX * sqrtY);
}

} /* namespace trendline */
