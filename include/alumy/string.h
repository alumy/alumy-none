#ifndef __AL_STRING_H
#define __AL_STRING_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

/**
 *
 *
 * @author chenyj (2019/8/9)
 *
 * @param dst
 * @param src
 * @param siz
 *
 * @return size_t
 */
size_t strlcpy(char *dst, const char *src, size_t siz);

/**
 *
 *
 * @author chenyj (2019/8/9)
 *
 * @param dst
 * @param dstsz
 * @param src
 * @param len
 *
 * @return ssize_t
 */
ssize_t str_add_null(void *dst, size_t dstsz, const void *src, size_t len);

/**
 *
 *
 * @author chenyj (2019/8/9)
 *
 * @param name
 * @param more
 * @param fh
 *
 * @return char*
 */
char *proc_gen_format(const char *name, int more, FILE *fh, ...);

/**
 * @brief Return string describing error number
 *
 * @author chenyj (2019/8/9)
 *
 * @param errnum
 *
 * @return const char*
 */
const char *al_strerror(int32_t errnum);

/**
 *
 *
 * @author jack (2022/1/8)
 *
 * @param t
 * @param tmstr
 * @param size
 *
 * @return const char*
 */
const char *gen_time_str(time_t t, char *tmstr, size_t size);

__END_DECLS

#endif
