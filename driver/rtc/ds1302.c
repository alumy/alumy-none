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

}

int_fast8_t ds1302_final(ds1302_t *this)
{

}

int_fast8_t ds1302_write_date_time(ds1302_t *this, const struct tm *tm)
{

}

int_fast8_t ds1302_read_date_time(ds1302_t *this, struct tm *tm)
{

}

int_fast8_t ds1302_read_ram(ds1302_t *this, uint16_t addr,
                            void *buf, size_t size)
{

}

int_fast8_t ds1302_write_ram(ds1302_t *this, uint16_t addr,
                             const void *data, size_t len)
{

}


__END_DECLS

