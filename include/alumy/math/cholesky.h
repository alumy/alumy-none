#ifndef __AL_MATH_CHOLESKY_H
#define __AL_MATH_CHOLESKY_H 1

#include "alumy/math/matrix.h"

__BEGIN_DECLS

/**
* \brief Decomposes a matrix into lower triangular form using Cholesky decomposition.
* \param[in] mat The matrix to decompose in place into a lower triangular matrix.
* \return Zero in case of success, nonzero if the matrix is not positive semi-definite.
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
int_t al_cholesky_decompose_lower(register const al_matrix_t *const mat) __hot;

__END_DECLS

#endif

