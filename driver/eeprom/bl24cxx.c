#include <stdio.h>
#include <string.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/mem.h"
#include "alumy/errno.h"
#include "alumy/driver/i2c.h"
#include "alumy/driver/eeprom/bl24c128.h"

__BEGIN_DECLS

int32_t bl24cxx_init(bl24cxx_t *this, const bl24cxx_opt_t *opt,
                     const bl24cxx_info_t *info, void *i2c)
{
    if (this == NULL || opt == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    if (opt->i2c_start == NULL || opt->i2c_stop == NULL ||
        opt->i2c_ack == NULL || opt->i2c_nack == NULL ||
        opt->i2c_wait_ack == NULL || opt->i2c_recv_byte == NULL ||
        opt->i2c_send_byte == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    if (info->addr_bits != 8 && info->addr_bits != 16) {
        set_errno(EINVAL);
        return -1;
    }

    this->i2c = i2c;

    memcpy(&this->opt, opt, sizeof(this->opt));
    memcpy(&this->info, info, sizeof(this->info));

    this->opt.gpio_init(this);

    this->opt.wp_set(true);

    this->opt.mem_reset(this);

    return 0;
}

int32_t bl24cxx_final(bl24cxx_t *this)
{
    this->opt.wp_set(true);

    if (this->opt.gpio_final) {
        this->opt.gpio_final(this);
    }

    return 0;
}

int_fast32_t bl24cxx_read_byte(bl24cxx_t *this, uint16_t addr)
{
    int_fast32_t byte = -1;

    this->opt.i2c_start(this);

    this->opt.i2c_send_byte(this, this->info.dev_addr | I2C_ADDR_WR);
    if (this->opt.i2c_wait_ack(this) != 0) {
        this->opt.i2c_stop(this);

        set_errno(EIO);
        return -1;
    }

    if (this->info.addr_bits == 16) {
        this->opt.i2c_send_byte(this, addr >> 8);
        if (this->opt.i2c_wait_ack(this) != 0) {
            this->opt.i2c_stop(this);

            set_errno(EIO);
            return -1;
        }
    }

    this->opt.i2c_send_byte(this, addr & 0xFF);
    if (this->opt.i2c_wait_ack(this) != 0) {
        this->opt.i2c_stop(this);
        set_errno(EIO);
        return -1;
    }

    this->opt.i2c_start(this);

    this->opt.i2c_send_byte(this, this->info.dev_addr | I2C_ADDR_RD);
    if (this->opt.i2c_wait_ack(this) != 0) {
        this->opt.i2c_stop(this);
        set_errno(EIO);
        return -1;
    }

    byte = this->opt.i2c_recv_byte(this);
    this->opt.i2c_nack(this);

    this->opt.i2c_stop(this);

    this->opt.watchdog_feed();

    return byte;
}

ssize_t bl24cxx_read(bl24cxx_t *this, void *buf, uint16_t addr, size_t len)
{
    uint8_t *p = (uint8_t *)buf;

    if ((addr + len) > this->info.size) {
        set_errno(EINVAL);
        return -1;
    }

    if (len == 0) {
        return 0;
    }

    this->opt.i2c_start(this);

    this->opt.i2c_send_byte(this, this->info.dev_addr | I2C_ADDR_WR);
    if (this->opt.i2c_wait_ack(this) != 0) {
        this->opt.i2c_stop(this);
        set_errno(EIO);
        return -1;
    }

    if (this->info.addr_bits == 16) {
        this->opt.i2c_send_byte(this, addr >> 8);
        if (this->opt.i2c_wait_ack(this) != 0) {
            this->opt.i2c_stop(this);
            set_errno(EIO);
            return -1;
        }
    }

    this->opt.i2c_send_byte(this, addr & 0xFF);
    if (this->opt.i2c_wait_ack(this) != 0) {
        this->opt.i2c_stop(this);
        set_errno(EIO);
        return -1;
    }

    this->opt.i2c_start(this);

    this->opt.i2c_send_byte(this, this->info.dev_addr | I2C_ADDR_RD);
    if (this->opt.i2c_wait_ack(this) != 0) {
        this->opt.i2c_stop(this);
        set_errno(EIO);
        return -1;
    }

    for (uint32_t i = len - 1; i > 0; --i) {
        *p++ = this->opt.i2c_recv_byte(this);
        this->opt.i2c_ack(this);
        this->opt.watchdog_feed();
    }

    *p++ = this->opt.i2c_recv_byte(this);
    this->opt.i2c_nack(this);

    this->opt.i2c_stop(this);

    this->opt.watchdog_feed();

    return ((ssize_t)p - (ssize_t)(buf));
}

static int32_t bl24cxx_write_byte(bl24cxx_t *this, uint16_t addr, uint8_t byte)
{
    this->opt.i2c_start(this);

    this->opt.i2c_send_byte(this, this->info.dev_addr | I2C_ADDR_WR);

    if (this->opt.i2c_wait_ack(this) != 0) {
        this->opt.i2c_stop(this);
        set_errno(EIO);
        return -1;
    }

    if (this->info.addr_bits == 16) {
        this->opt.i2c_send_byte(this, addr >> 8);
        if (this->opt.i2c_wait_ack(this) != 0) {
            this->opt.i2c_stop(this);
            set_errno(EIO);
            return -1;
        }
    }

    this->opt.i2c_send_byte(this, addr & 0xFF);
    if (this->opt.i2c_wait_ack(this) != 0) {
        this->opt.i2c_stop(this);
        set_errno(EIO);
        return -1;
    }

    this->opt.i2c_send_byte(this, byte);
    if (this->opt.i2c_wait_ack(this) != 0) {
        this->opt.i2c_stop(this);
        set_errno(EIO);
        return -1;
    }

    this->opt.i2c_stop(this);

    this->opt.watchdog_feed();

    return 0;
}

static ssize_t bl24cxx_write_page(bl24cxx_t *this, uint16_t addr,
                                  const void *data, size_t len)
{
	const uint8_t *p = (const uint8_t *)data;
	
    if (!AL_IS_ALIGNED(addr, this->info.page_size) ||
        len != this->info.page_size) {

        set_errno(EINVAL);
        return -1;
    }

    this->opt.i2c_start(this);

    this->opt.i2c_send_byte(this, this->info.dev_addr | I2C_ADDR_WR);
    if (this->opt.i2c_wait_ack(this) != 0) {
        this->opt.i2c_stop(this);
        set_errno(EIO);
        return -1;
    }

    if (this->info.addr_bits == 16) {
        this->opt.i2c_send_byte(this, addr >> 8);
        if (this->opt.i2c_wait_ack(this) != 0) {
            this->opt.i2c_stop(this);
            set_errno(EIO);
            return -1;
        }
    }

    this->opt.i2c_send_byte(this, addr & 0xFF);
    if (this->opt.i2c_wait_ack(this) != 0) {
        this->opt.i2c_stop(this);
        set_errno(EIO);
        return -1;
    }

    for (uint_fast32_t i = 0; i < len; ++i) {
        this->opt.i2c_send_byte(this, *p++);
        if (this->opt.i2c_wait_ack(this) != 0) {
            this->opt.i2c_stop(this);
            set_errno(EIO);
            return -1;
        }

        this->opt.watchdog_feed();
    }

    this->opt.i2c_stop(this);

    this->opt.watchdog_feed();

    return ((ssize_t)p - (ssize_t)data);
}

ssize_t bl24cxx_write(bl24cxx_t *this, uint16_t addr,
                      const void *data, size_t __len)
{
    const uint8_t *p = (const uint8_t *)data;
    ssize_t len = __len;

    if ((addr + len) > this->info.size) {
        set_errno(EINVAL);
        return -1;
    }

    if (len == 0) {
        return 0;
    }

    this->opt.wp_set(false);

    if (len >= this->info.page_size) {

        while (!AL_IS_ALIGNED(addr, this->info.page_size)) {
            if (bl24cxx_write_byte(this, addr, *p) != 0) {
                this->opt.wp_set(true);

                set_errno(EIO);
                return -1;
            }

            p += 1;
            addr += 1;
            len -= 1;

            this->opt.delay_ms(this, BL24CXX_SELF_TIMED_WRITE_CYCLE);
        }

        /**
         * now the addr is aligned to page size
         */

        while (len >= this->info.page_size) {
            ssize_t n;

            n = bl24cxx_write_page(this, addr, p, this->info.page_size);
            if (n != this->info.page_size) {
                this->opt.wp_set(true);

                set_errno(EIO);
                return -1;
            }

            addr += this->info.page_size;
            p += this->info.page_size;
            len -= this->info.page_size;

            this->opt.delay_ms(this, BL24CXX_SELF_TIMED_WRITE_CYCLE);
        }
    }

    while (len > 0) {
        if(bl24cxx_write_byte(this, addr, *p) != 0) {
            this->opt.wp_set(true);

            set_errno(EIO);
            return -1;
        }

        p += 1;
        addr += 1;
        len -= 1;

        this->opt.delay_ms(this, BL24CXX_SELF_TIMED_WRITE_CYCLE);
    }

    this->opt.wp_set(true);

    return ((ssize_t)p - (ssize_t)(data));
}

ssize_t bl24cxx_get_size(bl24cxx_t *this)
{
    if (this == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    return this->info.size;
}

ssize_t bl24cxx_get_page_size(bl24cxx_t *this)
{
    if (this == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    return this->info.page_size;
}

__END_DECLS

