#ifndef __AL_STRING_H
#define __AL_STRING_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

/**
 *
 *
 * @author jack (2019/8/9)
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
 * @author jack (2019/8/9)
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
 * @brief remove the char from string
 *
 * @author jack (2023/11/9)
 *
 * @param s
 * @param c
 *
 * @return char*
 */
char *strrmchr(char *s, char c);

/**
 * @brief set string with char, the last byte is eof('\0')
 *
 * @author jack (2024/8/28)
 *
 * @param s
 * @param c
 * @param n
 *
 * @return char*
 */
char *strset(char *s, char c, size_t n);

/**
 *
 *
 * @author jack (2019/8/9)
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
 * @author jack (2019/8/9)
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
