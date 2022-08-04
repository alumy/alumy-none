#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/errno.h"
#include "alumy/pid.h"

__BEGIN_DECLS

double al_pid_inc_cal(al_pid_t *pid, double actual)
{
    double e;
    double __inc;

    e = pid->target - actual;

    __inc = pid->kp * e + pid->ki * pid->e + pid->kd * pid->e1;

    pid->e1 = pid->e;
    pid->e = e;

    return __inc;
}

__END_DECLS

