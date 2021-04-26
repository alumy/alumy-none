#include "alumy/driver/sw_i2c.h"
#include "alumy/driver/i2c.h"
#include "alumy/errno.h"
#include "alumy/bug.h"

__BEGIN_DECLS

int_fast8_t sw_i2c_init(sw_i2c_t *i2c, uint8_t addr_bits,
                        const sw_i2c_opt_t *opt)
{
    if (i2c == NULL || opt == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    if (opt->delay == NULL || opt->scl_set == NULL ||
        opt->sda_set == NULL || opt->sda_dir_set == NULL ||
        opt->scl_dir_set == NULL || opt->sda_get == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    i2c->opt.delay = opt->delay;
    i2c->opt.scl_set = opt->scl_set;
    i2c->opt.sda_set = opt->sda_set;
    i2c->opt.sda_dir_set = opt->sda_dir_set;
    i2c->opt.scl_dir_set = opt->scl_dir_set;
    i2c->opt.sda_get = opt->sda_get;
    i2c->opt.gpio_init = opt->gpio_init;
    i2c->opt.gpio_final = opt->gpio_final;

    i2c->opt.gpio_init();

    i2c->opt.scl_dir_set(AL_GPIO_OUTPUT);

    i2c->addr_bits = addr_bits;

    BUG_ON(!(i2c->addr_bits == 8 || i2c->addr_bits == 16));

    return 0;
}

int_fast8_t sw_i2c_final(sw_i2c_t *i2c)
{
    if (i2c->opt.gpio_final) {
        i2c->opt.gpio_final();
    }

    return 0;
}

int_fast8_t sw_i2c_start(sw_i2c_t *i2c)
{
    i2c->opt.sda_dir_set(AL_GPIO_OUTPUT);

    i2c->opt.sda_set(AL_GPIO_HIGH);
    i2c->opt.scl_set(AL_GPIO_HIGH);
    i2c->opt.delay();

    i2c->opt.scl_set(AL_GPIO_HIGH);
    i2c->opt.sda_set(AL_GPIO_LOW);

    i2c->opt.delay();

    i2c->opt.scl_set(AL_GPIO_LOW);

    return 0;
}

void sw_i2c_stop(sw_i2c_t *i2c)
{
    i2c->opt.sda_dir_set(AL_GPIO_OUTPUT);

    i2c->opt.scl_set(AL_GPIO_LOW);
    i2c->opt.sda_set(AL_GPIO_LOW);
    i2c->opt.scl_set(AL_GPIO_HIGH);
    i2c->opt.delay();
    i2c->opt.sda_set(AL_GPIO_HIGH);
    i2c->opt.delay();
}

void sw_i2c_ack(sw_i2c_t *i2c)
{
    i2c->opt.sda_dir_set(AL_GPIO_OUTPUT);

    i2c->opt.sda_set(AL_GPIO_LOW);
    i2c->opt.delay();
    i2c->opt.scl_set(AL_GPIO_HIGH);
    i2c->opt.delay();
    i2c->opt.scl_set(AL_GPIO_LOW);
}

void sw_i2c_nack(sw_i2c_t *i2c)
{
    i2c->opt.sda_dir_set(AL_GPIO_OUTPUT);

    i2c->opt.sda_set(AL_GPIO_HIGH);
    i2c->opt.delay();
    i2c->opt.scl_set(AL_GPIO_HIGH);
    i2c->opt.delay();
    i2c->opt.scl_set(AL_GPIO_LOW);
}

int_fast8_t sw_i2c_wait_ack(sw_i2c_t *i2c, uint_fast16_t timeout)
{
    uint_fast16_t wait = 0;

    i2c->opt.sda_dir_set(AL_GPIO_INPUT);

    i2c->opt.sda_set(AL_GPIO_HIGH);
    i2c->opt.delay();
    i2c->opt.scl_set(AL_GPIO_HIGH);
    i2c->opt.delay();

    while ((i2c->opt.sda_get() == AL_GPIO_HIGH) && (wait++ < timeout));

    if (wait >= timeout) {
        sw_i2c_stop(i2c);
        return -1;
    }

    i2c->opt.scl_set(AL_GPIO_LOW);

    return 0;
}

void sw_i2c_send_byte(sw_i2c_t *i2c, uint8_t byte)
{
    uint_fast8_t i = 8;

    i2c->opt.sda_dir_set(AL_GPIO_OUTPUT);

    while (i--) {
        i2c->opt.scl_set(AL_GPIO_LOW);
        i2c->opt.delay();

        if (byte & 0x80) {
            i2c->opt.sda_set(AL_GPIO_HIGH);
        } else {
            i2c->opt.sda_set(AL_GPIO_LOW);
        }

        byte <<= 1;

        i2c->opt.scl_set(AL_GPIO_HIGH);
        i2c->opt.delay();
    }

    i2c->opt.scl_set(AL_GPIO_LOW);
}

uint8_t sw_i2c_recv_byte(sw_i2c_t *i2c)
{
    uint_fast8_t i = 8;
    uint8_t byte = 0;

    i2c->opt.sda_dir_set(AL_GPIO_INPUT);

    while (i--) {
        i2c->opt.scl_set(AL_GPIO_LOW);
        i2c->opt.delay();

        i2c->opt.scl_set(AL_GPIO_HIGH);
        byte <<= 1;

        if (i2c->opt.sda_get() == AL_GPIO_HIGH) {
            byte |= 0x01;
        }

        i2c->opt.delay();
    }

    i2c->opt.scl_set(AL_GPIO_LOW);

    return byte;
}

ssize_t sw_i2c_mem_write(sw_i2c_t *i2c, uint16_t dev_addr, uint16_t addr,
                         const void *data, size_t len, uint_fast16_t timeout)
{
    const uint8_t *p = (const uint8_t *)data;

    sw_i2c_start(i2c);

    sw_i2c_send_byte(i2c, dev_addr | I2C_ADDR_WR);
    if (sw_i2c_wait_ack(i2c, timeout) != 0) {
        sw_i2c_stop(i2c);
        set_errno(EIO);
        return -1;
    }

    if (i2c->addr_bits == 16) {
        sw_i2c_send_byte(i2c, (addr & 0xFF00) >> 8);
        if (sw_i2c_wait_ack(i2c, timeout) != 0) {
            sw_i2c_stop(i2c);
            set_errno(EIO);
            return -1;
        }
    }

    sw_i2c_send_byte(i2c, addr & 0xFF);
    if (sw_i2c_wait_ack(i2c, timeout) != 0) {
        sw_i2c_stop(i2c);
        set_errno(EIO);
        return -1;
    }

    for (uint_fast32_t i = 0; i < len; ++i) {
        sw_i2c_send_byte(i2c, *p++);
        if (sw_i2c_wait_ack(i2c, timeout) != 0) {
            sw_i2c_stop(i2c);
            set_errno(EIO);
            return -1;
        }
    }

    sw_i2c_stop(i2c);

    set_errno(0);

    return ((ssize_t)p - (ssize_t)data);
}

ssize_t sw_i2c_mem_read(sw_i2c_t *i2c, uint16_t dev_addr, uint16_t addr,
                        void *buf, size_t len, uint_fast16_t timeout)
{
    uint8_t *p = (uint8_t *)buf;

    if (len == 0) {
        return 0;
    }

    sw_i2c_start(i2c);

    sw_i2c_send_byte(i2c, dev_addr | I2C_ADDR_WR);
    if (sw_i2c_wait_ack(i2c, timeout) != 0) {
        sw_i2c_stop(i2c);
        set_errno(EIO);
        return -1;
    }

    if (i2c->addr_bits == 16) {
        sw_i2c_send_byte(i2c, (addr & 0xFF00) >> 8);
        if (sw_i2c_wait_ack(i2c, timeout) != 0) {
            sw_i2c_stop(i2c);
            set_errno(EIO);
            return -1;
        }
    }

    sw_i2c_send_byte(i2c, addr & 0xFF);
    if (sw_i2c_wait_ack(i2c, timeout) != 0) {
        sw_i2c_stop(i2c);
        set_errno(EIO);
        return -1;
    }

    sw_i2c_start(i2c);

    sw_i2c_send_byte(i2c, dev_addr | I2C_ADDR_RD);
    if (sw_i2c_wait_ack(i2c, timeout) != 0) {
        sw_i2c_stop(i2c);
        set_errno(EIO);
        return -1;
    }

    for (uint32_t i = len - 1; i > 0; --i) {
        *p++ = sw_i2c_recv_byte(i2c);
        sw_i2c_ack(i2c);
    }

    *p++ = sw_i2c_recv_byte(i2c);
    sw_i2c_nack(i2c);

    sw_i2c_stop(i2c);

    set_errno(0);

    return ((ssize_t)p - (ssize_t)(buf));
}

__END_DECLS

