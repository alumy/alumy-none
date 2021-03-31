#ifndef __AL_DRV_SD3078_H
#define __AL_DRV_SD3078_H 1

#include <time.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#define SD3078_SEC          0x00
#define SD3078_MIN          0x01
#define SD3078_HOUR         0x02
#define SD3078_WDAY         0x03
#define SD3078_MDAY         0x04
#define SD3078_MON          0x05
#define SD3078_YEAR         0x06

#define SD3078_CTR1         0x0F
#define SD3078_CTR2         0x10

#define SD3078_CHG          0x18

#define SD3078_CTR4         0x19
#define SD3078_CTR5         0x1A
#define SD3078_BAT_VAL      0x1B

#define SD3078_RAM_START        0x2C
#define SD3078_RAM_END          0x71

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

