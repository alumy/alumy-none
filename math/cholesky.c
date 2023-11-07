#include <assert.h>
#include <stdint.h>
#include <math.h>
#include "alumy/math/matrix.h"
#include "alumy/log.h"

__BEGIN_DECLS

/**
* \brief Decomposes a matrix into lower triangular form using Cholesky decomposition.
* \param[in] mat The matrix to decompose in place into a lower triangular matrix.
* \return Zero in case of success, nonzero if the matrix is not positive semi-definite.
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
int_t al_cholesky_decompose_lower(register const al_matrix_t *const mat)
{
    uint_fast8_t i, j;
    uint_fast8_t n = mat->rows;
    al_matrix_data_t *t = mat->data;

    al_matrix_data_t el_ii;
    al_matrix_data_t div_el_ii = 0;

    AL_ASSERT(mat != (al_matrix_t*)0);
    AL_ASSERT(mat->rows == mat->cols);
    AL_ASSERT(mat->rows > 0);

    for( i = 0; i < n; ++i )
    {
        for( j = i; j < n; ++j )
        {
            al_matrix_data_t sum = t[i*n+j];

            uint_fast16_t iEl = i*n;
            uint_fast16_t jEl = j*n;
            uint_fast16_t end = iEl+i;
            // k = 0:i-1
            for( ; iEl<end; ++iEl,++jEl )
            {
                // sum -= el[i*n+k]*el[j*n+k];
                sum -= t[iEl]* t[jEl];
            }

            if( i == j )
            {
                // is it positive-definite?
                if( sum <= 0.0 ) return 1;

                el_ii = (al_matrix_data_t)sqrt(sum);
                t[i*n+i] = el_ii;
                div_el_ii = (al_matrix_data_t)1.0/el_ii;
            }
            else
            {
                t[j*n+i] = sum*div_el_ii;
            }
        }
    }

    // zero the top right corner.
    for( i = 0; i < n; ++i )
    {
        for( j = i+1; j < n; ++j )
        {
            t[i*n+j] = 0.0;
        }
    }

    return 0;
}

__END_DECLS

