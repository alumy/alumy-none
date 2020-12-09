#include "alumy/byteorder.h"
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/errno.h"
#include "alumy/pid.h"

__BEGIN_DECLS

int32_t al_pid_pos_cal(al_pid_t *pid, double actual, double *pos)
{
    /* position */
    double p;

    BUG_ON(pid == NULL || pos == NULL);

    if (pid == NULL || pos == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    pid->e = pid->target - actual;

    /* accumulated error */
    pid->sum += pid->e;

    p = pid->kp * pid->e + pid->ki * pid->sum + pid->kd * (pid->e - pid->e1);

    pid->e1 = pid->e;

    if (pid->adjust) {
        p = pid->adjust(pid, p);
    }

    *pos = p;

    set_errno(0);
    return 0;
}

__END_DECLS

