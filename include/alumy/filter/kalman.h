#ifndef __AL_KALMAN_H
#define __AL_KALMAN_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#define KALMAN_Q        0.01
#define KALMAN_R        10.00
#define AL_KALMAN2_A		{ {1, 0.1}, {0, 1} }
#define AL_KALMAN2_H		{ 1, 0 }
#define AL_KALMAN2_Q		{ { 10e-6, 0 }, { 0, 10e-6 } }
#define AL_KALMAN2_R		(10e-7)

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

/* 2 Dimension */
typedef struct al_kalman2 {
    float x[2];     /* state: [0]-angle [1]-diffrence of angle, 2x1 */
    float a[2][2];  /* X(n)=A*X(n-1)+U(n),U(n)~N(0,q), 2x2 */
    float h[2];     /* Z(n)=H*X(n)+W(n),W(n)~N(0,r), 1x2   */
    float q[2];     /* process(predict) noise convariance,2x1 [q0,0; 0,q1] */
    float r;        /* measure noise convariance */
    float p[2][2];  /* estimated error convariance,2x2 [p0 p1; p2 p3] */
    float gain[2];  /* 2x1 */
} al_kalman2_t;

void al_kalman1_init(al_kalman1_t *kf,
                     float x, float p, float a, float h, float q, float r);

float al_kalman1_filter(al_kalman1_t *kf, float measure);

void al_kalman2_init(al_kalman2_t *k,
					 const float x[2], const float p[2][2],
					 const float a[2][2], const float h[2],
					 const float q[2], float r);

float al_kalman2_filter(al_kalman2_t *k, float measure);

__END_DECLS

#endif

