#ifndef __AL_SW_I2C_H
#define __AL_SW_I2C_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"
#include "alumy/driver/gpio.h"

__BEGIN_DECLS

typedef struct sw_i2c_opt {
    void (*gpio_init)(void);
    void (*gpio_final)(void);
    void (*delay)(void);
    void (*scl_set)(al_gpio_t level);
    void (*sda_set)(al_gpio_t level);
    void (*scl_dir_set)(al_gpio_dir_t dir);
    void (*sda_dir_set)(al_gpio_dir_t dir);
    al_gpio_t (*sda_get)(void);
} sw_i2c_opt_t;

typedef struct sw_i2c {
    sw_i2c_opt_t opt;
    uint8_t addr_bits;
} sw_i2c_t;

int_fast8_t sw_i2c_init(sw_i2c_t *i2c, uint8_t addr_bits,
                        const sw_i2c_opt_t *opt);

int_fast8_t sw_i2c_final(sw_i2c_t *i2c);

int_fast8_t sw_i2c_start(sw_i2c_t *i2c);
void sw_i2c_stop(sw_i2c_t *i2c);
void sw_i2c_ack(sw_i2c_t *i2c);
void sw_i2c_nack(sw_i2c_t *i2c);
int_fast8_t sw_i2c_wait_ack(sw_i2c_t *i2c, uint_fast16_t timeout);
void sw_i2c_send_byte(sw_i2c_t *i2c, uint8_t byte);
uint8_t sw_i2c_recv_byte(sw_i2c_t *i2c);

ssize_t sw_i2c_mem_write(sw_i2c_t *i2c, uint16_t dev_addr, uint16_t addr,
                         const void *data, size_t len, uint_fast16_t timeout);

ssize_t sw_i2c_mem_read(sw_i2c_t *i2c, uint16_t dev_addr, uint16_t addr,
                        void *buf, size_t len, uint_fast16_t timeout);

__END_DECLS

#endif

