#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "main.h"
#include "alumy/test_init.h"
#include "alumy.h"

__BEGIN_DECLS

#if AL_TEST_DRIVER

#define DS1302_SCLK_PORT        PortD
#define DS1302_SCLK_PIN         Pin11
#define DS1302_IO_PORT          PortD
#define DS1302_IO_PIN           Pin12
#define DS1302_RST_PORT         PortD
#define DS1302_RST_PIN          Pin13

static ds1302_t ds1302;

TEST_GROUP(rtc);

static int32_t ds1302_io_set(ds1302_t *this, al_gpio_t level)
{
    return 0;
}

static al_gpio_t ds1302_io_get(ds1302_t *this)
{
    return AL_GPIO_HIGH;
}

static int32_t ds1302_io_dir_set(ds1302_t *this, al_gpio_dir_t dir)
{
    return 0;
}

static int32_t ds1302_sclk_set(ds1302_t *this, al_gpio_t level)
{
    if (level == AL_GPIO_HIGH) {
    } else {
    }

    return 0;
}

static int32_t ds1302_rst_set(ds1302_t *this, al_gpio_t level)
{
    if (level == AL_GPIO_HIGH) {
    } else {
    }

    return 0;
}

static int32_t ds1302_gpio_init(ds1302_t *this)
{
    return 0;
}

static int32_t ds1302_gpio_final(ds1302_t *this)
{
    return 0;
}

static void ds1302_delay_us(ds1302_t *this)
{
    uint32_t delay = SystemCoreClock / 5 / 200000;

    while (delay--) {
        __asm__ volatile("nop");
    }
}

TEST_SETUP(rtc)
{
    ds1302_opt_t opt = {
        .delay_us = ds1302_delay_us,
        .gpio_init = ds1302_gpio_init,
        .gpio_final = ds1302_gpio_final,
        .io_set = ds1302_io_set,
        .io_get = ds1302_io_get,
        .io_dir_set = ds1302_io_dir_set,
        .sclk_set = ds1302_sclk_set,
        .rst_set = ds1302_rst_set,
    };

    ds1302_init(&ds1302, &opt);
}

TEST_TEAR_DOWN(rtc)
{
    ds1302_final(&ds1302);
}

TEST(rtc, ds1302_write_date_time_test)
{
    struct tm tm_wr = {
        .tm_sec = 0,
        .tm_min = 0,
        .tm_hour = 0,
        .tm_mday = 1,
        .tm_mon = 0,
        .tm_year = 2021 - 1900
    };

    struct tm tm_rd;

    ds1302_write_date_time(&ds1302, &tm_wr);
    ds1302_read_date_time(&ds1302, &tm_rd);

    TEST_ASSERT(mktime(&tm_wr) == mktime(&tm_rd));
}

TEST(rtc, ds1302_write_ram_test)
{
    uint8_t ram_wr[31], ram_rd[31];

    for (int32_t i = 0; i < sizeof(ram_wr); ++i) {
        ram_wr[i] = rand() & 0xFF;
    }

    memset(ram_rd, 0, sizeof(ram_rd));

    ds1302_write_ram(&ds1302, 0x00, ram_wr, sizeof(ram_wr));
    ds1302_read_ram(&ds1302, 0x00, ram_rd, sizeof(ram_rd));

    TEST_ASSERT(memcmp(ram_wr, ram_rd, sizeof(ram_wr)) == 0);
}

TEST_GROUP_RUNNER(rtc)
{
    RUN_TEST_CASE(rtc, ds1302_write_date_time_test);
    RUN_TEST_CASE(rtc, ds1302_write_ram_test);
}

static int32_t __add_rtc_tests(void)
{
    printf("run rtc\n");
    RUN_TEST_GROUP(rtc);
    return 0;
}

al_test_suite_init(__add_rtc_tests);

#endif

__END_DECLS

