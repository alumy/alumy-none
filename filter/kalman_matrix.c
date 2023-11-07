#include <stdint.h>

#include "alumy/math/cholesky.h"
#include "alumy/filter/kalman_matrix.h"

__BEGIN_DECLS

/*!
* \brief Initializes the Kalman Filter
* \param[in] kf The Kalman Filter structure to initialize
* \param[in] num_states The number of state variables
* \param[in] num_inputs The number of input variables
* \param[in] A The state transition matrix ({\ref num_states}
*			 x {\ref num_states})
* \param[in] x The state vector ({\ref num_states} x \c 1)
* \param[in] B The input transition matrix ({\ref num_states}
*			 x {\ref num_inputs})
* \param[in] u The input vector ({\ref num_inputs} x \c 1)
* \param[in] P The state covariance matrix ({\ref num_states}
*			 x {\ref num_states})
* \param[in] Q The input covariance matrix ({\ref num_inputs}
*			 x {\ref num_inputs})
* \param[in] aux The auxiliary buffer (length {\ref num_states} or
*			 {\ref num_inputs}, whichever is greater)
* \param[in] predictedX The temporary vector for predicted
*			 X ({\ref num_states} x \c 1)
* \param[in] temp_P The temporary matrix for P calculation
*			 ({\ref num_states} x {\ref num_states})
* \param[in] temp_BQ The temporary matrix for BQ calculation
*			 ({\ref num_states} x {\ref num_inputs})
*/
void al_kalman_filter_init(al_kalman_t *kf,
						   uint_fast8_t num_states,
						   uint_fast8_t num_inputs,
						   al_matrix_data_t *A, al_matrix_data_t *x,
						   al_matrix_data_t *B, al_matrix_data_t *u,
						   al_matrix_data_t *P, al_matrix_data_t *Q,
						   al_matrix_data_t *aux,
						   al_matrix_data_t *predictedX,
						   al_matrix_data_t *temp_P,
						   al_matrix_data_t *temp_BQ)
{
    al_matrix_init(&kf->A, num_states, num_states, A);
    al_matrix_init(&kf->P, num_states, num_states, P);
    al_matrix_init(&kf->x, num_states, 1, x);

    al_matrix_init(&kf->B, num_states, num_inputs, B);
    al_matrix_init(&kf->Q, num_inputs, num_inputs, Q);
    al_matrix_init(&kf->u, num_inputs, 1, u);

    // set auxiliary vector
    kf->temporary.aux = aux;

    // set predicted x vector
    al_matrix_init(&kf->temporary.predicted_x, num_states, 1, predictedX);

    // set temporary P al_matrix
    al_matrix_init(&kf->temporary.P, num_states, num_states, temp_P);

    // set temporary BQ al_matrix
    al_matrix_init(&kf->temporary.BQ, num_states, num_inputs, temp_BQ);
}


/*!
* \brief Sets the measurement vector
* \param[in] kfm The Kalman Filter measurement structure to initialize
* \param[in] num_states The number of states
* \param[in] num_measurements The number of measurements
* \param[in] H The measurement transformation matrix
*			 ({\ref num_measurements} x {\ref num_states})
* \param[in] z The measurement vector ({\ref num_measurements} x \c 1)
* \param[in] R The process noise / measurement uncertainty
*			 ({\ref num_measurements} x {\ref num_measurements})
* \param[in] y The innovation ({\ref num_measurements} x \c 1)
* \param[in] S The residual covariance ({\ref num_measurements}
*			 x {\ref num_measurements})
* \param[in] K The Kalman gain ({\ref num_states} x {\ref num_measurements})
* \param[in] aux The auxiliary buffer (length {\ref num_states} or
*			 {\ref num_measurements}, whichever is greater)
* \param[in] S_inv The temporary matrix for the inverted residual covariance
*			 ({\ref num_measurements} x {\ref num_measurements})
* \param[in] temp_HP The temporary matrix for HxP ({\ref num_measurements}
*			 x {\ref num_states})
* \param[in] temp_PHt The temporary matrix for PxH' ({\ref num_states}
*			 x {\ref num_measurements})
* \param[in] temp_KHP The temporary matrix for KxHxP ({\ref num_states}
*			 x {\ref num_states})
*/
void al_kalman_measure_init(al_kalman_measure_t *kfm,
							uint_fast8_t num_states,
							uint_fast8_t num_measurements,
							al_matrix_data_t *H, al_matrix_data_t *z,
							al_matrix_data_t *R, al_matrix_data_t *y,
							al_matrix_data_t *S, al_matrix_data_t *K,
							al_matrix_data_t *aux, al_matrix_data_t *S_inv,
							al_matrix_data_t *temp_HP,
							al_matrix_data_t *temp_PHt,
							al_matrix_data_t *temp_KHP)
{
    al_matrix_init(&kfm->H, num_measurements, num_states, H);
    al_matrix_init(&kfm->R, num_measurements, num_measurements, R);
    al_matrix_init(&kfm->z, num_measurements, 1, z);

    al_matrix_init(&kfm->K, num_states, num_measurements, K);
    al_matrix_init(&kfm->S, num_measurements, num_measurements, S);
    al_matrix_init(&kfm->y, num_measurements, 1, y);

    // set auxiliary vector
    kfm->temporary.aux = aux;

    // set inverted S matrix
    al_matrix_init(&kfm->temporary.S_inv, num_measurements, num_measurements, S_inv);

    // set temporary HxP matrix
    al_matrix_init(&kfm->temporary.HP, num_measurements, num_states, temp_HP);

    // set temporary PxH' matrix
    al_matrix_init(&kfm->temporary.PHt, num_states, num_measurements, temp_PHt);

    // set temporary KxHxP matrix
    al_matrix_init(&kfm->temporary.KHP, num_states, num_states, temp_KHP);
}

/*!
* \brief Performs the time update / prediction step of only the state vector
* \param[in] kf The Kalman Filter structure to predict with.
*/
void al_kalman_predict_x(register al_kalman_t *const kf)
{
    // matrices and vectors
    const al_matrix_t *__restrict const A = &kf->A;
    al_matrix_t *__restrict const x = &kf->x;

    // temporaries
    al_matrix_t *__restrict const xpredicted = &kf->temporary.predicted_x;

    /************************************************************************/
    /* Predict next state using system dynamics                             */
    /* x = A*x                                                              */
    /************************************************************************/

    // x = A*x
    al_matrix_mult_rowvector(A, x, xpredicted);
    al_matrix_copy(xpredicted, x);
}

/*!
* \brief Performs the time update / prediction step of only the
*		 state covariance matrix
* \param[in] kf The Kalman Filter structure to predict with.
*/
void al_kalman_predict_Q(register al_kalman_t *const kf)
{
    // matrices and vectors
    const al_matrix_t *__restrict const A = &kf->A;
    const al_matrix_t *__restrict const B = &kf->B;
    al_matrix_t *__restrict const P = &kf->P;

    // temporaries
    al_matrix_data_t *__restrict const aux = kf->temporary.aux;
    al_matrix_t *__restrict const P_temp = &kf->temporary.P;
    al_matrix_t *__restrict const BQ_temp = &kf->temporary.BQ;

    /************************************************************************/
    /* Predict next covariance using system dynamics and input              */
    /* P = A*P*A' + B*Q*B'                                                  */
    /************************************************************************/

    // P = A*P*A'
    al_matrix_mult(A, P, P_temp, aux);                 // temp = A*P
    al_matrix_mult_transb(P_temp, A, P);               // P = temp*A'

    // P = P + B*Q*B'
    if (kf->B.rows > 0)
    {
        al_matrix_mult(B, &kf->Q, BQ_temp, aux);       // temp = B*Q
        al_matrix_multadd_transb(BQ_temp, B, P);       // P += temp*B'
    }
}

/*!
* \brief Performs the time update / prediction step of only the
*		 state covariance matrix
* \param[in] kf The Kalman Filter structure to predict with.
*/
void al_kalman_predict_Q_tuned(register al_kalman_t *const kf,
							   al_matrix_data_t lambda)
{
    // matrices and vectors
    const al_matrix_t *__restrict const A = &kf->A;
    const al_matrix_t *__restrict const B = &kf->B;
    al_matrix_t *__restrict const P = &kf->P;

    // temporaries
    al_matrix_data_t *__restrict const aux = kf->temporary.aux;
    al_matrix_t *__restrict const P_temp = &kf->temporary.P;
    al_matrix_t *__restrict const BQ_temp = &kf->temporary.BQ;

    /************************************************************************/
    /* Predict next covariance using system dynamics and input              */
    /* P = A*P*A' * 1/lambda^2 + B*Q*B'                                     */
    /************************************************************************/

    // lambda = 1/lambda^2
	// TODO: This should be precalculated,
	// e.g. using al_kalman_set_lambda(...);
    lambda = (al_matrix_data_t)1.0 / (lambda * lambda);

    // P = A*P*A'
	// temp = A*P
    al_matrix_mult(A, P, P_temp, aux);
	// P = temp*A' * 1/(lambda^2)
    al_matrix_multscale_transb(P_temp, A, lambda, P);

    // P = P + B*Q*B'
    if (kf->B.rows > 0)
    {
        al_matrix_mult(B, &kf->Q, BQ_temp, aux);       // temp = B*Q
        al_matrix_multadd_transb(BQ_temp, B, P);        // P += temp*B'
    }
}

/*!
* \brief Performs the measurement update step.
* \param[in] kf The Kalman Filter structure to correct.
*/
void al_kalman_correct(al_kalman_t *kf, al_kalman_measure_t *kfm)
{
    al_matrix_t *__restrict const P = &kf->P;
    const al_matrix_t *__restrict const H = &kfm->H;
    al_matrix_t *__restrict const K = &kfm->K;
    al_matrix_t *__restrict const S = &kfm->S;
    al_matrix_t *__restrict const y = &kfm->y;
    al_matrix_t *__restrict const x = &kf->x;

    // temporaries
    al_matrix_data_t *__restrict const aux = kfm->temporary.aux;
    al_matrix_t *__restrict const Sinv = &kfm->temporary.S_inv;
    al_matrix_t *__restrict const temp_HP = &kfm->temporary.HP;
    al_matrix_t *__restrict const temp_KHP = &kfm->temporary.KHP;
    al_matrix_t *__restrict const temp_PHt = &kfm->temporary.PHt;

    /************************************************************************/
    /* Calculate innovation and residual covariance                         */
    /* y = z - H*x                                                          */
    /* S = H*P*H' + R                                                       */
    /************************************************************************/

    // y = z - H*x
    al_matrix_mult_rowvector(H, x, y);
    al_matrix_sub_inplace_b(&kfm->z, y);

    // S = H*P*H' + R
    al_matrix_mult(H, P, temp_HP, aux);            // temp = H*P
    al_matrix_mult_transb(temp_HP, H, S);          // S = temp*H'
    al_matrix_add_inplace(S, &kfm->R);             // S += R

    /************************************************************************/
    /* Calculate Kalman gain                                                */
    /* K = P*H' * S^-1                                                      */
    /************************************************************************/

    // K = P*H' * S^-1
    al_cholesky_decompose_lower(S);
    al_matrix_invert_lower(S, Sinv);               // Sinv = S^-1
    // NOTE that to allow aliasing of Sinv and temp_PHt,
	// a copy must be performed here
    al_matrix_mult_transb(P, H, temp_PHt);         // temp = P*H'
    al_matrix_mult(temp_PHt, Sinv, K, aux);        // K = temp*Sinv

    /************************************************************************/
    /* Correct state prediction                                             */
    /* x = x + K*y                                                          */
    /************************************************************************/

    // x = x + K*y
    al_matrix_multadd_rowvector(K, y, x);

    /************************************************************************/
    /* Correct state covariances                                            */
    /* P = (I-K*H) * P                                                      */
    /*   = P - K*(H*P)                                                      */
    /************************************************************************/

    // P = P - K*(H*P)
    al_matrix_mult(H, P, temp_HP, aux);            // temp_HP = H*P
    al_matrix_mult(K, temp_HP, temp_KHP, aux);     // temp_KHP = K*temp_HP
    al_matrix_sub(P, temp_KHP, P);                 // P -= temp_KHP
}

__END_DECLS

