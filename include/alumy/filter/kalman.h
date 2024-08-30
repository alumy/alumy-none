#ifndef __AL_KALMAN_H
#define __AL_KALMAN_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#define AL_KALMAN1_A		(1)
#define AL_KALMAN1_H		(1)
#define AL_KALMAN1_Q		(10e-6)
#define AL_KALMAN1_R		(10e-5)

#define AL_KALMAN2_A		{ {1, 0.1}, {0, 1} }
#define AL_KALMAN2_H		{ 1, 0 }
#define AL_KALMAN2_Q		{ { 10e-6, 0 }, { 0, 10e-6 } }
#define AL_KALMAN2_R		(10e-7)

typedef float al_kf_t;

/*
 * NOTES: n Dimension means the state is n dimension,
 * measurement always 1 dimension
 */

/* 1 Dimension */
typedef struct al_kalman1 {
    al_kf_t x;        /* state */
    al_kf_t a;        /* x(n)=A*x(n-1)+u(n),u(n)~N(0,q) */
    al_kf_t h;        /* z(n)=H*x(n)+w(n),w(n)~N(0,r)   */
    al_kf_t q;        /* process(predict) noise convariance */
    al_kf_t r;        /* measure noise convariance */
    al_kf_t p;        /* estimated error convariance */
    al_kf_t gain;
} al_kalman1_t;

/* 2 Dimension */
typedef struct al_kalman2 {
    al_kf_t x[2];     /* state: [0]-angle [1]-diffrence of angle, 2x1 */
    al_kf_t a[2][2];  /* X(n)=A*X(n-1)+U(n),U(n)~N(0,q), 2x2 */
    al_kf_t h[2];     /* Z(n)=H*X(n)+W(n),W(n)~N(0,r), 1x2   */
    al_kf_t q[2];     /* process(predict) noise convariance,2x1 [q0,0; 0,q1] */
    al_kf_t r;        /* measure noise convariance */
    al_kf_t p[2][2];  /* estimated error convariance,2x2 [p0 p1; p2 p3] */
    al_kf_t gain[2];  /* 2x1 */
} al_kalman2_t;

void al_kalman1_init(al_kalman1_t *kf,
                     al_kf_t x, al_kf_t p, al_kf_t a, al_kf_t h,
                     al_kf_t q, al_kf_t r);

al_kf_t al_kalman1_filter(al_kalman1_t *kf, al_kf_t measure);

void al_kalman2_init(al_kalman2_t *k,
                     const al_kf_t x[2], const al_kf_t p[2][2],
                     const al_kf_t a[2][2], const al_kf_t h[2],
                     const al_kf_t q[2], al_kf_t r);

al_kf_t al_kalman2_filter(al_kalman2_t *k, const al_kf_t measure[2]);

__END_DECLS

#endif

