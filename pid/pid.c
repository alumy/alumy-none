#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/errno.h"
#include "alumy/pid.h"

__BEGIN_DECLS

int32_t al_pid_init(al_pid_t *pid, float kp, float ki, float kd, double target,
                    double (*adjust)(al_pid_t *pid, double out))
{
    BUG_ON(pid == NULL);

    if (pid == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->target = target;

    pid->e = 0;
    pid->e1 = 0;
    pid->sum = 0;
    pid->adjust = adjust;

    set_errno(0);
    return 0;
}

int32_t al_pid_set_target(al_pid_t *pid, double target)
{
    BUG_ON(pid == NULL);

    if (pid == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    pid->target = target;

    set_errno(0);
    return 0;
}

int32_t al_pid_get_target(al_pid_t *pid, double *target)
{
    BUG_ON(pid == NULL || target == NULL);

    if (pid == NULL || target == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    *target = pid->target;

    set_errno(0);
    return 0;
}

int32_t al_pid_set_adjust(al_pid_t *pid,
                          double (*adjust)(al_pid_t *pid, double out))
{
    BUG_ON(pid == NULL);

    if (pid == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    pid->adjust = adjust;

    set_errno(0);
    return 0;
}

int32_t al_pid_set_param(al_pid_t *pid, float kp, float ki, float kd)
{
    if (pid == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    set_errno(0);
    return 0;
}

__END_DECLS

