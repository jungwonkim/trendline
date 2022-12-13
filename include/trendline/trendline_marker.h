#ifndef TRENDLINE_INCLUDE_TRENDLINE_TRENDLINE_MARKER_H
#define TRENDLINE_INCLUDE_TRENDLINE_TRENDLINE_MARKER_H

#include <trendline/trendline_errno.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int trendline_init(int* argc, char*** argv);
extern int trendline_finalize();

extern int trendline_start();
extern int trendline_stop();

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* TRENDLINE_INCLUDE_TRENDLINE_TRENDLINE_MARKER_H */

