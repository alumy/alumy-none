#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/test_init.h"
#include "alumy.h"
#include "test.h"

__BEGIN_DECLS

TEST_GROUP(bcd);

TEST_SETUP(bcd)
{

}

TEST_TEAR_DOWN(bcd)
{

}

TEST(bcd, bcd2bin)
{
    TEST_ASSERT(bcd2bin(0x00) == 0);
    TEST_ASSERT(bcd2bin(0x99) == 99);
    TEST_ASSERT(bcd2bin(0x45) == 45);
    TEST_ASSERT(bcd2bin(0x20) == 20);
}

TEST(bcd, bin2bcd)
{
    TEST_ASSERT(bin2bcd(0) == 0x00);
    TEST_ASSERT(bin2bcd(10) == 0x10);
    TEST_ASSERT(bin2bcd(20) == 0x20);
    TEST_ASSERT(bin2bcd(99) == 0x99);
}

TEST_GROUP_RUNNER(bcd)
{
    RUN_TEST_CASE(bcd, bcd2bin);
    RUN_TEST_CASE(bcd, bin2bcd);
}

static int32_t __add_bcd_tests(void)
{
    RUN_TEST_GROUP(bcd);
    return 0;
}

al_test_suite_init(__add_bcd_tests);

__END_DECLS

