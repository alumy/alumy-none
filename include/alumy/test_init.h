#ifndef __AL_TEST_INIT_H
#define __AL_TEST_INIT_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/cunit/CUnit.h"
#include "alumy/cunit/Automated.h"
#include "alumy/cunit/Basic.h"
#include "unity.h"
#include "unity_fixture.h"

__BEGIN_DECLS

typedef int32_t (*al_test_suite_initcall_t)(void);

#define al_test_suite_init(fn) \
    static al_test_suite_initcall_t __initcall_##fn __used \
    __attribute__((__section__(".test_suite_initcall"))) = fn

__END_DECLS

#endif

