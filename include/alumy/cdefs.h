/**
 * @file cdefs.h
 * @brief Common definitions and macros for C/C++ compatibility
 * 
 * This header provides essential macros and definitions that facilitate
 * compatibility between C and C++ code, particularly for function declarations
 * and linkage specifications.
 */

#ifndef __AL_CDEFS_H
#define __AL_CDEFS_H 1

/* C++ needs to know that types and declarations are C, not C++.  */
#ifdef  __cplusplus
# define __BEGIN_DECLS  extern "C" {
# define __END_DECLS    }
#else
# define __BEGIN_DECLS
# define __END_DECLS
#endif

#endif
