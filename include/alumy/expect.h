#ifndef __EXPECT_H
#define __EXPECT_H 1

#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

const char *mkpasswd(char *buf, size_t bufsz, size_t len);

const char *mkname(char *buf, size_t bufsz, size_t len);

__END_DECLS

#endif
