/**
 * @file    string.h
 * @author  alumy project
 * @version v0.0.1
 * @brief   String manipulation utilities for the alumy library
 * 
 * This header file provides additional string manipulation functions
 * that extend the standard C library string functions. It includes
 * safe string operations, character manipulation, and utility functions
 * for string processing.
 * 
 * @copyright Copyright (c) 2019 alumy project
 */

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
 * @brief Size-bounded string copying
 * 
 * Copy src to string dst of size siz. At most siz-1 characters
 * will be copied. Always NUL terminates (unless siz == 0).
 * This function is similar to strncpy but guarantees NUL termination.
 *
 * @author jack (2019/8/9)
 *
 * @param dst Destination string buffer
 * @param src Source string to copy
 * @param siz Size of destination buffer
 *
 * @return size_t Total length of src string (not including NUL terminator)
 */
size_t strlcpy(char *dst, const char *src, size_t siz);

/**
 * @brief Add null terminator to a memory buffer
 * 
 * Copies data from src to dst and ensures the destination is null-terminated.
 * This is useful when working with binary data that needs to be treated as a string.
 *
 * @author jack (2019/8/9)
 *
 * @param dst Destination buffer
 * @param dstsz Size of destination buffer
 * @param src Source data to copy
 * @param len Length of source data to copy
 *
 * @return ssize_t Number of bytes copied, or -1 on error
 */
ssize_t str_add_null(void *dst, size_t dstsz, const void *src, size_t len);

/**
 * @brief Remove all occurrences of a character from string
 * 
 * Removes all instances of the specified character from the string
 * by shifting remaining characters left. The string is modified in-place.
 *
 * @author jack (2023/11/9)
 *
 * @param s String to modify
 * @param c Character to remove
 *
 * @return char* Pointer to the modified string (same as input s)
 */
char *strrmchr(char *s, char c);

/**
 * @brief Set string with character, null-terminated
 * 
 * Fills the first n-1 characters of string s with character c,
 * then sets the last byte to null terminator ('\0').
 *
 * @author jack (2024/8/28)
 *
 * @param s String buffer to fill
 * @param c Character to fill with
 * @param n Total size of buffer (including space for null terminator)
 *
 * @return char* Pointer to the filled string (same as input s)
 */
char *strset(char *s, char c, size_t n);

/**
 * @brief Generate formatted string from file handle
 * 
 * Reads and processes data from a file handle to generate a formatted string.
 * This function uses variable arguments for additional formatting parameters.
 *
 * @author jack (2019/8/9)
 *
 * @param name Name identifier for the format operation
 * @param more Additional formatting flag
 * @param fh File handle to read from
 * @param ... Variable arguments for formatting
 *
 * @return char* Pointer to generated format string, or NULL on error
 */
char *proc_gen_format(const char *name, int more, FILE *fh, ...);

/**
 * @brief Return string describing error number
 * 
 * Returns a human-readable string describing the error code.
 * This is the alumy library's version of strerror() with support
 * for library-specific error codes.
 *
 * @author jack (2019/8/9)
 *
 * @param errnum Error number to describe
 *
 * @return const char* Pointer to error description string
 */
const char *al_strerror(int32_t errnum);

/**
 * @brief Generate time string from timestamp
 * 
 * Converts a time_t timestamp to a formatted time string.
 * The format and content of the string depend on the implementation.
 *
 * @author jack (2022/1/8)
 *
 * @param t Timestamp to convert
 * @param tmstr Buffer to store the formatted time string
 * @param size Size of the tmstr buffer
 *
 * @return const char* Pointer to the formatted time string
 */
const char *gen_time_str(time_t t, char *tmstr, size_t size);

__END_DECLS

#endif
