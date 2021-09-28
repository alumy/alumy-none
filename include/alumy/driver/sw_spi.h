#ifndef __AL_SW_SPI_H
#define __AL_SW_SPI_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"
#include "alumy/driver/gpio.h"

__BEGIN_DECLS

typedef struct sw_spi_opt {
    int32_t (*gpio_init)(void);
    int32_t (*gpio_final)(void);
    void (*delay)(void);
    void (*sck_set)(al_gpio_t level);
    void (*mosi_set)(al_gpio_t level);
    al_gpio_t (*miso_get)(void);
    void (*nss_set)(al_gpio_t level);
} sw_spi_opt_t;

typedef struct sw_spi {
    sw_spi_opt_t opt;
} sw_spi_t;

int_fast8_t sw_spi_init(sw_spi_t *spi, const sw_spi_opt_t *opt);

int_fast8_t sw_spi_final(sw_spi_t *spi);

uint8_t sw_spi_read_write_byte(sw_spi_t *spi, uint8_t byte);

__END_DECLS

#endif

