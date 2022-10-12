#ifndef TRENDLINE_SRC_DEBUG_H
#define TRENDLINE_SRC_DEBUG_H

#include <stdio.h>
#include <string.h>

#ifndef NDEBUG
#define _TRACE_ENABLE
#define _CHECK_ENABLE
#define _DEBUG_ENABLE
#define _INFO_ENABLE
#define _TODO_ENABLE
#endif

#define _ERROR_ENABLE

#define _COLOR_DEBUG

#ifdef _COLOR_DEBUG
#define RED     "\033[22;31m"
#define GREEN   "\033[22;32m"
#define YELLOW  "\033[22;33m"
#define BLUE    "\033[22;34m"
#define PURPLE  "\033[22;35m"
#define CYAN    "\033[22;36m"
#define GRAY    "\033[22;37m"
#define BRED    "\033[1;31m"
#define BGREEN  "\033[1;32m"
#define BYELLOW "\033[1;33m"
#define BBLUE   "\033[1;34m"
#define BPURPLE "\033[1;35m"
#define BCYAN   "\033[1;36m"
#define BGRAY   "\033[1;37m"
#define _RED    "\033[22;41m" BGRAY
#define _GREEN  "\033[22;42m" BGRAY
#define _YELLOW "\033[22;43m" BGRAY
#define _BLUE   "\033[22;44m" BGRAY
#define _PURPLE "\033[22;45m" BGRAY
#define _CYAN   "\033[22;46m" BGRAY
#define _GRAY   "\033[22;47m"
#define RESET   "\x1b[m"
#else
#define RED
#define GREEN
#define YELLOW
#define BLUE
#define PURPLE
#define CYAN
#define GRAY
#define BRED
#define BGREEN
#define BYELLOW
#define BBLUE
#define BPURPLE
#define BCYAN
#define BGRAY
#define _RED
#define _GREEN
#define _YELLOW
#define _BLUE
#define _PURPLE
#define _CYAN
#define _GRAY
#define RESET
#endif

#define CHECK_O   "\u2714 "
#define CHECK_X   "\u2716 "

namespace trendline {

#define __SHORT_FILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifdef _TRACE_ENABLE
#define  _trace(fmt, ...) do { printf( BLUE "[T] [%s:%d:%s] " fmt RESET "\n", __SHORT_FILE__, __LINE__, __func__, __VA_ARGS__); fflush(stdout); } while (0)
#define __trace(fmt, ...) do { printf(_BLUE "[T] [%s:%d:%s] " fmt RESET "\n", __SHORT_FILE__, __LINE__, __func__, __VA_ARGS__); fflush(stdout); } while (0)
#else
#define  _trace(fmt, ...) do { } while (0)
#define __trace(fmt, ...) do { } while (0)
#endif

#ifdef _CHECK_ENABLE
#define  _check() do { printf( PURPLE "[C] [%s:%d:%s]" RESET "\n", __SHORT_FILE__, __LINE__, __func__); fflush(stdout); } while (0)
#define __check() do { printf(_PURPLE "[C] [%s:%d:%s]" RESET "\n", __SHORT_FILE__, __LINE__, __func__); fflush(stdout); } while (0)
#else
#define  _check() do { } while (0)
#define __check() do { } while (0)
#endif

#ifdef _DEBUG_ENABLE
#define  _debug(fmt, ...) do { printf( CYAN "[D] [%s:%d:%s] " fmt RESET "\n", __SHORT_FILE__, __LINE__, __func__, __VA_ARGS__); fflush(stdout); } while (0)
#define __debug(fmt, ...) do { printf(_CYAN "[D] [%s:%d:%s] " fmt RESET "\n", __SHORT_FILE__, __LINE__, __func__, __VA_ARGS__); fflush(stdout); } while (0)
#else
#define  _debug(fmt, ...) do { } while (0)
#define __debug(fmt, ...) do { } while (0)
#endif

#ifdef _INFO_ENABLE
#define  _info(fmt, ...) do { printf( YELLOW "[I] [%s:%d:%s] " fmt RESET "\n", __SHORT_FILE__, __LINE__, __func__, __VA_ARGS__); fflush(stdout); } while (0)
#define __info(fmt, ...) do { printf(_YELLOW "[I] [%s:%d:%s] " fmt RESET "\n", __SHORT_FILE__, __LINE__, __func__, __VA_ARGS__); fflush(stdout); } while (0)
#else
#define  _info(fmt, ...) do { } while (0)
#define __info(fmt, ...) do { } while (0)
#endif

#ifdef _ERROR_ENABLE
#define   _error(fmt, ...) do { printf( RED "[E] [%s:%d:%s] " fmt RESET "\n", __SHORT_FILE__, __LINE__, __func__, __VA_ARGS__); fflush(stdout); } while (0)
#define ___error(fmt, ...) do { printf(_RED "[E] [%s:%d:%s] " fmt RESET "\n", __SHORT_FILE__, __LINE__, __func__, __VA_ARGS__); fflush(stdout); } while (0) // MacOS
#else
#define  _error(fmt, ...) do { } while (0)
#define ___error(fmt, ...) do { } while (0) // MacOS
#endif

#ifdef _TODO_ENABLE
#define  _todo(fmt, ...) do { printf( GREEN "[TODO] [%s:%d:%s] " fmt RESET "\n", __SHORT_FILE__, __LINE__, __func__, __VA_ARGS__); fflush(stdout); } while (0)
#define __todo(fmt, ...) do { printf(_GREEN "[TODO] [%s:%d:%s] " fmt RESET "\n", __SHORT_FILE__, __LINE__, __func__, __VA_ARGS__); fflush(stdout); } while (0)
#else
#define  _todo(fmt, ...) do { } while (0)
#define __todo(fmt, ...) do { } while (0)
#endif

} /* namespace trendline */

#endif /* TRENDLINE_SRC_DEBUG_H */
