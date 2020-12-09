#ifndef __AL_DRV_EEPROM_BL24CXX
#define __AL_DRV_EEPROM_BL24CXX 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/driver/gpio.h"

#define BL24CXX_SELF_TIMED_WRITE_CYCLE      5       /* unit: ms */

typedef struct bl24cxx bl24cxx_t;

typedef struct bl24cxx_opt {
    void (*watchdog_feed)(void);
    void (*delay_ms)(bl24cxx_t *this, uint32_t ms);
    void (*i2c_start)(bl24cxx_t *this);
    void (*i2c_stop)(bl24cxx_t *this);
    void (*i2c_ack)(bl24cxx_t *this);
    void (*i2c_nack)(bl24cxx_t *this);
    int_fast8_t (*i2c_wait_ack)(bl24cxx_t *this);
    void (*mem_reset)(bl24cxx_t *this);
    uint8_t (*i2c_recv_byte)(bl24cxx_t *this);
    void (*i2c_send_byte)(bl24cxx_t *this, uint8_t byte);
    void (*gpio_init)(bl24cxx_t *this);
    void (*gpio_final)(bl24cxx_t *this);
    void (*wp_set)(bool lock);
} bl24cxx_opt_t;

typedef struct bl24cxx_info {
    size_t size;
    size_t page_size;
    uintptr_t dev_addr;     /* device address */
    size_t addr_bits;       /* the bits of address */
} bl24cxx_info_t;

struct bl24cxx {
    bl24cxx_opt_t opt;
    bl24cxx_info_t info;
    void *i2c;
};

int32_t bl24cxx_init(bl24cxx_t *this, const bl24cxx_opt_t *opt,
                     const bl24cxx_info_t *info, void *i2c);
int32_t bl24cxx_final(bl24cxx_t *this);
ssize_t bl24cxx_read(bl24cxx_t *this, void *buf, uint16_t addr, size_t len);
ssize_t bl24cxx_write(bl24cxx_t *this, uint16_t addr,
                      const void *data, size_t len);
ssize_t bl24cxx_get_size(bl24cxx_t *this);
ssize_t bl24cxx_get_page_size(bl24cxx_t *this);

#endif
