/**
 * @file    test_init.h
 * @author  alumy project
 * @version v0.0.1
 * @brief   Test suite initialization framework for the alumy library
 * 
 * This header file provides the infrastructure for automatic test suite
 * initialization. It defines the function pointer type and macro for
 * registering test suite initialization functions that will be called
 * automatically during test framework startup.
 * 
 * @copyright Copyright (c) 2019 alumy project
 */

#ifndef __AL_TEST_INIT_H
#define __AL_TEST_INIT_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/mock.h"
#include "alumy/cunit/CUnit.h"
#include "alumy/cunit/Automated.h"
#include "alumy/cunit/Basic.h"
#include "unity.h"
#include "unity_fixture.h"

__BEGIN_DECLS

/**
 * @brief Function pointer type for test suite initialization callbacks
 * 
 * This type defines the signature for test suite initialization functions.
 * These functions are called during test framework startup to register
 * and configure test suites.
 * 
 * @return int32_t Returns 0 on success, negative error code on failure
 */
typedef int32_t (*al_test_suite_initcall_t)(void);

/**
 * @brief Macro to register a test suite initialization function
 * 
 * This macro places a test suite initialization function into a special
 * linker section (.test_suite_initcall) so it can be automatically
 * discovered and called during test framework initialization.
 * 
 * @param fn The test suite initialization function to register
 * 
 * @note The function must have the signature: int32_t fn(void)
 * @note The function should return 0 on success, negative on error
 * 
 * Example usage:
 * @code
 * static int32_t my_test_suite_init(void) {
 *     // Initialize test suite
 *     return 0;
 * }
 * al_test_suite_init(my_test_suite_init);
 * @endcode
 */
#define al_test_suite_init(fn) \
    static al_test_suite_initcall_t __initcall_##fn __used \
    __attribute__((__section__(".test_suite_initcall"))) = fn

__END_DECLS

#endif
