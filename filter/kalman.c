#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/filter/kalman.h"

__BEGIN_DECLS

/**
 * @brief
 *   Init fields of structure @kalman1_state.
 *   I make some defaults in this init function:
 *     A = 1;
 *     H = 1;
 *   and @q,@r are valued after prior tests.
 *
 *   NOTES: Please change A,H,q,r according to your application.
 *
 * @inputs
 *   state - Klaman filter structure
 *   init_x - initial x state value
 *   init_p - initial estimated error convariance
 * @outputs
 * @retval
 */
void al_kalman1_init(al_kalman1_t *k,
                     float x, float p, float a, float h, float q, float r)
{
    k->x = x;
    k->p = p;
    k->a = a;
    k->h = h;
    k->q = q;       /* predict noise convariance */
    k->r = r;       /* measure error convariance */
}

/**
 * @brief
 *   1 Dimension Kalman filter
 * @inputs
 *   state - Klaman filter structure
 *   z_measure - Measure value
 * @outputs
 * @retval
 *   Estimated result
 */
float al_kalman1_filter(al_kalman1_t *k, float measure)
{
    /* Predict */
    k->x = k->a * k->x;
    /* p(n|n-1)=A^2*p(n-1|n-1)+q */
    k->p = k->a * k->a * k->p + k->q;

    /* Measurement */
    k->gain = k->p * k->h / (k->p * k->h * k->h + k->r);
    k->x = k->x + k->gain * (measure - k->h * k->x);
    k->p = (1 - k->gain * k->h) * k->p;

    return k->x;
}

/*
 * @brief
 *   Init fields of structure @kalman1_state.
 *   I make some defaults in this init function:
 *     A = {{1, 0.1}, {0, 1}};
 *     H = {1,0};
 *   and @q,@r are valued after prior tests.
 *
 *   NOTES: Please change A,H,q,r according to your application.
 *
 * @inputs
 * @outputs
 * @retval
 */
void al_kalman2_init(al_kalman2_t *k,
					 const float x[2], const float p[2][2],
					 const float a[2][2], const float h[2],
					 const float q[2], float r)
{
    k->x[0] = x[0];
    k->x[1] = x[1];

	k->p[0][0] = p[0][0];
    k->p[0][1] = p[0][1];
    k->p[1][0] = p[1][0];
    k->p[1][1] = p[1][1];

    k->a[0][0] = a[0][0];
    k->a[0][1] = a[0][1];
    k->a[1][0] = a[1][0];
    k->a[1][1] = a[1][1];

    k->h[0] = h[0];
    k->h[1] = h[1];

    k->q[0] = q[0];
    k->q[1] = q[1];
    k->r = r;  /* estimated error convariance */
}

/*
 * @brief
 *   2 Dimension kalman filter
 * @inputs
 *   state - Klaman filter structure
 *   z_measure - Measure value
 * @outputs
 *   state->x[0] - Updated state value, Such as angle,velocity
 *   state->x[1] - Updated state value, Such as diffrence angle, acceleration
 *   state->p    - Updated estimated error convatiance matrix
 * @retval
 *   Return value is equals to state->x[0], so maybe angle or velocity.
 */
float al_kalman2_filter(al_kalman2_t *k, const float measure[2])
{
	float temp = 0.0f;
	float temp0 = 0.0f;
	float temp1 = 0.0f;

	/* Step1: Predict */
	k->x[0] = k->a[0][0] * k->x[0] + k->a[0][1] * k->x[1];
	k->x[1] = k->a[1][0] * k->x[0] + k->a[1][1] * k->x[1];
	/* p(n|n-1)=A^2*p(n-1|n-1)+q */
	k->p[0][0] = k->a[0][0] * k->p[0][0] + k->a[0][1] * k->p[1][0] + k->q[0];
	k->p[0][1] = k->a[0][0] * k->p[0][1] + k->a[1][1] * k->p[1][1];
	k->p[1][0] = k->a[1][0] * k->p[0][0] + k->a[0][1] * k->p[1][0];
	k->p[1][1] = k->a[1][0] * k->p[0][1] + k->a[1][1] * k->p[1][1] + k->q[1];

	/* Step2: Measurement */
	/* gain = p * H^T * [r + H * p * H^T]^(-1), H^T means transpose. */
	temp0 = k->p[0][0] * k->h[0] + k->p[0][1] * k->h[1];
	temp1 = k->p[1][0] * k->h[0] + k->p[1][1] * k->h[1];
	temp = k->r + k->h[0] * temp0 + k->h[1] * temp1;
	k->gain[0] = temp0 / temp;
	k->gain[1] = temp1 / temp;
	/* x(n|n) = x(n|n-1) + gain(n) * [measure - H(n)*x(n|n-1)]*/
	temp = k->h[0] * k->x[0] + k->h[1] * k->x[1];
	k->x[0] = k->x[0] + k->gain[0] *(measure[0] - temp);
	k->x[1] = k->x[1] + k->gain[1] *(measure[1] - temp);

	/* Update @p: p(n|n) = [I - gain * H] * p(n|n-1) */
	k->p[0][0] = (1 - k->gain[0] * k->h[0])* k->p[0][0];
	k->p[0][1] = (1 - k->gain[0] * k->h[1])* k->p[0][1];
	k->p[1][0] = (1 - k->gain[1] * k->h[0])* k->p[1][0];
	k->p[1][1] = (1 - k->gain[1] * k->h[1])* k->p[1][1];

	return k->x[0];
}

__END_DECLS

