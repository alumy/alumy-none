#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/errno.h"
#include "alumy/pid.h"

__BEGIN_DECLS

double al_pid_pos_cal(al_pid_t *pid, double actual)
{
    /* position */
    double p;

    pid->e = pid->target - actual;

    /* accumulated error */
    pid->sum += pid->e;

    p = pid->kp * pid->e + pid->ki * pid->sum + pid->kd * (pid->e - pid->e1);

    pid->e1 = pid->e;

    return p;
}

__END_DECLS

