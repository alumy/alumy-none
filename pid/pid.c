#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/errno.h"
#include "alumy/pid.h"

__BEGIN_DECLS

void al_pid_init(al_pid_t *pid, float kp, float ki, float kd, double target)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->target = target;

    pid->e = 0;
    pid->e1 = 0;
    pid->sum = 0;
}

void al_pid_reset(al_pid_t *pid)
{
    pid->e = 0;
    pid->e1 = 0;
    pid->sum = 0;
}

void al_pid_set_target(al_pid_t *pid, double target)
{
    pid->target = target;
}

double al_pid_get_target(al_pid_t *pid)
{
    return pid->target;
}

void al_pid_set_param(al_pid_t *pid, float kp, float ki, float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
}

__END_DECLS

