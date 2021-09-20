#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/errno.h"
#include "alumy/pid.h"
#include "alumy/driver/boost.h"

__BEGIN_DECLS

int32_t al_boost_init(al_boost_t *boost,
                      al_pid_t *pid, al_kalman1_t *kalman,
                      const al_boost_opt_t *opt)
{
    if (boost == NULL || pid == NULL || kalman == NULL || opt == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    boost->pid = pid;
    boost->kalman = kalman;

    memcpy(&boost->opt, opt, sizeof(boost->opt));

    set_errno(0);
    return 0;
}

int32_t al_boost_final(al_boost_t *boost)
{
    UNUSED(boost);

    BUG_ON(boost == NULL);

    return 0;
}

int32_t al_boost_set_target(al_boost_t *boost, float target)
{
    BUG_ON(boost == NULL);

    boost->target = target;

    return al_pid_set_target(boost->pid, boost->target);
}

int32_t al_boost_open(al_boost_t *boost)
{
    BUG_ON(boost == NULL);

    BUG_ON(al_pid_set_target(boost->pid, 0) != 0);

    if (boost->opt.open) {
        boost->opt.open();
    }

    BUG_ON(al_pid_set_target(boost->pid, boost->target) != 0);

    return 0;
}

int32_t al_boost_close(al_boost_t *boost)
{
    BUG_ON(boost == NULL);

    BUG_ON(al_pid_set_target(boost->pid, 0) != 0);

    if (boost->opt.close) {
        return boost->opt.close();
    }

    return 0;
}

int32_t al_boost_adjust(al_boost_t *boost)
{
    double out;

    BUG_ON(boost == NULL);

    float v = boost->opt.voltage_get();

    float vk = al_kalman1_filter(boost->kalman, v);

    if(al_pid_pos_cal(boost->pid, vk, &out) != 0) {
        return -1;
    }

    float duty = boost->opt.u_to_duty(vk, out);

    boost->opt.pwm_set(duty);

    return 0;
}

__END_DECLS

