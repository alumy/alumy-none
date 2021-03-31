#ifndef __AL_DRV_SD3078_H
#define __AL_DRV_SD3078_H 1

#include <time.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef struct sd3078 sd3078_t;

typedef struct sd3078_opt {
    ssize_t (*i2c_mem_read)(sd3078_t *this, uint8_t devaddr, uint8_t addr,
                            void *buf, size_t bufsz, uint_fast16_t timeout);
    ssize_t (*i2c_mem_write)(sd3078_t *this, uint8_t devaddr, uint8_t addr,
                             const void *data, size_t len,
                             uint_fast16_t timeout);
} sd3078_opt_t;

struct sd3078 {
    uint8_t devaddr;
    sd3078_opt_t opt;
    void *i2c;
};

typedef struct sd3078_bat_info {
    uint16_t voltage;
    bool bhf;       /* battery high flag */
    bool blf;       /* battery low flag */
} sd3078_bat_info_t;

int_fast8_t sd3078_init(sd3078_t *this, const sd3078_opt_t *opt, void *i2c,
                        uint8_t devaddr);

int_fast8_t sd3078_final(sd3078_t *this);

int_fast8_t sd3078_write_date_time(sd3078_t *this, const struct tm *tm);

int_fast8_t sd3078_read_date_time(sd3078_t *this, struct tm *tm);

int_fast8_t sd3078_bat_charge_set(sd3078_t *this, bool enable);

int_fast8_t sd3078_bat_info_get(sd3078_t *this, sd3078_bat_info_t *info);

ssize_t sd3078_ram_write(sd3078_t *this, uint8_t addr,
                         const void *data, size_t len);

ssize_t sd3078_ram_read(sd3078_t *this, uint8_t addr,
                        void *data, size_t len);

__END_DECLS

#endif

