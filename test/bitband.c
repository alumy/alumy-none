#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/cunit/CUnit.h"
#include "alumy/cunit/Automated.h"
#include "alumy/cunit/Basic.h"
#include "alumy/arch/arm.h"
#include "alumy.h"
#include "test.h"

__BEGIN_DECLS

static int bitband_suite_init(void)
{
	return 0;
}

static int bitband_suite_clean(void)
{
	return 0;
}

static void bitband_sram_test(void)
{
    uint8_t bits;
    uint32_t bitband_addr;

    bits = 8;
    bitband_addr = 0x22000000;

    for (uint32_t addr = 0x20000000; addr < 0x200FFFFC; addr += (bits >> 3)) {
        for (uint32_t bit = 0; bit < bits; ++bit) {
            CU_ASSERT(BITBAND(addr, bit) == bitband_addr);

            bitband_addr += 4;
        }
    }

    bits = 16;
    bitband_addr = 0x22000000;

    for (uint32_t addr = 0x20000000; addr < 0x200FFFFC; addr += (bits >> 3)) {
        for (uint32_t bit = 0; bit < bits; ++bit) {
            CU_ASSERT(BITBAND(addr, bit) == bitband_addr);

            bitband_addr += 4;
        }
    }

    bits = 32;
    bitband_addr = 0x22000000;

    for (uint32_t addr = 0x20000000; addr < 0x200FFFFC; addr += (bits >> 3)) {
        for (uint32_t bit = 0; bit < bits; ++bit) {
            CU_ASSERT(BITBAND(addr, bit) == bitband_addr);

            bitband_addr += 4;
        }
    }
}

static void bitband_perh_test(void)
{
    uint8_t bits;
    uint32_t bitband_addr;

    bits = 8;
    bitband_addr = 0x42000000;

    for (uint32_t addr = 0x40000000; addr < 0x400FFFFC; addr += (bits >> 3)) {
        for (uint32_t bit = 0; bit < bits; ++bit) {
            CU_ASSERT(BITBAND(addr, bit) == bitband_addr);

            bitband_addr += 4;
        }
    }

    bits = 16;
    bitband_addr = 0x42000000;

    for (uint32_t addr = 0x40000000; addr < 0x400FFFFC; addr += (bits >> 3)) {
        for (uint32_t bit = 0; bit < bits; ++bit) {
            CU_ASSERT(BITBAND(addr, bit) == bitband_addr);

            bitband_addr += 4;
        }
    }

    bits = 32;
    bitband_addr = 0x42000000;

    for (uint32_t addr = 0x40000000; addr < 0x400FFFFC; addr += (bits >> 3)) {
        for (uint32_t bit = 0; bit < bits; ++bit) {
            CU_ASSERT(BITBAND(addr, bit) == bitband_addr);

            bitband_addr += 4;
        }
    }
}

void add_bitband_tests(void)
{
	CU_pSuite suite;

    suite = CU_add_suite("bitband", bitband_suite_init, bitband_suite_clean);

    CU_add_test(suite, "bitband_sram_test", bitband_sram_test);
    CU_add_test(suite, "bitband_perh_test", bitband_perh_test);
}

__END_DECLS

