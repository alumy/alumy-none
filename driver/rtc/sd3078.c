#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bcd.h"
#include "alumy/bug.h"
#include "alumy/log.h"
#include "alumy/mem.h"
#include "alumy/errno.h"
#include "alumy/driver/rtc/sd3078.h"

__BEGIN_DECLS

static bool sd3078_is_power_down(sd3078_t *this);
static int32_t sd3078_reset_time(sd3078_t *this);

int_fast8_t sd3078_init(sd3078_t *this, const sd3078_opt_t *opt, void *i2c,
                        uint8_t devaddr)
{
    BUG_ON(opt->i2c_mem_read == NULL);
    BUG_ON(opt->i2c_mem_write == NULL);

    this->opt.i2c_mem_read = opt->i2c_mem_read;
    this->opt.i2c_mem_write = opt->i2c_mem_write;
    this->devaddr = devaddr;
    this->i2c = i2c;

    if (sd3078_is_power_down(this)) {
        AL_INFO(AL_DRV_RTC_LOG, "rtc reset to default");

        sd3078_reset_time(this);
    }

    set_errno(0);
    return 0;
}

int_fast8_t sd3078_final(sd3078_t *this)
{
    set_errno(0);
    return 0;
}

static bool sd3078_is_power_down(sd3078_t *this)
{
    ssize_t n;
    uint8_t data[SD3078_BAT_VAL + 1];

    n = this->opt.i2c_mem_read(this, this->devaddr, 0x00,
                               data, sizeof(data), 1000);

    if (n != sizeof(data)) {
        set_errno(EIO);
        return false;
    }

    return (data[SD3078_CTR1] & 0x01) ? true : false;
}

static int32_t sd3078_reset_time(sd3078_t *this)
{
    struct tm tm = {
        .tm_year = 100,
        .tm_mon = 0,
        .tm_mday = 1,
        .tm_hour = 0,
        .tm_min = 0,
        .tm_sec = 0,
    };

    if (sd3078_write_date_time(this, &tm) != 0) {
        set_errno(EIO);
        return -1;
    }

    set_errno(0);
    return 0;
}

int_fast8_t sd3078_write_date_time_enable(sd3078_t *this)
{
    uint8_t ctr2 = 0x80;
    uint8_t ctr1 = 0xFF;

    if (this->opt.i2c_mem_write(this, this->devaddr, SD3078_CTR2,
                                &ctr2, sizeof(ctr2), 1000) != sizeof(ctr2)) {
        set_errno(EIO);
        return -1;
    }

    if (this->opt.i2c_mem_write(this, this->devaddr, SD3078_CTR1,
                                &ctr1, sizeof(ctr1), 1000) != sizeof(ctr1)) {
        set_errno(EIO);
        return -1;
    }

    set_errno(0);
    return 0;
}

int_fast8_t sd3078_write_date_time_disable(sd3078_t *this)
{
    uint8_t ctr2 = 0x00;
    uint8_t ctr1 = 0x7b;

    if (this->opt.i2c_mem_write(this, this->devaddr, SD3078_CTR1,
                                &ctr1, sizeof(ctr1), 1000) != sizeof(ctr1)) {
        set_errno(EIO);
        return -1;
    }

    if (this->opt.i2c_mem_write(this, this->devaddr, SD3078_CTR2,
                                &ctr2, sizeof(ctr2), 1000) != sizeof(ctr2)) {
        set_errno(EIO);
        return -1;
    }

    set_errno(0);
    return 0;
}

int_fast8_t sd3078_write_date_time(sd3078_t *this, const struct tm *tm)
{
    uint8_t data[7];

    BUG_ON(!(tm->tm_sec >= 0 && tm->tm_sec <= 59));
    BUG_ON(!(tm->tm_min >= 0 && tm->tm_min <= 59));
    BUG_ON(!(tm->tm_hour >= 0 && tm->tm_hour <= 23));
    BUG_ON(!(tm->tm_mday >= 1 && tm->tm_mday <= 31));
    BUG_ON(!(tm->tm_wday >= 0 && tm->tm_wday <= 6));
    BUG_ON(!(tm->tm_mon >= 0 && tm->tm_mon <= 11));
    BUG_ON(!(tm->tm_year >= 100 && tm->tm_year <= 199));

    data[SD3078_SEC] = bin2bcd(tm->tm_sec);
    data[SD3078_MIN] = bin2bcd(tm->tm_min);
    data[SD3078_HOUR] = bin2bcd(tm->tm_hour) | 0x80;
    data[SD3078_WDAY] = bin2bcd(tm->tm_mday);
    data[SD3078_MDAY] = bin2bcd(tm->tm_wday);
    data[SD3078_MON] = bin2bcd(tm->tm_mon + 1);
    data[SD3078_YEAR] = bin2bcd(tm->tm_year % 100);

    AL_DEBUG(AL_DRV_RTC_LOG, "sd3078 write:");
    AL_BIN_D(AL_DRV_RTC_LOG, data, sizeof(data));

    if (sd3078_write_date_time_enable(this) != 0) {
        set_errno(EIO);
        return -1;
    }

    if (this->opt.i2c_mem_write(this, this->devaddr, SD3078_SEC,
                                data, sizeof(data), 1000) != sizeof(data)) {
        set_errno(EIO);
        return -1;
    }

    if (sd3078_write_date_time_disable(this) != 0) {
        set_errno(EIO);
        return -1;
    }

    set_errno(0);
    return 0;
}

int_fast8_t sd3078_read_date_time(sd3078_t *this, struct tm *tm)
{
    uint8_t data[7] = { 0 };

    if (this->opt.i2c_mem_read(this, this->devaddr, SD3078_SEC,
                               data, sizeof(data), 1000) != sizeof(data)) {
        set_errno(EIO);
        return -1;
    }

    tm->tm_sec = bcd2bin(data[SD3078_SEC]);
    tm->tm_min = bcd2bin(data[SD3078_MIN]);
    tm->tm_hour = bcd2bin(data[SD3078_HOUR] & 0x1F);
    tm->tm_mday = bcd2bin(data[SD3078_WDAY]);
    tm->tm_wday = bcd2bin(data[SD3078_MDAY]);
    tm->tm_mon = bcd2bin(data[SD3078_MON]) - 1;
    tm->tm_year = bcd2bin(data[SD3078_YEAR]) + 100;

    BUG_ON(!(tm->tm_sec >= 0 && tm->tm_sec <= 59));
    BUG_ON(!(tm->tm_min >= 0 && tm->tm_min <= 59));
    BUG_ON(!(tm->tm_hour >= 0 && tm->tm_hour <= 23));
    BUG_ON(!(tm->tm_mday >= 1 && tm->tm_mday <= 31));
    BUG_ON(!(tm->tm_wday >= 0 && tm->tm_wday <= 6));
    BUG_ON(!(tm->tm_mon >= 0 && tm->tm_mon <= 11));
    BUG_ON(!(tm->tm_year >= 100 && tm->tm_year <= 199));

    set_errno(0);
    return 0;
}

int_fast8_t sd3078_bat_charge_set(sd3078_t *this, bool enable)
{
    uint8_t data[SD3078_BAT_VAL + 1];
    uint8_t chg = enable ? 0x82 : 0x00;
    ssize_t n;

    n = this->opt.i2c_mem_read(this, this->devaddr, 0x00,
                               data, sizeof(data), 1000);
    if (n != sizeof(data)) {
        set_errno(EIO);
        return -1;
    }

    if ((data[SD3078_CHG] & 0x80) && enable) {
        set_errno(0);
        return 0;
    }

    if ((!(data[SD3078_CHG] & 0x80)) && (!enable)) {
        set_errno(0);
        return 0;
    }

    AL_INFO(AL_DRV_RTC_LOG, "sd3078 battery charge, enable = %d", enable);

    if (sd3078_write_date_time_enable(this) != 0) {
        set_errno(EIO);
        return -1;
    }

    if (this->opt.i2c_mem_write(this, this->devaddr, SD3078_CHG,
                                &chg, sizeof(chg), 1000) != sizeof(chg)) {
        set_errno(EIO);
        return -1;
    }

    if (sd3078_write_date_time_disable(this) != 0) {
        set_errno(EIO);
        return -1;
    }

    set_errno(0);
    return 0;
}

int_fast8_t sd3078_bat_info_get(sd3078_t *this, sd3078_bat_info_t *info)
{
    ssize_t n;
    uint8_t data[SD3078_BAT_VAL + 1];

    if (this == NULL || info == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    n = this->opt.i2c_mem_read(this, this->devaddr, 0x00,
                               data, sizeof(data), 1000);
    if (n != sizeof(data)) {
        set_errno(EIO);
        return -1;
    }

    info->bhf = data[SD3078_CTR5] & 0x02;
    info->blf = data[SD3078_CTR5] & 0x01;
    info->voltage = ((data[SD3078_CTR5] >> 7) << 8) | data[SD3078_BAT_VAL];
    info->voltage *= 10;

    set_errno(0);
    return 0;
}

ssize_t sd3078_ram_write(sd3078_t *this, uint8_t addr,
                         const void *data, size_t len)
{
    if (this == NULL || data == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    if (al_mem_is_overflow(addr, len, SD3078_RAM_START, SD3078_RAM_END)) {
        set_errno(EINVAL);
        return -1;
    }

    if (this->opt.i2c_mem_write(this, this->devaddr, addr,
                                data, len, 1000) != sizeof(data)) {
        set_errno(EIO);
        return -1;
    }

    set_errno(0);
    return 0;
}

ssize_t sd3078_ram_read(sd3078_t *this, uint8_t addr,
                        void *data, size_t len)
{
    if (this == NULL || data == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    if (al_mem_is_overflow(addr, len, SD3078_RAM_START, SD3078_RAM_END)) {
        set_errno(EINVAL);
        return -1;
    }

    if (this->opt.i2c_mem_read(this, this->devaddr, addr,
                               data, len, 1000) != sizeof(data)) {
        set_errno(EIO);
        return -1;
    }

    set_errno(0);
    return 0;
}

__END_DECLS

