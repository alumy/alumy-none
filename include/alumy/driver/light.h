#ifndef __AL_DRV_LIGHT_H
#define __AL_DRV_LIGHT_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"
#include "alumy/list.h"
#include "alumy/driver/gpio.h"

__BEGIN_DECLS

#ifndef AL_LIGHT_UPDATE_FREQ_HZ
#define AL_LIGHT_UPDATE_FREQ_HZ     100
#endif

#define AL_LIGHT_INIT(id, intv, set, user_data)     \
    { { 0 }, (id), 0, AL_LIGHT_MS_TO_TICKS((intv)), 0, (set), (user_data) }

#define AL_LIGHT_MS_TO_TICKS(ms)    ((ms) / (1000 / AL_LIGHT_UPDATE_FREQ_HZ))

enum {
    AL_LIGHT_OFF = 0,
    AL_LIGHT_ON,
    AL_LIGHT_FLASH
};

struct al_light_item;
typedef struct al_light_item al_light_item_t;

struct al_light_item {
    list_head_t link;
    uint8_t id;
    uint8_t value;
    uint16_t intv;
    uint16_t tick;
    int_t (*set)(al_light_item_t *item, bool on);
    void *user_data;
};

typedef struct al_light {
    list_head_t ls;
    uint32_t value;
} al_light_t;

int_t al_light_init(al_light_t *this);
int_t al_light_register(al_light_t *this, al_light_item_t *item);
al_light_item_t *al_light_search(al_light_t *this, uint8_t id);
int_t al_light_set(al_light_t *this, uint8_t id, int_t value, uint16_t intv);
int_t al_light_routine(al_light_t *this);

__END_DECLS

#endif

