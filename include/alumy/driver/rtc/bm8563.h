#ifndef __AL_DRV_BM8563_H
#define __AL_DRV_BM8563_H 1

#include <time.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef struct bt8563 bm8563_t;

typedef struct bm8563_opt {
    ssize_t (*i2c_mem_read)(bm8563_t *this, uint8_t devaddr, uint8_t addr,
                            void *buf, size_t bufsz, uint_fast16_t timeout);
    ssize_t (*i2c_mem_write)(bm8563_t *this, uint8_t devaddr, uint8_t addr,
                             const void *data, size_t len,
                             uint_fast16_t timeout);
} bm8563_opt_t;

struct bt8563 {
    uint8_t devaddr;
    bm8563_opt_t opt;
    void *i2c;
};

int_fast8_t bm8563_init(bm8563_t *this, const bm8563_opt_t *opt, void *i2c,
                        uint8_t devaddr);
int_fast8_t bm8563_final(bm8563_t *this);

int_fast8_t bm8563_write_date_time(bm8563_t *this, const struct tm *tm);
int_fast8_t bm8563_read_date_time(bm8563_t *this, struct tm *tm);

__END_DECLS

#endif

