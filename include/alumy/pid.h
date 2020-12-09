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

    double (*adjust)(al_pid_t *pid, double out);
};

int32_t al_pid_init(al_pid_t *pid, float kp, float ki, float kd, double target,
                    double (*adjust)(al_pid_t *pid, double out));

int32_t al_pid_set_target(al_pid_t *pid, double target);

int32_t al_pid_get_target(al_pid_t *pid, double *target);

int32_t al_pid_set_adjust(al_pid_t *pid,
                          double (*adjust)(al_pid_t *pid, double out));

int32_t al_pid_set_param(al_pid_t *pid, float kp, float ki, float kd);

int32_t al_pid_pos_cal(al_pid_t *pid, double actual, double *pos);

int32_t al_pid_inc_cal(al_pid_t *pid, double actual, double *inc);

__END_DECLS

#endif

