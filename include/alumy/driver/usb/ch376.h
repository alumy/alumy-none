#ifndef __AL_DRV_USB_CH376_H
#define __AL_DRV_USB_CH376_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/base.h"
#include "alumy/types.h"

__BEGIN_DECLS


typedef struct ch376_opt {
    int32_t (*gpio_init)(void);
    int32_t (*spi_init)(void);
} ch376_opt_t;


__END_DECLS

#endif

