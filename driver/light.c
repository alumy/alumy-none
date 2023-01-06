#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/check.h"
#include "alumy/errno.h"
#include "alumy/driver/light.h"
#include "alumy/bit.h"

__BEGIN_DECLS

int_t al_light_init(al_light_t *light)
{
	AL_CHECK_RET(light != NULL, EINVAL, -1);

	INIT_LIST_HEAD(&light->ls);
    light->value = 0;

	set_errno(0);
    return 0;
}

al_light_item_t *al_light_search(al_light_t *light, uint8_t id)
{
    list_head_t *pos, *n;

	AL_CHECK_RET(light != NULL, EINVAL, NULL);

    list_for_each_safe(pos, n, &light->ls) {
        al_light_item_t *item = list_entry(pos, al_light_item_t, link);

        if (item->id == id) {
            return item;
        }
    }

	set_errno(0);
    return NULL;
}

int_t al_light_register(al_light_t *light, al_light_item_t *item)
{
	AL_CHECK_RET(light != NULL, EINVAL, -1);

    if (al_light_search(light, item->id) != NULL) {
        set_errno(EEXIST);
        return -1;
    }

    if (item->id > (sizeof(light->value) << 3)) {
		set_errno(EINVAL);
        return -1;
    }

    INIT_LIST_HEAD(&item->link);
    item->tick = item->intv;

    list_add_tail(&item->link, &light->ls);

    set_errno(0);
    return 0;
}

int_t al_light_set(al_light_t *light, uint8_t id, int_t value, uint16_t intv)
{
	AL_CHECK_RET(light != NULL, EINVAL, -1);

    al_light_item_t *item = al_light_search(light, id);
    if (item == NULL) {
        set_errno(EINVAL);
        return -1;
    }
    
    if(value == item->value) {
		set_errno(0);
        return 0;
    }

    clear_bit(light->value, item->id);
    item->value = value;
    item->intv = 0;
    item->tick = 0;

    switch (item->value) {
        case AL_LIGHT_OFF:
            item->set(item, false);
            break;

        case AL_LIGHT_ON:
            item->set(item, true);
            break;

        case AL_LIGHT_FLASH:
            item->intv = intv;
            item->tick = intv;
            break;

        default:
            break;
    }

	set_errno(0);
    return 0;
}

int_t al_light_routine(al_light_t *light)
{
    int32_t cnt = 0;
    list_head_t *pos, *n;

	AL_CHECK_RET(light != NULL, EINVAL, -1);

    list_for_each_safe(pos, n, &light->ls) {
        al_light_item_t *item = list_entry(pos, al_light_item_t, link);

        if (item->intv > 0) {
            if ((--item->tick) == 0) {
                item->set(item, get_bit(light->value, item->id));
                item->tick = item->intv;

                toggle_bit(light->value, item->id);
            }
        }

        ++cnt;
    }

    return cnt;
}

__END_DECLS

