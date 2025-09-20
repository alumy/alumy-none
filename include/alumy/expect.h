/**
 * @file expect.h
 * @brief Utility functions for generating random strings and names
 * 
 * This header provides functions for generating random passwords and names,
 * commonly used in testing scenarios or when random string generation is needed.
 */

#ifndef __EXPECT_H
#define __EXPECT_H 1

#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

/**
 * @brief Generate a random password string
 * 
 * @param buf Buffer to store the generated password
 * @param bufsz Size of the buffer
 * @param len Desired length of the password
 * @return Pointer to the generated password string, or NULL on failure
 */
const char *mkpasswd(char *buf, size_t bufsz, size_t len);

/**
 * @brief Generate a random name string
 * 
 * @param buf Buffer to store the generated name
 * @param bufsz Size of the buffer
 * @param len Desired length of the name
 * @return Pointer to the generated name string, or NULL on failure
 */
const char *mkname(char *buf, size_t bufsz, size_t len);

__END_DECLS

#endif
