#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bcd.h"
#include "alumy/bug.h"
#include "alumy/log.h"
#include "alumy/errno.h"
#include "alumy/driver/rtc/ds1302.h"

__BEGIN_DECLS

int_fast8_t ds1302_init(ds1302_t *this, const ds1302_opt_t *opt)
{
    BUG_ON(this == NULL);
    BUG_ON(opt == NULL);

    BUG_ON(opt->io_set == NULL);
    BUG_ON(opt->io_get == NULL);
    BUG_ON(opt->io_dir_set == NULL);
    BUG_ON(opt->sclk_set == NULL);
    BUG_ON(opt->rst_set == NULL);
    BUG_ON(opt->gpio_init == NULL);
    BUG_ON(opt->gpio_final == NULL);
    BUG_ON(opt->delay_us == NULL);

    this->opt.gpio_init = opt->gpio_init;
    this->opt.io_set = opt->io_set;
    this->opt.io_get = opt->io_get;
    this->opt.io_dir_set = opt->io_dir_set;
    this->opt.sclk_set = opt->sclk_set;
    this->opt.rst_set = opt->rst_set;
    this->opt.gpio_init = opt->gpio_init;
    this->opt.gpio_final = opt->gpio_final;
    this->opt.delay_us = opt->delay_us;

    if (this->opt.gpio_init(this) != 0) {
        set_errno(EIO);
        return -1;
    }

    set_errno(0);
    return 0;
}

int_fast8_t ds1302_final(ds1302_t *this)
{
    if (this->opt.gpio_final(this) != 0) {
        set_errno(EIO);
        return -1;
    }

    set_errno(0);
    return 0;
}

static void ds1302_write_byte(ds1302_t *this, uint8_t byte)
{
    BUG_ON(this == NULL);

    this->opt.io_dir_set(this, AL_GPIO_OUTPUT);

    this->opt.delay_us(this);

    for (int_fast32_t i = 0; i < 8; ++i) {
        if (byte & 0x01) {
            this->opt.io_set(this, AL_GPIO_HIGH);
        } else {
            this->opt.io_set(this, AL_GPIO_LOW);
        }

        byte >>= 1;

        this->opt.sclk_set(this, AL_GPIO_HIGH);
        this->opt.delay_us(this);
        this->opt.sclk_set(this, AL_GPIO_LOW);
        this->opt.delay_us(this);
    }
}

static uint8_t ds1302_read_byte(ds1302_t *this)
{
    uint8_t byte = 0;

    BUG_ON(this == NULL);

    this->opt.io_dir_set(this, AL_GPIO_INPUT);

    this->opt.delay_us(this);

    for (int_fast32_t i = 0; i < 8; ++i) {
        byte >>= 1;

        if (this->opt.io_get(this) == AL_GPIO_HIGH) {
            byte |= 0x80;
        }

        this->opt.sclk_set(this, AL_GPIO_HIGH);
        this->opt.delay_us(this);
        this->opt.sclk_set(this, AL_GPIO_LOW);
        this->opt.delay_us(this);
    }

    return byte;
}

static void ds1302_write(ds1302_t *this, uint8_t addr, uint8_t byte)
{
    BUG_ON(this == NULL);

    this->opt.rst_set(this, AL_GPIO_LOW);
    this->opt.sclk_set(this, AL_GPIO_LOW);
    this->opt.rst_set(this, AL_GPIO_HIGH);
    ds1302_write_byte(this, addr);
    ds1302_write_byte(this, byte);
    this->opt.rst_set(this, AL_GPIO_LOW);
    this->opt.sclk_set(this, AL_GPIO_HIGH);
}

static uint8_t ds1302_read(ds1302_t *this, uint8_t addr)
{
    uint8_t byte;

    BUG_ON(this == NULL);

    this->opt.rst_set(this, AL_GPIO_LOW);
    this->opt.sclk_set(this, AL_GPIO_LOW);
    this->opt.rst_set(this, AL_GPIO_HIGH);
    ds1302_write_byte(this, addr);
    byte = ds1302_read_byte(this);
    this->opt.rst_set(this, AL_GPIO_LOW);

    return byte;
}

int_fast8_t ds1302_write_date_time(ds1302_t *this, const struct tm *tm)
{
    BUG_ON(this == NULL);
    BUG_ON(tm == NULL);

    if (((tm->tm_sec < 0) || (tm->tm_sec > 60)) ||
        ((tm->tm_min < 0) || (tm->tm_min > 59)) ||
        (tm->tm_hour < 0) || (tm->tm_hour > 23) ||
        (tm->tm_mday < 1) || (tm->tm_mday > 31) ||
        (tm->tm_mon < 0) || (tm->tm_mon > 11)) {
        return -1;
    }

    AL_DEBUG(AL_DRV_RTC_LOG, "%s, %04d-%02d-%02d %02d:%02d:%02d",
             __func__,
             tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
             tm->tm_hour, tm->tm_min, tm->tm_sec);

    ds1302_write(this, 0x8E, 0x00);

    ds1302_write(this, 0x80, bin2bcd(tm->tm_sec));
    ds1302_write(this, 0x82, bin2bcd(tm->tm_min));
    /* bit7 set to 0 for 24 hours */
    ds1302_write(this, 0x84, bin2bcd(tm->tm_hour) & 0x3F);
    ds1302_write(this, 0x86, bin2bcd(tm->tm_mday));
    ds1302_write(this, 0x88, bin2bcd(tm->tm_mon + 1));
    /* week day */
    /* ds1302_write(this, 0x8A, bin2bcd(tm->tm.tm_wday + 1)); */
    ds1302_write(this, 0x8C, bin2bcd((tm->tm_year + 1900) % 100));

    ds1302_write(this, 0x8E, 0x80);

    return 0;
}

int_fast8_t ds1302_read_date_time(ds1302_t *this, struct tm *tm)
{
    BUG_ON(this == NULL);
    BUG_ON(tm == NULL);

    tm->tm_sec = bcd2bin(ds1302_read(this, 0x81) & 0x7F);
    tm->tm_min = bcd2bin(ds1302_read(this, 0x83));
    tm->tm_hour = bcd2bin(ds1302_read(this, 0x85) & 0x3F);
    tm->tm_mday = bcd2bin(ds1302_read(this, 0x87));
    tm->tm_mon = bcd2bin(ds1302_read(this, 0x89)) - 1;
    tm->tm_wday = bcd2bin(ds1302_read(this, 0x8B));
    tm->tm_year = bcd2bin(ds1302_read(this, 0x8D)) + 2000 - 1900;

    if (((tm->tm_sec < 0) || (tm->tm_sec > 60)) ||
        ((tm->tm_min < 0) || (tm->tm_min > 59)) ||
        ((tm->tm_hour < 0) || (tm->tm_hour > 23)) ||
        ((tm->tm_mday < 1) || (tm->tm_mday > 31)) ||
        ((tm->tm_mon < 0) || (tm->tm_mon > 11))) {

        tm->tm_year = 100;
        tm->tm_mon = 0;
        tm->tm_mday = 1;
        tm->tm_hour = 0;
        tm->tm_min = 0;
        tm->tm_sec = 0;
    }

    AL_DEBUG(AL_DRV_RTC_LOG, "%s, %04d-%02d-%02d %02d:%02d:%02d",
             __func__,
             tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
             tm->tm_hour, tm->tm_min, tm->tm_sec);

    BUG_ON((tm->tm_sec < 0) || (tm->tm_sec > 60));
    BUG_ON((tm->tm_min < 0) || (tm->tm_min > 59));
    BUG_ON((tm->tm_hour < 0) || (tm->tm_hour > 23));
    BUG_ON((tm->tm_mday < 1) || (tm->tm_mday > 31));
    BUG_ON((tm->tm_mon < 0) || (tm->tm_mon > 11));

    return 0;
}

int_fast8_t ds1302_read_ram(ds1302_t *this, uint16_t addr,
                            void *buf, size_t size)
{
    uint8_t *p = (uint8_t *)buf;
    uint8_t __addr = (0xC1 + (addr << 1));
    uint8_t __end = (__addr + ((size - 1) << 1));

    BUG_ON(this == NULL);
    BUG_ON(buf == NULL);
    BUG_ON(size > 31);
    BUG_ON(__end > 0xFD);

    while (__addr <= __end) {
        *p++ = ds1302_read(this, __addr);
        __addr += 2;
    }

    return 0;
}

int_fast8_t ds1302_write_ram(ds1302_t *this, uint16_t addr,
                             const void *data, size_t len)
{
    const uint8_t *p = (const uint8_t *)data;
    uint8_t __addr = (0xC0 + (addr << 1));
    uint8_t __end = (__addr + ((len - 1) << 1));

    BUG_ON(this == NULL);
    BUG_ON(data == NULL);
    BUG_ON(len > 31);
    BUG_ON(__end > 0xFC);

    ds1302_write(this, 0x8E, 0x00);

    while (__addr <= __end) {
        ds1302_write(this, __addr, *p++);
        __addr += 2;
    }

    ds1302_write(this, 0x8E, 0x80);

    return 0;
}


__END_DECLS

