#ifndef __AL_LOG_H
#define __AL_LOG_H 1

#include <stdlib.h>
#include <stdarg.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/format_color.h"

__BEGIN_DECLS

#define AL_LOG_EMERG   0   /* system is unusable */
#define AL_LOG_ALERT   1   /* action must be taken immediately */
#define AL_LOG_CRIT    2   /* critical conditions */
#define AL_LOG_ERR     3   /* error conditions */
#define AL_LOG_WARN    4   /* warning conditions */
#define AL_LOG_NOTICE  5   /* normal but significant condition */
#define AL_LOG_INFO    6   /* informational */
#define AL_LOG_DEBUG   7   /* debug-level messages */

#define AL_LOG_PRIMASK 0x07    /* mask to extract priority part (internal) */
				/* extract priority */
#define AL_LOG_PRI(p)  ((p) & AL_LOG_PRIMASK)

/**
 * arguments to setlogmask.
 */
/* mask for one priority */
#define AL_LOG_MASK(pri)   (1 << (pri))
/* all priorities through pri */
#define AL_LOG_UPTO(pri)   ((1 << ((pri)+1)) - 1)

#define AL_LOG_COLOR_A       AL_PRI_BOLD(AL_PRI_GREEN)
#define AL_LOG_COLOR_C       AL_PRI_BOLD(AL_PRI_RED)
#define AL_LOG_COLOR_E       AL_PRI_BOLD(AL_PRI_RED)
#define AL_LOG_COLOR_W       AL_PRI_COLOR(AL_PRI_BROWN)
#define AL_LOG_COLOR_N       AL_PRI_COLOR(AL_PRI_GREEN)
#define AL_LOG_COLOR_I       AL_PRI_COLOR(AL_PRI_GREEN)
#define AL_LOG_COLOR_D
#define AL_LOG_COLOR_V

#define AL_LOG_LINE     __FILE__, __LINE__, __func__

#define AL_LOG_FMT(letter, fmt)     \
	AL_LOG_COLOR_ ## letter fmt AL_PRI_RESET_COLOR "\n"

#define AL_DEBUG(type, fmt, ...)    do {                                    \
    if ((type))                                                               \
        al_log(AL_LOG_DEBUG, AL_LOG_LINE, AL_LOG_FMT(D, fmt), ##__VA_ARGS__); \
} while (0)

#define AL_INFO(type, fmt, ...)	do {								\
	if ((type))														\
		al_log(AL_LOG_INFO, AL_LOG_LINE, AL_LOG_FMT(I, fmt), ##__VA_ARGS__); \
} while (0)

#define AL_NOTICE(type, fmt, ...)	do {							\
	if ((type))														\
		al_log(AL_LOG_NOTICE, AL_LOG_LINE, AL_LOG_FMT(N, fmt), ##__VA_ARGS__); \
} while (0)

#define AL_WARN(type, fmt, ...)	do {								\
	if ((type))														\
		al_log(AL_LOG_WARN, AL_LOG_LINE, AL_LOG_FMT(W, fmt), ##__VA_ARGS__); \
} while (0)

#define AL_ERROR(type, fmt, ...)	do {							\
	if ((type))														\
		al_log(AL_LOG_ERR, AL_LOG_LINE, AL_LOG_FMT(E, fmt), ##__VA_ARGS__); \
} while (0)

#define AL_CRIT(type, fmt, ...)	do {								\
	if ((type))														\
		al_log(AL_LOG_CRIT, AL_LOG_LINE, AL_LOG_FMT(C, fmt), ##__VA_ARGS__); \
} while (0)

#define AL_ALERT(type, fmt, ...)	do {							\
	if ((type))														\
		al_log(AL_LOG_ALERT, AL_LOG_LINE, AL_LOG_FMT(A, fmt), ##__VA_ARGS__); \
} while (0)

#define AL_EMERG(type, fmt, ...)	do {							\
	if ((type))														\
		al_log(AL_LOG_EMERG, AL_LOG_LINE, AL_LOG_FMT(A, fmt), ##__VA_ARGS__); \
} while (0)

#define AL_BIN_D(type, data, len)   do {                        \
    if ((type)) {                                               \
        al_log_bin(AL_LOG_DEBUG, AL_LOG_LINE, (data), (len));   \
    }                                                           \
} while(0)

#define AL_BIN_I(type, data, len)   do {                        \
    if ((type)) {                                               \
        al_log_bin(AL_LOG_INFO, AL_LOG_LINE, (data), (len));    \
    }                                                           \
} while(0)

#define AL_BIN_N(type, data, len)   do {                        \
    if ((type)) {                                               \
        al_log_bin(AL_LOG_NOTICE, AL_LOG_LINE, (data), (len));  \
    }                                                           \
} while(0)

#define AL_BIN_W(type, data, len)   do {                        \
    if ((type)) {                                               \
        al_log_bin(AL_LOG_WARN, AL_LOG_LINE, (data), (len));    \
    }                                                           \
} while(0)

#define AL_BIN_E(type, data, len)   do {                        \
    if ((type)) {                                               \
        al_log_bin(AL_LOG_ERR, AL_LOG_LINE, (data), (len));     \
    }                                                           \
} while(0)

#define AL_BIN_C(type, data, len)   do {                        \
    if ((type)) {                                               \
        al_log_bin(AL_LOG_CRIT, AL_LOG_LINE, (data), (len));    \
    }                                                           \
} while(0)

#define AL_BIN_A(type, data, len)   do {                        \
    if ((type)) {                                               \
        al_log_bin(AL_LOG_ALERT, AL_LOG_LINE, (data), (len));   \
    }                                                           \
} while(0)

#ifndef NDEBUG
#define AL_ASSERT(exp)  do{                                 \
    if(!(exp)) {                                            \
        AL_CRIT(1, "%s:%d:%s: Assertion %s failed.",        \
                __FILE__, __LINE__, __func__, #exp);        \
        abort();                                            \
    }                                                       \
}while(0)
#else
#define AL_ASSERT(exp)      (void)(exp)
#endif

const char *al_log_timestamp(void);

void al_vlog(int32_t pri, const char *fmt, va_list ap);

void al_log(int32_t pri, const char *file, int32_t line, const char *func,
			const char *fmt, ...);

void al_log_bin(int32_t pri,
				const char *file, int32_t line, const char *func,
				const void *data, size_t len);

int32_t al_log_set_mask(int32_t mask);

__END_DECLS

#endif
