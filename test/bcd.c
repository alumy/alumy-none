#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/test_init.h"
#include "alumy.h"
#include "test.h"

__BEGIN_DECLS

static int bcd_suite_init(void)
{
    return 0;
}

static int bcd_suite_clean(void)
{
    return 0;
}

static void bcd2bin_test(void)
{
    CU_ASSERT(bcd2bin(0x00) == 0);
    CU_ASSERT(bcd2bin(0x99) == 99);
    CU_ASSERT(bcd2bin(0x45) == 45);
    CU_ASSERT(bcd2bin(0x20) == 20);
}

static void bin2bcd_test(void)
{
    CU_ASSERT(bin2bcd(0) == 0x00);
    CU_ASSERT(bin2bcd(10) == 0x10);
    CU_ASSERT(bin2bcd(20) == 0x20);
    CU_ASSERT(bin2bcd(99) == 0x99);
}

static int32_t add_bcd_tests(void)
{
    CU_pSuite suite;

    suite = CU_add_suite("bcd", bcd_suite_init, bcd_suite_clean);

    CU_add_test(suite, "bcd2bin_test", bcd2bin_test);
    CU_add_test(suite, "bin2bcd_test", bin2bcd_test);

    return 0;
}

al_test_suite_init(add_bcd_tests);

__END_DECLS

