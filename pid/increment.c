#include "alumy/byteorder.h"
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/errno.h"
#include "alumy/pid.h"

__BEGIN_DECLS

int32_t al_pid_inc_cal(al_pid_t *pid, double actual, double *inc)
{
    double e;
    double __inc;

    BUG_ON(pid == NULL || inc == NULL);

    if (pid == NULL || inc == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    e = pid->target - actual;

    __inc = pid->kp * e + pid->ki * pid->e + pid->kd * pid->e1;

    pid->e1 = pid->e;
    pid->e = e;

    if (pid->adjust) {
        __inc = pid->adjust(pid, __inc);
    }

    *inc = __inc;

    set_errno(0);
    return 0;
}

__END_DECLS

