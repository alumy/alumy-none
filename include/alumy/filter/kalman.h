#ifndef __AL_KALMAN_H
#define __AL_KALMAN_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#define KALMAN_Q        0.01
#define KALMAN_R        10.00

/*
 * NOTES: n Dimension means the state is n dimension,
 * measurement always 1 dimension
 */

/* 1 Dimension */
typedef struct al_kalman1 {
    float x;        /* state */
    float a;        /* x(n)=A*x(n-1)+u(n),u(n)~N(0,q) */
    float h;        /* z(n)=H*x(n)+w(n),w(n)~N(0,r)   */
    float q;        /* process(predict) noise convariance */
    float r;        /* measure noise convariance */
    float p;        /* estimated error convariance */
    float gain;
} al_kalman1_t;

void al_kalman1_init(al_kalman1_t *kf,
                     float x, float p, float a, float h, float q, float r);

float al_kalman1_filter(al_kalman1_t *kf, float measure);

__END_DECLS

#endif

