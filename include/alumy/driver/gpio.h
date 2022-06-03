#ifndef __AL_DRV_GPIO_H
#define __AL_DRV_GPIO_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef enum al_gpio {
    AL_GPIO_LOW = 0,
    AL_GPIO_HIGH
} al_gpio_t;

typedef enum al_gpio_dir {
    AL_GPIO_INPUT = 0,
    AL_GPIO_OUTPUT
} al_gpio_dir_t;

__END_DECLS

#endif

