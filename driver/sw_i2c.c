#include "alumy/driver/sw_i2c.h"
#include "alumy/driver/i2c.h"
#include "alumy/errno.h"
#include "alumy/bug.h"

__BEGIN_DECLS

int_t al_sw_i2c_init(al_sw_i2c_t *i2c, uint_t addr_bits,
					 const al_sw_i2c_opt_t *opt)
{
	if (i2c == NULL || opt == NULL) {
		set_errno(EINVAL);
		return -1;
	}

	if (opt->gpio_init == NULL || opt->gpio_final == NULL ||
		opt->delay == NULL || opt->scl_set == NULL ||
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

int_t al_sw_i2c_final(al_sw_i2c_t *i2c)
{
    if (i2c->opt.gpio_final) {
        i2c->opt.gpio_final();
    }

    return 0;
}

int_t al_sw_i2c_start(al_sw_i2c_t *i2c)
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

void al_sw_i2c_stop(al_sw_i2c_t *i2c)
{
    i2c->opt.sda_dir_set(AL_GPIO_OUTPUT);

    i2c->opt.scl_set(AL_GPIO_LOW);
    i2c->opt.sda_set(AL_GPIO_LOW);
    i2c->opt.scl_set(AL_GPIO_HIGH);
    i2c->opt.delay();
    i2c->opt.sda_set(AL_GPIO_HIGH);
    i2c->opt.delay();
}

void al_sw_i2c_ack(al_sw_i2c_t *i2c)
{
    i2c->opt.sda_dir_set(AL_GPIO_OUTPUT);

    i2c->opt.sda_set(AL_GPIO_LOW);
    i2c->opt.delay();
    i2c->opt.scl_set(AL_GPIO_HIGH);
    i2c->opt.delay();
    i2c->opt.scl_set(AL_GPIO_LOW);
}

void al_sw_i2c_nack(al_sw_i2c_t *i2c)
{
    i2c->opt.sda_dir_set(AL_GPIO_OUTPUT);

    i2c->opt.sda_set(AL_GPIO_HIGH);
    i2c->opt.delay();
    i2c->opt.scl_set(AL_GPIO_HIGH);
    i2c->opt.delay();
    i2c->opt.scl_set(AL_GPIO_LOW);
}

int_t al_sw_i2c_wait_ack(al_sw_i2c_t *i2c, uint_t timeout)
{
    uint_t wait = 0;

    i2c->opt.sda_dir_set(AL_GPIO_INPUT);

    i2c->opt.sda_set(AL_GPIO_HIGH);
    i2c->opt.delay();
    i2c->opt.scl_set(AL_GPIO_HIGH);
    i2c->opt.delay();

    while ((i2c->opt.sda_get() == AL_GPIO_HIGH) && (wait++ < timeout));

    if (wait >= timeout) {
        al_sw_i2c_stop(i2c);
        return -1;
    }

    i2c->opt.scl_set(AL_GPIO_LOW);

    return 0;
}

void al_sw_i2c_send_byte(al_sw_i2c_t *i2c, uint8_t byte)
{
    uint_t i = 8;

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

uint8_t al_sw_i2c_recv_byte(al_sw_i2c_t *i2c)
{
    uint_t i = 8;
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

ssize_t al_sw_i2c_mem_write(al_sw_i2c_t *i2c, uint16_t dev_addr, uint16_t addr,
							const void *data, size_t len, uint_t timeout)
{
    const uint8_t *p = (const uint8_t *)data;

    al_sw_i2c_start(i2c);

    al_sw_i2c_send_byte(i2c, dev_addr | I2C_ADDR_WR);
    if (al_sw_i2c_wait_ack(i2c, timeout) != 0) {
        al_sw_i2c_stop(i2c);
        set_errno(EIO);
        return -1;
    }

    if (i2c->addr_bits == 16) {
        al_sw_i2c_send_byte(i2c, (addr & 0xFF00) >> 8);
        if (al_sw_i2c_wait_ack(i2c, timeout) != 0) {
            al_sw_i2c_stop(i2c);
            set_errno(EIO);
            return -1;
        }
    }

    al_sw_i2c_send_byte(i2c, addr & 0xFF);
    if (al_sw_i2c_wait_ack(i2c, timeout) != 0) {
        al_sw_i2c_stop(i2c);
        set_errno(EIO);
        return -1;
    }

    for (uint_t i = 0; i < len; ++i) {
        al_sw_i2c_send_byte(i2c, *p++);
        if (al_sw_i2c_wait_ack(i2c, timeout) != 0) {
            al_sw_i2c_stop(i2c);
            set_errno(EIO);
            return -1;
        }
    }

    al_sw_i2c_stop(i2c);

    set_errno(0);

    return ((ssize_t)p - (ssize_t)data);
}

ssize_t al_sw_i2c_mem_read(al_sw_i2c_t *i2c, uint16_t dev_addr, uint16_t addr,
						   void *buf, size_t len, uint_t timeout)
{
    uint8_t *p = (uint8_t *)buf;

    if (len == 0) {
        return 0;
    }

    al_sw_i2c_start(i2c);

    al_sw_i2c_send_byte(i2c, dev_addr | I2C_ADDR_WR);
    if (al_sw_i2c_wait_ack(i2c, timeout) != 0) {
        al_sw_i2c_stop(i2c);
        set_errno(EIO);
        return -1;
    }

    if (i2c->addr_bits == 16) {
        al_sw_i2c_send_byte(i2c, (addr & 0xFF00) >> 8);
        if (al_sw_i2c_wait_ack(i2c, timeout) != 0) {
            al_sw_i2c_stop(i2c);
            set_errno(EIO);
            return -1;
        }
    }

    al_sw_i2c_send_byte(i2c, addr & 0xFF);
    if (al_sw_i2c_wait_ack(i2c, timeout) != 0) {
        al_sw_i2c_stop(i2c);
        set_errno(EIO);
        return -1;
    }

    al_sw_i2c_start(i2c);

    al_sw_i2c_send_byte(i2c, dev_addr | I2C_ADDR_RD);
    if (al_sw_i2c_wait_ack(i2c, timeout) != 0) {
        al_sw_i2c_stop(i2c);
        set_errno(EIO);
        return -1;
    }

    for (uint32_t i = len - 1; i > 0; --i) {
        *p++ = al_sw_i2c_recv_byte(i2c);
        al_sw_i2c_ack(i2c);
    }

    *p++ = al_sw_i2c_recv_byte(i2c);
    al_sw_i2c_nack(i2c);

    al_sw_i2c_stop(i2c);

    set_errno(0);

    return ((ssize_t)p - (ssize_t)(buf));
}

__END_DECLS

