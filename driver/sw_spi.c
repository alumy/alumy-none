#include "alumy/driver/sw_spi.h"
#include "alumy/errno.h"
#include "alumy/bug.h"

__BEGIN_DECLS

int_fast8_t sw_spi_init(sw_spi_t *spi, const sw_spi_opt_t *opt)
{
    if (spi == NULL || opt == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    if (opt->gpio_init == NULL || opt->gpio_final == NULL ||
        opt->delay == NULL || opt->sck_set == NULL ||
        opt->mosi_set == NULL || opt->miso_get == NULL ||
        opt->nss_set == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    spi->opt.gpio_init = opt->gpio_init;
    spi->opt.gpio_final = opt->gpio_final;
    spi->opt.delay = opt->delay;
    spi->opt.sck_set = opt->sck_set;
    spi->opt.mosi_set = opt->mosi_set;
    spi->opt.miso_get = opt->miso_get;
    spi->opt.nss_set = opt->nss_set;

    if (spi->opt.gpio_init() != 0) {
        return -1;
    }

    spi->opt.nss_set(AL_GPIO_HIGH);

    return 0;
}

int_fast8_t sw_spi_final(sw_spi_t *spi)
{
    if (spi->opt.gpio_final() != 0) {
        return -1;
    }

    return 0;
}

uint8_t sw_spi_read_write_byte(sw_spi_t *spi, uint8_t byte)
{
    uint8_t recv = 0;

    for (int32_t i = 0; i < 8; i++) {
        spi->opt.sck_set(AL_GPIO_LOW);
        spi->opt.delay();
        spi->opt.mosi_set((byte & 0x80) ? AL_GPIO_HIGH : AL_GPIO_LOW);
        byte <<= 1;
        spi->opt.delay();
        spi->opt.sck_set(AL_GPIO_HIGH);
        spi->opt.delay();
        recv <<= 1;
        if (spi->opt.miso_get() == AL_GPIO_HIGH) {
            recv |= 0x01;
        }
        spi->opt.delay();
    }

    spi->opt.sck_set(AL_GPIO_LOW);

    return recv;
}

__END_DECLS


