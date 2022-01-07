#include "alumy/driver/light.h"
#include "alumy/errno.h"
#include "alumy/bug.h"

__BEGIN_DECLS

int32_t al_light_init(al_light_t *this)
{
    INIT_LIST_HEAD(&this->ls);
    this->value = 0;
    return 0;
}

al_light_item_t *al_light_search(al_light_t *this, uint8_t id)
{
    list_head_t *pos, *n;

    list_for_each_safe(pos, n, &this->ls) {
        al_light_item_t *item = list_entry(pos, al_light_item_t, link);

        if (item->id == id) {
            return item;
        }
    }

    return NULL;
}

int32_t al_light_register(al_light_t *this, al_light_item_t *item)
{
    if (al_light_search(this, item->id) != NULL) {
        set_errno(EEXIST);
        return -1;
    }

    if (item->id > (sizeof(this->value) << 3)) {
        return -1;
    }

    INIT_LIST_HEAD(&item->link);
    item->tick = item->intv;

    list_add_tail(&item->link, &this->ls);

    set_errno(0);
    return 0;
}

int32_t al_light_set(al_light_t *this, uint8_t id, int32_t value, int32_t intv)
{
    al_light_item_t *item = al_light_search(this, id);
    if (item == NULL) {
        set_errno(EINVAL);
        return -1;
    }
    
    if(value == item->value) {
		set_errno(0);
        return 0;
    }

    this->value &= ~(1 << item->id);
    item->value = value;
    item->intv = 0;
    item->tick = 0;

    switch (item->value) {
        case AL_LIGHT_OFF:
            item->set(item->user_data, false);
            break;

        case AL_LIGHT_ON:
            item->set(item->user_data, true);
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

int32_t al_light_routine(al_light_t *this)
{
    int32_t cnt = 0;
    list_head_t *pos, *n;

    list_for_each_safe(pos, n, &this->ls) {
        al_light_item_t *item = list_entry(pos, al_light_item_t, link);

        if (item->intv > 0) {
            if ((--item->tick) == 0) {
                bool on = this->value & (1 << item->id) ? true : false;

                item->set(item->user_data, on);
                item->tick = item->intv;

                this->value ^= (1 << item->id);
            }
        }

        ++cnt;
    }

    return cnt;
}

__END_DECLS

