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
#include "alumy/driver/rtc/bm8563.h"

__BEGIN_DECLS

int_fast8_t bm8563_init(bm8563_t *this, const bm8563_opt_t *opt, void *i2c,
                        uint8_t devaddr)
{
    BUG_ON(opt->i2c_mem_read == NULL);
    BUG_ON(opt->i2c_mem_write == NULL);

    this->opt.i2c_mem_read = opt->i2c_mem_read;
    this->opt.i2c_mem_write = opt->i2c_mem_write;
    this->devaddr = devaddr;
    this->i2c = i2c;

    set_errno(0);
	return 0;
}

int_fast8_t bm8563_final(bm8563_t *this)
{
    set_errno(0);
    return 0;
}

int_fast8_t bm8563_write_date_time(bm8563_t *this, const struct tm *tm)
{
    uint8_t data[9] = { 0 };

    BUG_ON(!(tm->tm_sec >= 0 && tm->tm_sec <= 59));
    BUG_ON(!(tm->tm_min >= 0 && tm->tm_min <= 59));
    BUG_ON(!(tm->tm_hour >= 0 && tm->tm_hour <= 23));
    BUG_ON(!(tm->tm_mday >= 1 && tm->tm_mday <= 31));
    BUG_ON(!(tm->tm_wday >= 0 && tm->tm_wday <= 6));
    BUG_ON(!(tm->tm_mon >= 0 && tm->tm_mon <= 11));
    BUG_ON(!(tm->tm_year >= 0 && tm->tm_year <= 199));

    data[0] = 0x00;
    data[1] = 0x00;

    data[2] = bin2bcd(tm->tm_sec);
    data[3] = bin2bcd(tm->tm_min);
    data[4] = bin2bcd(tm->tm_hour);
    data[5] = bin2bcd(tm->tm_mday);
    data[6] = bin2bcd(tm->tm_wday);
    data[7] = bin2bcd(tm->tm_mon + 1);
    data[8] = (tm->tm_year >= 100 ? 0x80 : 0x00) | bin2bcd(tm->tm_year % 100);

    AL_DEBUG(AL_DRV_RTC_LOG, "bm8563 write:");
    AL_BIN_D(AL_DRV_RTC_LOG, data, sizeof(data));

    if (this->opt.i2c_mem_write(this, this->devaddr, 0x00,
                                data, sizeof(data), 1000) != sizeof(data)) {
        set_errno(EIO);
        return -1;
    }

    set_errno(0);
    return 0;
}

int_fast8_t bm8563_read_date_time(bm8563_t *this, struct tm *tm)
{
    uint8_t year;
    uint8_t data[7] = { 0 };

    if (this->opt.i2c_mem_read(this, this->devaddr, 0x02,
                               data, sizeof(data), 1000) != sizeof(data)) {
        set_errno(EIO);
        return -1;
    }

    AL_DEBUG(AL_DRV_RTC_LOG, "bm8563 read:");
    AL_BIN_D(AL_DRV_RTC_LOG, data, sizeof(data));

    tm->tm_sec = bcd2bin(data[0]);
    tm->tm_min = bcd2bin(data[1]);
    tm->tm_hour = bcd2bin(data[2]);
    tm->tm_mday = bcd2bin(data[3]);
    tm->tm_wday = bcd2bin(data[4]);
    tm->tm_mon = bcd2bin(data[5]) - 1;

    year = bcd2bin(data[6]);
    tm->tm_year = ((year & 0x80) ? 100 : 0) + (year & 0x7F);

    BUG_ON(!(tm->tm_sec >= 0 && tm->tm_sec <= 59));
    BUG_ON(!(tm->tm_min >= 0 && tm->tm_min <= 59));
    BUG_ON(!(tm->tm_hour >= 0 && tm->tm_hour <= 23));
    BUG_ON(!(tm->tm_mday >= 1 && tm->tm_mday <= 31));
    BUG_ON(!(tm->tm_wday >= 0 && tm->tm_wday <= 6));
    BUG_ON(!(tm->tm_mon >= 0 && tm->tm_mon <= 11));
    BUG_ON(!(tm->tm_year >= 0 && tm->tm_year <= 199));

    set_errno(0);
    return 0;
}

__END_DECLS

