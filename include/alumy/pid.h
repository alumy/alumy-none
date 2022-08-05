#ifndef __AL_PID_H
#define __AL_PID_H 1

#include "alumy/byteorder.h"
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef struct al_pid al_pid_t;

struct al_pid {
    float kp;       /* Proportional */
    float ki;       /* Integral */
    float kd;       /* Derivative */

    float e;        /* current error */
    float e1;       /* last error */
    float sum;      /* position summary */

    double target;   /* target */
};

void al_pid_init(al_pid_t *pid, float kp, float ki, float kd, double target);

void al_pid_reset(al_pid_t *pid);

void al_pid_set_target(al_pid_t *pid, double target);

double al_pid_get_target(al_pid_t *pid);

void al_pid_set_param(al_pid_t *pid, float kp, float ki, float kd);

double al_pid_pos_cal(al_pid_t *pid, double actual);

double al_pid_inc_cal(al_pid_t *pid, double actual);

__END_DECLS

#endif

