#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/test_init.h"
#include "alumy.h"
#include "test.h"

__BEGIN_DECLS

TEST_GROUP(string);

TEST_SETUP(string)
{

}

TEST_TEAR_DOWN(string)
{

}

TEST(string, strlcpy)
{
    const char src[] = "0123456789";
    char dst[32];

    /* Enough buffer */
    TEST_ASSERT((strlcpy(dst, src, sizeof(dst)) == strlen(src))&&
                (strcmp(dst, src)== 0));

    /* Just right */
    TEST_ASSERT((strlcpy(dst, src, 11) == strlen(src))&&
                (strcmp(dst, src)== 0));

    /* One less */
    TEST_ASSERT((strlcpy(dst, src, 10) == strlen(src))&&
                (strcmp(dst, "012345678")== 0));

    /* Only one */
    TEST_ASSERT((strlcpy(dst, src, 1) == strlen(src))&&
                (strcmp(dst, "")== 0));

    /* No buffer */
    memset(dst, 0xAA, sizeof(dst));
    TEST_ASSERT((strlcpy(dst, src, 0) == strlen(src))&&
                al_mem_is_filled(dst, 0xAA, sizeof(dst)));
}

TEST(string, str_add_null)
{
    const char src[] = "0123456789";
    char dst[128];

    TEST_ASSERT((str_add_null(dst, sizeof(dst),
                              src, strlen(src)) == strlen(src))&&
                (strcmp(dst, src)== 0));

    TEST_ASSERT((str_add_null(dst, 11, src, strlen(src)) == strlen(src))&&
                (strcmp(dst, src)== 0));

    TEST_ASSERT((str_add_null(dst, 8, src, strlen(src)) == 7)&&
                (strcmp(dst, "0123456")== 0));

    TEST_ASSERT((str_add_null(dst, 1, src, strlen(src)) == 0)&&
                (strcmp(dst, "")== 0));

    memset(dst, 0xAA, sizeof(dst));
    TEST_ASSERT((str_add_null(dst, 0, src, strlen(src)) == 0)&&
                al_mem_is_filled(dst, 0xAA, sizeof(dst)));
}

TEST_GROUP_RUNNER(string)
{
    RUN_TEST_CASE(string, strlcpy);
    RUN_TEST_CASE(string, str_add_null);
}

static int32_t __add_string_tests(void)
{
    RUN_TEST_GROUP(string);
    return 0;
}

al_test_suite_init(__add_string_tests);

__END_DECLS

