#ifndef __AL_CHECK_H
#define __AL_CHECK_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/log.h"

__BEGIN_DECLS

#ifndef AL_CHECK_RET
#define AL_CHECK_RET(exp, __errno, ret)     do {        \
    BUG_ON(!(exp));                                     \
    if(!(exp)) {                                        \
        set_errno((__errno));                           \
        return (ret);                                   \
    }                                                   \
} while(0)
#endif

#ifndef AL_CHECK
#define AL_CHECK(exp, __errno)     do {                 \
    BUG_ON(!(exp));                                     \
    if(!(exp)) {                                        \
        set_errno((__errno));                           \
        return;                                         \
    }                                                   \
} while(0)
#endif

__END_DECLS

#endif

