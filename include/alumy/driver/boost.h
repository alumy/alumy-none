#ifndef __AL_BOOST_H
#define __AL_BOOST_H 1

#include "alumy/byteorder.h"
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/filter.h"
#include "alumy/pid.h"

__BEGIN_DECLS

typedef struct al_boost_opt {
    int32_t (*open)(void);
    int32_t (*close)(void);

    float (*voltage_get)(void);
    void (*pwm_set)(float duty);
    float (*u_to_duty)(float actual, float out);
} al_boost_opt_t;

typedef struct al_boost {
    al_pid_t *pid;
    al_kalman1_t *kalman;
    al_boost_opt_t opt;
    float target;
} al_boost_t;

int32_t al_boost_init(al_boost_t *boost,
                      al_pid_t *pid, al_kalman1_t *kalman,
                      const al_boost_opt_t *opt);

int32_t al_boost_final(al_boost_t *boost);

int32_t al_boost_set_target(al_boost_t *boost, float target);

int32_t al_boost_open(al_boost_t *boost);

int32_t al_boost_close(al_boost_t *boost);

int32_t al_boost_adjust(al_boost_t *boost);

__END_DECLS

#endif
