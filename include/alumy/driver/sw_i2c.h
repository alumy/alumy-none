#ifndef __AL_SW_I2C_H
#define __AL_SW_I2C_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"
#include "alumy/driver/gpio.h"

__BEGIN_DECLS

typedef struct al_sw_i2c_opt {
    void (*gpio_init)(void);
    void (*gpio_final)(void);
    void (*delay)(void);
    void (*scl_set)(al_gpio_t level);
    void (*sda_set)(al_gpio_t level);
    void (*scl_dir_set)(al_gpio_dir_t dir);
    void (*sda_dir_set)(al_gpio_dir_t dir);
    al_gpio_t (*sda_get)(void);
} al_sw_i2c_opt_t;

typedef struct al_sw_i2c {
    al_sw_i2c_opt_t opt;
    uint_t addr_bits;
} al_sw_i2c_t;

int_t al_sw_i2c_init(al_sw_i2c_t *i2c, uint_t addr_bits,
					 const al_sw_i2c_opt_t *opt);

int_t al_sw_i2c_final(al_sw_i2c_t *i2c);

int_t al_sw_i2c_start(al_sw_i2c_t *i2c);

void al_sw_i2c_stop(al_sw_i2c_t *i2c);

void al_sw_i2c_ack(al_sw_i2c_t *i2c);

void al_sw_i2c_nack(al_sw_i2c_t *i2c);

int_t al_sw_i2c_wait_ack(al_sw_i2c_t *i2c, uint_t timeout);

void al_sw_i2c_send_byte(al_sw_i2c_t *i2c, uint8_t byte);

uint8_t al_sw_i2c_recv_byte(al_sw_i2c_t *i2c);

ssize_t al_sw_i2c_mem_write(al_sw_i2c_t *i2c, uint16_t dev_addr, uint16_t addr,
							const void *data, size_t len, uint_t timeout);

ssize_t al_sw_i2c_mem_read(al_sw_i2c_t *i2c, uint16_t dev_addr, uint16_t addr,
						   void *buf, size_t len, uint_t timeout);

__END_DECLS

#endif

