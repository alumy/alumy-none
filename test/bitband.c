#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/test_init.h"
#include "alumy/arch/arm.h"
#include "alumy.h"
#include "test.h"

__BEGIN_DECLS

TEST_GROUP(bitband);

TEST_SETUP(bitband)
{

}

TEST_TEAR_DOWN(bitband)
{

}

TEST(bitband, sram)
{
    uint8_t bits;
    uint32_t bitband_addr;

    bits = 8;
    bitband_addr = 0x22000000;

    for (uint32_t addr = 0x20000000; addr < 0x200FFFFC; addr += (bits >> 3)) {
        for (uint32_t bit = 0; bit < bits; ++bit) {
            TEST_ASSERT(BITBAND(addr, bit) == bitband_addr);

            bitband_addr += 4;
        }
    }

    bits = 16;
    bitband_addr = 0x22000000;

    for (uint32_t addr = 0x20000000; addr < 0x200FFFFC; addr += (bits >> 3)) {
        for (uint32_t bit = 0; bit < bits; ++bit) {
            TEST_ASSERT(BITBAND(addr, bit) == bitband_addr);

            bitband_addr += 4;
        }
    }

    bits = 32;
    bitband_addr = 0x22000000;

    for (uint32_t addr = 0x20000000; addr < 0x200FFFFC; addr += (bits >> 3)) {
        for (uint32_t bit = 0; bit < bits; ++bit) {
            TEST_ASSERT(BITBAND(addr, bit) == bitband_addr);

            bitband_addr += 4;
        }
    }
}

TEST(bitband, perh)
{
    uint8_t bits;
    uint32_t bitband_addr;

    bits = 8;
    bitband_addr = 0x42000000;

    for (uint32_t addr = 0x40000000; addr < 0x400FFFFC; addr += (bits >> 3)) {
        for (uint32_t bit = 0; bit < bits; ++bit) {
            TEST_ASSERT(BITBAND(addr, bit) == bitband_addr);

            bitband_addr += 4;
        }
    }

    bits = 16;
    bitband_addr = 0x42000000;

    for (uint32_t addr = 0x40000000; addr < 0x400FFFFC; addr += (bits >> 3)) {
        for (uint32_t bit = 0; bit < bits; ++bit) {
            TEST_ASSERT(BITBAND(addr, bit) == bitband_addr);

            bitband_addr += 4;
        }
    }

    bits = 32;
    bitband_addr = 0x42000000;

    for (uint32_t addr = 0x40000000; addr < 0x400FFFFC; addr += (bits >> 3)) {
        for (uint32_t bit = 0; bit < bits; ++bit) {
            TEST_ASSERT(BITBAND(addr, bit) == bitband_addr);

            bitband_addr += 4;
        }
    }
}

TEST_GROUP_RUNNER(bitband)
{
    RUN_TEST_CASE(bitband, sram);
    RUN_TEST_CASE(bitband, perh);
}

static int32_t __add_bitband_tests(void)
{
    RUN_TEST_GROUP(bitband);
    return 0;
}

al_test_suite_init(__add_bitband_tests);

__END_DECLS

