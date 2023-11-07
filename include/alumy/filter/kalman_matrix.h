#ifndef __AL_FILTER_KALMAN_H
#define __AL_FILTER_KALMAN_H 1

#include <stdint.h>
#include "alumy/math/matrix.h"

__BEGIN_DECLS

/*!
* \brief Kalman Filter structure
* \see al_kalman_measure_t
*/
typedef struct al_kalman
{
    /*!
    * \brief State vector
    */
    al_matrix_t x;

    /*!
    * \brief System matrix
    * \see P
    */
    al_matrix_t A;

    /*!
    * \brief System covariance matrix
    * \see A
    */
    al_matrix_t P;

    /*!
    * \brief Input vector
    */
    al_matrix_t u;

    /*!
    * \brief Input matrix
    * \see Q
    */
    al_matrix_t B;

    /*!
    * \brief Input covariance/uncertainty matrix
    * \see B
    */
    al_matrix_t Q;

    /*!
    * \brief Temporary variables.
    */
    struct
    {
        /*!
        * \brief Auxiliary array for matrix multiplication, needs to be
		*        MAX(num states, num inputs)
        *
        * This auxiliary field can also be used as a backing field for the
		* predicted x vector, however
        * it MUST NOT be aliased with either temporary P or temporary BQ.
        */
        al_matrix_data_t *aux;

        /*!
        * \brief x-sized temporary vector
        * \see x
        */
        al_matrix_t predicted_x;

        /*!
        * \brief P-Sized temporary matrix (number of states x number of states)
        *
        * The backing field for this temporary MAY be aliased with
		* temporary BQ.
        *
        * \see P
        */
        al_matrix_t P;

        /*!
        * \brief BxQ-sized temporary matrix
				(number of states x number of inputs)
        *
        * The backing field for this temporary MAY be aliased with temporary P.
        *
        * \see B
        * \see Q
        */
        al_matrix_t BQ;

    } temporary;

} al_kalman_t;

/*!
* \brief Kalman Filter measurement structure
* \see al_kalman_t
*/
typedef struct al_kalman_measure
{
    /*!
    * \brief Measurement vector
    */
    al_matrix_t z;

    /*!
    * \brief Measurement transformation matrix
    * \see R
    */
    al_matrix_t H;

    /*!
    * \brief Process noise covariance matrix
    * \see H
    */
    al_matrix_t R;

    /*!
    * \brief Innovation vector
    */
    al_matrix_t y;

    /*!
    * \brief Residual covariance matrix
    * \see A
    */
    al_matrix_t S;

    /*!
    * \brief Kalman gain matrix
    */
    al_matrix_t K;

    /*!
    * \brief Temporary variables.
    */
    struct
    {
        /*!
        * \brief Auxiliary array for matrix multiplication, needs to be
		*        MAX(num states, num measurements)
        *
        * This auxiliary field MUST NOT be aliased with either
		* temporary HP, KHP, HPt or S_inverted.
        */
        al_matrix_data_t *aux;

        /*!
        * \brief S-Sized temporary matrix
		* 		 (number of measurements x number of measurements)
        *
        * The backing field for this temporary MAY be aliased with
		* temporary temp_KHP.
        * The backing field for this temporary MAY be aliased
		* with temporary temp_HP (if it is not aliased with temp_PHt).
        * The backing field for this temporary MUST NOT be aliased
		* with temporary temp_PHt.
        * The backing field for this temporary MUST NOT be aliased with aux.
        *
        * \see S
        */
        al_matrix_t S_inv;

        /*!
        * \brief H-Sized temporary matrix
		*       (number of measurements x number of states)
        *
        * The backing field for this temporary MAY be aliased
		* with temporary S_inv.
        * The backing field for this temporary MAY be aliased
		* with temporary temp_PHt.
        * The backing field for this temporary MUST NOT be aliased
		* with temporary temp_KHP.
        */
        al_matrix_t HP;

        /*!
        * \brief P-Sized temporary matrix (number of states x number of states)
        *
        * The backing field for this temporary MAY be aliased
		* with temporary S_inv.
        * The backing field for this temporary MAY be aliased
		* with temporary temp_PHt.
        * The backing field for this temporary MUST NOT be aliased
		* with temporary temp_HP.
        */
        al_matrix_t KHP;

        /*!
        * \brief PxH'-Sized (H'-Sized) temporary matrix
		* (number of states x number of measurements)
        *
        * The backing field for this temporary MAY be aliased
		* with temporary temp_HP.
        * The backing field for this temporary MAY be aliased
		* with temporary temp_KHP.
        * The backing field for this temporary MUST NOT be aliased
		* with temporary S_inv.
        */
        al_matrix_t PHt;

    } temporary;

} al_kalman_measure_t;

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
						   al_matrix_data_t *temp_BQ) __cold;

/*!
* \brief Sets the measurement vector
* \param[in] kfm The Kalman Filter measurement structure to initialize
* \param[in] num_states The number of states
* \param[in] num_measurements The number of measurements
* \param[in] H The measurement transformation matrix
			 ({\ref num_measurements} x {\ref num_states})
* \param[in] z The measurement vector ({\ref num_measurements} x \c 1)
* \param[in] R The process noise / measurement uncertainty
			 ({\ref num_measurements} x {\ref num_measurements})
* \param[in] y The innovation ({\ref num_measurements} x \c 1)
* \param[in] S The residual covariance ({\ref num_measurements}
			 x {\ref num_measurements})
* \param[in] K The Kalman gain ({\ref num_states}
			 x {\ref num_measurements})
* \param[in] aux The auxiliary buffer (length {\ref num_states} or
			 {\ref num_measurements}, whichever is greater)
* \param[in] S_inv The temporary matrix for the inverted residual covariance
			 ({\ref num_measurements} x {\ref num_measurements})
* \param[in] temp_HP The temporary matrix for HxP ({\ref num_measurements}
			 x {\ref num_states})
* \param[in] temp_PHt The temporary matrix for PxH' ({\ref num_states}
			 x {\ref num_measurements})
* \param[in] temp_KHP The temporary matrix for KxHxP ({\ref num_states}
			 x {\ref num_states})
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
							al_matrix_data_t *temp_KHP)__cold;

/*!
* \brief Performs the time update / prediction step of only the state vector
* \param[in] kf The Kalman Filter structure to predict with.
*
* \see kalman_predict
* \see kalman_predict_tuned
*/
void al_kalman_predict_x(register al_kalman_t *const kf) __hot;

/*!
* \brief Performs the time update / prediction step of only the
*		 state covariance matrix
* \param[in] kf The Kalman Filter structure to predict with.
*
* \see kalman_predict
* \see kalman_predict_Q_tuned
*/
void al_kalman_predict_Q(register al_kalman_t *const kf) __hot;

/*!
* \brief Performs the time update / prediction step of
*        only the state covariance matrix
* \param[in] kf The Kalman Filter structure to predict with.
*
* \see kalman_predict_tuned
* \see kalman_predict_Q
*/
void al_kalman_predict_Q_tuned(register al_kalman_t *const kf,
							   al_matrix_data_t lambda) __hot;

/*!
* \brief Performs the time update / prediction step.
* \param[in] kf The Kalman Filter structure to predict with.
* \param[in] lambda Lambda factor (\c 0 < {\ref lambda} <= \c 1) to
*			 forcibly reduce prediction certainty.
*			 Smaller values mean larger uncertainty.
*
* This call assumes that the input covariance and variables are already
* set in the filter structure.
*
* \see kalman_predict_x
* \see kalman_predict_Q
*/
__static_inline__
void al_kalman_predict(al_kalman_t *kf)
{
    /************************************************************************/
    /* Predict next state using system dynamics                             */
    /* x = A*x                                                              */
    /************************************************************************/

    al_kalman_predict_x(kf);

    /************************************************************************/
    /* Predict next covariance using system dynamics and input              */
    /* P = A*P*A' + B*Q*B'                                                  */
    /************************************************************************/

    al_kalman_predict_Q(kf);
}

/*!
* \brief Performs the time update / prediction step.
* \param[in] kf The Kalman Filter structure to predict with.
* \param[in] lambda Lambda factor (\c 0 < {\ref lambda} <= \c 1) to
* 			 forcibly reduce prediction certainty. Smaller values
*			 mean larger uncertainty.
*
* This call assumes that the input covariance and variables are already
* set in the filter structure.
*
* \see kalman_predict_x
* \see kalman_predict_Q_tuned
*/
__hot __static_inline__
void al_kalman_predict_tuned(al_kalman_t *kf, al_matrix_data_t lambda)
{
    /************************************************************************/
    /* Predict next state using system dynamics                             */
    /* x = A*x                                                              */
    /************************************************************************/

    al_kalman_predict_x(kf);

    /************************************************************************/
    /* Predict next covariance using system dynamics and input              */
    /* P = A*P*A' * 1/lambda^2 + B*Q*B'                                     */
    /************************************************************************/

    al_kalman_predict_Q_tuned(kf, lambda);
}

/*!
* \brief Performs the measurement update step.
* \param[in] kf The Kalman Filter structure to correct.
*/
void al_kalman_correct(al_kalman_t *kf, al_kalman_measure_t *kfm) __hot;

/*!
* \brief Gets a pointer to the state vector x.
* \param[in] kf The Kalman Filter structure
* \return The state vector x.
*/
__hot __pure __static_inline__
al_matrix_t *al_kalman_get_state_vector(al_kalman_t *kf)
{
    return &(kf->x);
}

/*!
* \brief Gets a pointer to the state transition matrix A.
* \param[in] kf The Kalman Filter structure
* \return The state transition matrix A.
*/
__hot __pure __static_inline__
al_matrix_t *al_kalman_get_state_transition(al_kalman_t *kf)
{
    return &(kf->A);
}

/*!
* \brief Gets a pointer to the system covariance matrix P.
* \param[in] kf The Kalman Filter structure
* \return The system covariance matrix.
*/
__pure __static_inline__
al_matrix_t *al_kalman_get_system_covariance(al_kalman_t *kf)
{
    return &(kf->P);
}

/*!
* \brief Gets a pointer to the input vector u.
* \param[in] kf The Kalman Filter structure
* \return The input vector u.
*/
__hot __pure __static_inline__
al_matrix_t *al_kalman_get_input_vector(al_kalman_t *kf)
{
    return &(kf->u);
}

/*!
* \brief Gets a pointer to the input transition matrix B.
* \param[in] kf The Kalman Filter structure
* \return The input transition matrix B.
*/
__hot __pure __static_inline__
al_matrix_t *al_kalman_get_input_transition(al_kalman_t *kf)
{
    return &(kf->B);
}

/*!
* \brief Gets a pointer to the input covariance matrix P.
* \param[in] kf The Kalman Filter structure
* \return The input covariance matrix.
*/
__hot __pure __static_inline__
al_matrix_t *al_kalman_get_input_covariance(al_kalman_t *kf)
{
    return &(kf->Q);
}

/*!
* \brief Gets a pointer to the measurement vector z.
* \param[in] kfm The Kalman Filter measurement structure.
* \return The measurement vector z.
*/
__hot __pure __static_inline__
al_matrix_t *al_kalman_get_measure_vector(al_kalman_measure_t *kfm)
{
    return &(kfm->z);
}

/*!
* \brief Gets a pointer to the measurement transformation matrix H.
* \param[in] kfm The Kalman Filter measurement structure.
* \return The measurement transformation matrix H.
*/
__hot __pure __static_inline__
al_matrix_t *al_kalman_get_measure_trans(al_kalman_measure_t *kfm)
{
    return &(kfm->H);
}

/*!
* \brief Gets a pointer to the process noise matrix R.
* \param[in] kfm The Kalman Filter measurement structure.
* \return The process noise matrix R.
*/
__hot __pure __static_inline__
al_matrix_t* al_kalman_get_process_noise(al_kalman_measure_t *kfm)
{
    return &(kfm->R);
}

__END_DECLS

#endif
