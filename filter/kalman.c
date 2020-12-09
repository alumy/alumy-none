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
void al_kalman1_init(al_kalman1_t *kf,
                     float x, float p, float a, float h, float q, float r)
{
    kf->x = x;
    kf->p = p;
    kf->a = a;
    kf->h = h;
    kf->q = q;       /* predict noise convariance */
    kf->r = r;       /* measure error convariance */
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
float al_kalman1_filter(al_kalman1_t *kf, float measure)
{
    /* Predict */
    kf->x = kf->a * kf->x;
    /* p(n|n-1)=A^2*p(n-1|n-1)+q */
    kf->p = kf->a * kf->a * kf->p + kf->q;

    /* Measurement */
    kf->gain = kf->p * kf->h / (kf->p * kf->h * kf->h + kf->r);
    kf->x = kf->x + kf->gain * (measure - kf->h * kf->x);
    kf->p = (1 - kf->gain * kf->h) * kf->p;

    return kf->x;
}

__END_DECLS

