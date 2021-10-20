#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/test_init.h"
#include "alumy.h"
#include "test.h"

__BEGIN_DECLS

TEST_GROUP(filter);

TEST_SETUP(filter)
{

}

TEST_TEAR_DOWN(filter)
{

}

TEST(filter, kalman)
{

}

TEST_GROUP_RUNNER(filter)
{
    RUN_TEST_CASE(filter, kalman);
}

static int32_t __add_filter_tests(void)
{
    RUN_TEST_GROUP(filter);
    return 0;
}

al_test_suite_init(__add_filter_tests);

__END_DECLS

