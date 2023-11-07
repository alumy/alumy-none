#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/test_init.h"
#include "alumy.h"
#include "test.h"

__BEGIN_DECLS

// create the filter structure
#define KALMAN_NAME gravity
#define KALMAN_NUM_STATES 3
#define KALMAN_NUM_INPUTS 0
#include "alumy/filter/kalman_factory_filter.h"

// create the measurement structure
#define KALMAN_MEASUREMENT_NAME position
#define KALMAN_NUM_MEASUREMENTS 1
#include "alumy/filter/kalman_factory_measure.h"

// clean up
#include "alumy/filter/kalman_factory_cleanup.h"

TEST_GROUP(filter_kalman);

TEST_SETUP(filter_kalman)
{

}

TEST_TEAR_DOWN(filter_kalman)
{

}

/*!
* \brief Initializes the gravity Kalman filter
*/
static void kalman_gravity_init()
{
    /************************************************************************/
    /* initialize the filter structures                                     */
    /************************************************************************/
    al_kalman_t *kf = kalman_filter_gravity_init();
    al_kalman_measure_t *kfm = kalman_filter_gravity_measure_position_init();

    /************************************************************************/
    /* set initial state                                                    */
    /************************************************************************/
    al_matrix_t *x = al_kalman_get_state_vector(kf);
    x->data[0] = 0; // s_i
    x->data[1] = 0; // v_i
    x->data[2] = 6; // g_i

    /************************************************************************/
    /* set state transition                                                 */
    /************************************************************************/
    al_matrix_t *A = al_kalman_get_state_transition(kf);

    // set time constant
    const al_matrix_data_t T = 1;

    // transition of x to s
    al_matrix_set(A, 0, 0, 1);   // 1
    al_matrix_set(A, 0, 1, T);   // T
    al_matrix_set(A, 0, 2, (al_matrix_data_t)0.5*T*T); // 0.5 * T^2

    // transition of x to v
    al_matrix_set(A, 1, 0, 0);   // 0
    al_matrix_set(A, 1, 1, 1);   // 1
    al_matrix_set(A, 1, 2, T);   // T

    // transition of x to g
    al_matrix_set(A, 2, 0, 0);   // 0
    al_matrix_set(A, 2, 1, 0);   // 0
    al_matrix_set(A, 2, 2, 1);   // 1

    /************************************************************************/
    /* set covariance                                                       */
    /************************************************************************/
    al_matrix_t *P = al_kalman_get_system_covariance(kf);

    al_matrix_set_symmetric(P, 0, 0, (al_matrix_data_t)0.1);   // var(s)
    al_matrix_set_symmetric(P, 0, 1, 0);   // cov(s,v)
    al_matrix_set_symmetric(P, 0, 2, 0);   // cov(s,g)

    al_matrix_set_symmetric(P, 1, 1, 1);   // var(v)
    al_matrix_set_symmetric(P, 1, 2, 0);   // cov(v,g)

    al_matrix_set_symmetric(P, 2, 2, 1);   // var(g)

    /************************************************************************/
    /* set measurement transformation                                       */
    /************************************************************************/
    al_matrix_t *H = al_kalman_get_measure_trans(kfm);

    al_matrix_set(H, 0, 0, 1);     // z = 1*s
    al_matrix_set(H, 0, 1, 0);     //   + 0*v
    al_matrix_set(H, 0, 2, 0);     //   + 0*g

    /************************************************************************/
    /* set process noise                                                    */
    /************************************************************************/
    al_matrix_t *R = al_kalman_get_process_noise(kfm);

    al_matrix_set(R, 0, 0, (al_matrix_data_t)0.5);     // var(s)
}

// define measurements.
//
// MATLAB source
// -------------
// s = s + v*T + g*0.5*T^2;
// v = v + g*T;
#define MEAS_COUNT (15)
static al_matrix_data_t real_distance[MEAS_COUNT] = {
    (al_matrix_data_t)0,
    (al_matrix_data_t)4.905,
    (al_matrix_data_t)19.62,
    (al_matrix_data_t)44.145,
    (al_matrix_data_t)78.48,
    (al_matrix_data_t)122.63,
    (al_matrix_data_t)176.58,
    (al_matrix_data_t)240.35,
    (al_matrix_data_t)313.92,
    (al_matrix_data_t)397.31,
    (al_matrix_data_t)490.5,
    (al_matrix_data_t)593.51,
    (al_matrix_data_t)706.32,
    (al_matrix_data_t)828.94,
    (al_matrix_data_t)961.38 };

// define measurement noise with variance 0.5
//
// MATLAB source
// -------------
// noise = 0.5^2*randn(15,1);
static al_matrix_data_t measurement_error[MEAS_COUNT] = {
    (al_matrix_data_t)0.13442,
    (al_matrix_data_t)0.45847,
    (al_matrix_data_t)-0.56471,
    (al_matrix_data_t)0.21554,
    (al_matrix_data_t)0.079691,
    (al_matrix_data_t)-0.32692,
    (al_matrix_data_t)-0.1084,
    (al_matrix_data_t)0.085656,
    (al_matrix_data_t)0.8946,
    (al_matrix_data_t)0.69236,
    (al_matrix_data_t)-0.33747,
    (al_matrix_data_t)0.75873,
    (al_matrix_data_t)0.18135,
    (al_matrix_data_t)-0.015764,
    (al_matrix_data_t)0.17869 };

/*!
* \brief Runs the gravity Kalman filter.
*/
TEST(filter_kalman, kalman_gravity)
{
    // initialize the filter
    kalman_gravity_init();

    // fetch structures
    al_kalman_t *kf = &kalman_filter_gravity;
    al_kalman_measure_t *kfm = &kalman_filter_gravity_measure_position;

    al_matrix_t *x = al_kalman_get_state_vector(kf);
    al_matrix_t *z = al_kalman_get_measure_vector(kfm);

    // filter!
    for (int i = 0; i < MEAS_COUNT; ++i)
    {
        // prediction.
        al_kalman_predict(kf);

        // measure ...
        al_matrix_data_t measurement = real_distance[i] + measurement_error[i];
        al_matrix_set(z, 0, 0, measurement);

        // update
        al_kalman_correct(kf, kfm);
    }

    // fetch estimated g
    al_matrix_data_t g_estimated = x->data[2];
    TEST_ASSERT(g_estimated > 9 && g_estimated < 10);
}

/*!
* \brief Runs the gravity Kalman filter with lambda tuning.
*/
TEST(filter_kalman, kalman_gravity_lambda)
{
    // initialize the filter
    kalman_gravity_init();

    // fetch structures
    al_kalman_t *kf = &kalman_filter_gravity;
    al_kalman_measure_t *kfm = &kalman_filter_gravity_measure_position;

    al_matrix_t *x = al_kalman_get_state_vector(kf);
    al_matrix_t *z = al_kalman_get_measure_vector(kfm);

    // forcibly increase uncertainty in every prediction step by ~20% (1/lambda^2)
    const al_matrix_data_t lambda = (al_matrix_data_t)0.9;

    // filter!
    for (int i = 0; i < MEAS_COUNT; ++i)
    {
        // prediction.
        al_kalman_predict_tuned(kf, lambda);

        // measure ...
        al_matrix_data_t measurement = real_distance[i] + measurement_error[i];
        al_matrix_set(z, 0, 0, measurement);

        // update
        al_kalman_correct(kf, kfm);
    }

    // fetch estimated g
    al_matrix_data_t g_estimated = x->data[2];
    TEST_ASSERT(g_estimated > 9 && g_estimated < 10);
}

TEST_GROUP_RUNNER(filter_kalman)
{
    RUN_TEST_CASE(filter_kalman, kalman_gravity);
    RUN_TEST_CASE(filter_kalman, kalman_gravity_lambda);
}

static int32_t __add_filter_kalman_tests(void)
{
    RUN_TEST_GROUP(filter_kalman);
    return 0;
}

al_test_suite_init(__add_filter_kalman_tests);

__END_DECLS

