#ifndef __AL_DRV_DS1302_H
#define __AL_DRV_DS1302_H 1

#include <time.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/driver/gpio.h"

__BEGIN_DECLS

typedef struct ds1302 ds1302_t;

typedef struct ds1302_opt {
    int32_t (*io_set)(ds1302_t * this, al_gpio_t level);
    al_gpio_t (*io_get)(ds1302_t * this);
    int32_t (*io_dir_set)(ds1302_t * this, al_gpio_dir_t dir);
    int32_t (*sclk_set)(ds1302_t * this, al_gpio_t level);
    int32_t (*rst_set)(ds1302_t * this, al_gpio_t level);
    int32_t (*gpio_init)(ds1302_t * this);
    int32_t (*gpio_final)(ds1302_t * this);
    void (*delay_us)(ds1302_t * this);
} ds1302_opt_t;

struct ds1302 {
    ds1302_opt_t opt;
};

int_fast8_t ds1302_init(ds1302_t *this, const ds1302_opt_t *opt);

int_fast8_t ds1302_final(ds1302_t *this);

int_fast8_t ds1302_write_date_time(ds1302_t *this, const struct tm *tm);

int_fast8_t ds1302_read_date_time(ds1302_t *this, struct tm *tm);

/**
 * @brief read the ram
 *
 * @author jack (2021/9/23)
 *
 * @param this
 * @param addr mapped to 0x00 - 0x1E
 * @param buf
 * @param size
 *
 * @return int_fast8_t
 */
int_fast8_t ds1302_read_ram(ds1302_t *this, uint16_t addr,
                            void *buf, size_t size);

/**
 * @brief write the ram
 *
 * @author jack (2021/9/23)
 *
 * @param this
 * @param addr
 * @param data
 * @param len
 *
 * @return int_fast8_t
 */
int_fast8_t ds1302_write_ram(ds1302_t *this, uint16_t addr,
                             const void *data, size_t len);

__END_DECLS

#endif

