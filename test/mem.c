#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/test_init.h"
#include "alumy.h"
#include "test.h"

__BEGIN_DECLS

TEST_GROUP(mem);

TEST_SETUP(mem)
{

}

TEST_TEAR_DOWN(mem)
{

}

TEST(mem, al_mem_is_filled)
{
    uint8_t buf[128];

    memset(buf, 0xAA, sizeof(buf));
    TEST_ASSERT(al_mem_is_filled(buf, 0xAA, sizeof(buf)));

    memset(buf, 0xAA, sizeof(buf));
    TEST_ASSERT(al_mem_is_filled(buf, 0xAA, sizeof(buf)));

    memset(buf, 0xAA, sizeof(buf));
    buf[0] = 0x55;
    TEST_ASSERT(!al_mem_is_filled(buf, 0xAA, sizeof(buf)));

    memset(buf, 0xAA, sizeof(buf));
    buf[sizeof(buf) - 1] = 0x55;
    TEST_ASSERT(!al_mem_is_filled(buf, 0xAA, sizeof(buf)));

    memset(buf, 0xAA, sizeof(buf));
    buf[63] = 0x55;
    TEST_ASSERT(!al_mem_is_filled(buf, 0xAA, sizeof(buf)));

    memset(buf, 0xAA, sizeof(buf));
    TEST_ASSERT(al_mem_is_filled(buf + 1, 0xAA, sizeof(buf) - 1));

    memset(buf, 0xAA, sizeof(buf));
    TEST_ASSERT(!al_mem_is_filled(buf + 1, 0x55, sizeof(buf) - 1));

    memset(buf, 0xAA, sizeof(buf));
    TEST_ASSERT(al_mem_is_filled(buf, 0xAA, sizeof(buf) - 3));

    memset(buf, 0xAA, sizeof(buf));
    buf[sizeof(buf) - 4] = 0x55;
    TEST_ASSERT(!al_mem_is_filled(buf, 0xAA, sizeof(buf) - 3));
}

TEST_GROUP_RUNNER(mem)
{
    RUN_TEST_CASE(mem, al_mem_is_filled);
}

static int32_t __add_mem_tests(void)
{
    RUN_TEST_GROUP(mem);
    return 0;
}

al_test_suite_init(__add_mem_tests);

__END_DECLS

