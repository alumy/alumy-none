/**
 * @file check.h
 * @brief Condition checking macros with error handling
 * 
 * This header provides macros for checking conditions and handling errors
 * by setting errno and returning appropriate values when conditions fail.
 */

#ifndef __AL_CHECK_H
#define __AL_CHECK_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"
#include "alumy/log.h"

__BEGIN_DECLS

/**
 * @brief Check condition and return with specified value on failure
 * 
 * This macro checks if the given expression is true. If the expression
 * evaluates to false, it sets errno to the specified error code and
 * returns the specified return value.
 * 
 * @param exp The expression to evaluate
 * @param __errno The error code to set if expression is false
 * @param ret The value to return if expression is false
 */
#ifndef AL_CHECK_RET
#define AL_CHECK_RET(exp, __errno, ret)     do {        \
    if(__unlikely(!(exp))) {                            \
        errno = (__errno);                              \
        return (ret);                                   \
    }                                                   \
} while(0)
#endif

/**
 * @brief Check condition and return void on failure
 * 
 * This macro checks if the given expression is true. If the expression
 * evaluates to false, it sets errno to the specified error code and
 * returns from the current function (for void functions).
 * 
 * @param exp The expression to evaluate
 * @param __errno The error code to set if expression is false
 */
#ifndef AL_CHECK
#define AL_CHECK(exp, __errno)     do {                 \
    if(__unlikely(!(exp))) {                            \
        errno = (__errno);                              \
        return;                                         \
    }                                                   \
} while(0)
#endif

__END_DECLS

#endif
