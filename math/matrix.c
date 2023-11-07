#include <stdint.h>
#include "alumy/math/matrix.h"
#include "alumy/log.h"

__BEGIN_DECLS

/**
* \brief Initializes a matrix structure.
* \param[in] mat The matrix to initialize
* \param[in] rows The number of rows
* \param[in] cols The number of columns
* \param[in] buffer The data buffer (of size {\see rows} x {\see cols}).
*/
void al_matrix_init(al_matrix_t *const  mat,
					const uint_fast8_t rows, const uint_fast8_t cols,
					al_matrix_data_t *const buffer)
{
    mat->cols = cols;
    mat->rows = rows;
    mat->data = buffer;
}

/**
* \brief Inverts a lower triangular matrix.
* \param[in] lower The lower triangular matrix to be inverted.
* \param[out] inverse The inverse of the lower triangular matrix.
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
void al_matrix_invert_lower(const al_matrix_t *__restrict const lower,
							al_matrix_t *__restrict inverse)
{
	int_fast8_t i, j, k;
	const uint_fast8_t n = lower->rows;
	const al_matrix_data_t *const  t = lower->data;
	al_matrix_data_t *a = inverse->data;

	// TODO reorder these operations to avoid cache misses

	// inverts the lower triangular system and saves the result
	// in the upper triangle to minimize cache misses
	for (i = 0; i < n; ++i) {
		const al_matrix_data_t el_ii = t[i * n + i];

		for (j = 0; j <= i; ++j) {
			al_matrix_data_t sum;

			sum = (i == j) ? (al_matrix_data_t)1.0 : (al_matrix_data_t)0;

			for (k = i - 1; k >= j; --k) {
				sum -= t[i * n + k] * a[j * n + k];
			}
			a[j * n + i] = sum / el_ii;
		}
	}

	// solve the system and handle the previous solution being in the
	// upper triangle takes advantage of symmetry
	for (i = n - 1; i >= 0; --i) {
		const al_matrix_data_t el_ii = t[i * n + i];

		for (j = 0; j <= i; ++j) {
			al_matrix_data_t sum = (i < j) ? 0 : a[j * n + i];

			for (k = i + 1; k < n; ++k) {
				sum -= t[k * n + i] * a[j * n + k];
			}

			a[i * n + j] = a[j * n + i] = sum / el_ii;
		}
	}
}

/*!
* \brief Performs a matrix multiplication such that
* 		 {\ref c} = {\ref a} * {\ref b}
* \param[in] a Matrix A
* \param[in] b Matrix B
* \param[in] c Resulting matrix C (will be overwritten)
* \param[in] aux Auxiliary vector that can hold a column of {\ref b}
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
void al_matrix_mult(const al_matrix_t *const a,
                    const al_matrix_t *const b,
					const al_matrix_t *__restrict c,
                    al_matrix_data_t *const baux)
{
    register int_fast16_t i, j, k;
    const uint_fast8_t bcols = b->cols;
    const uint_fast8_t ccols = c->cols;
    const uint_fast8_t brows = b->rows;
    const uint_fast8_t arows = a->rows;

    al_matrix_data_t *__restrict const adata = a->data;
    al_matrix_data_t *__restrict const cdata = c->data;

    // assert pointer validity
    AL_ASSERT(a != (al_matrix_t*)0);
    AL_ASSERT(b != (al_matrix_t*)0);
    AL_ASSERT(c != (al_matrix_t*)0);
    AL_ASSERT(baux != (al_matrix_data_t*)0);

    // test dimensions of a and b
    AL_ASSERT(a->cols == b->rows);

    // test dimension of c
    AL_ASSERT(a->rows == c->rows);
    AL_ASSERT(b->cols == c->cols);

    //for (j = 0; j < bcols; ++j)
    for (j = bcols-1; j >= 0; --j)
    {
        // create a copy of the column in B to avoid cache issues
        al_matrix_get_column_copy(b, j, baux);

        uint_fast16_t indexA = 0;
        for (i = 0; i < arows; ++i)
        {
            al_matrix_data_t total = (al_matrix_data_t)0;
            for (k = 0; k < brows;)
            {
                total += adata[indexA++]*baux[k++];
            }
            cdata[i*ccols + j] = total;
        }
    }
}

/*!
* \brief Performs a matrix multiplication with transposed B such that
* 		 {\ref c} = {\ref a} * {\ref b'}
* \param[in] a Matrix A
* \param[in] b Matrix B
* \param[in] c Resulting matrix C (will be overwritten)
* \param[in] aux Auxiliary vector that can hold a column of {\ref b}
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
void al_matrix_mult_transb(const al_matrix_t *const a,
                           const al_matrix_t *const b,
						   const al_matrix_t *__restrict c)
{
    register uint_fast16_t xA, xB, indexA, indexB, end;
    const uint_fast8_t bcols = b->cols;
    const uint_fast8_t brows = b->rows;
    const uint_fast8_t arows = a->rows;
    const uint_fast8_t acols = a->cols;

    al_matrix_data_t *const adata = a->data;
    al_matrix_data_t *const bdata = b->data;
    al_matrix_data_t *__restrict const cdata = c->data;

    uint_fast16_t cIndex = 0;
    uint_fast16_t aIndexStart = 0;

    for (xA = 0; xA < arows; ++xA)
    {
        end = aIndexStart + bcols;
        indexB = 0;
        for (xB = 0; xB < brows; ++xB)
        {
            indexA = aIndexStart;
            al_matrix_data_t total = 0;

            while (indexA < end)
            {
                total += adata[indexA++] * bdata[indexB++];
            }

            cdata[cIndex++] = total;
        }
        aIndexStart += acols;
    }
}

/*!
* \brief Performs a matrix multiplication with transposed B and adds the
*   	 result to {\ref c} such that
*   	 {\ref c} = {\ref c} + {\ref a} * {\ref b'}
* \param[in] a Matrix A
* \param[in] b Matrix B
* \param[in] c Resulting matrix C
* \param[in] aux Auxiliary vector that can hold a column of {\ref b}
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
void al_matrix_multadd_transb(const al_matrix_t *const a,
                              const al_matrix_t *const b,
							  const al_matrix_t *__restrict c)
{
    register uint_fast16_t xA, xB, indexA, indexB, end;
    const uint_fast8_t bcols = b->cols;
    const uint_fast8_t brows = b->rows;
    const uint_fast8_t arows = a->rows;
    const uint_fast8_t acols = a->cols;

    al_matrix_data_t *const adata = a->data;
    al_matrix_data_t *const bdata = b->data;
    al_matrix_data_t *__restrict const cdata = c->data;

    uint_fast16_t cIndex = 0;
    uint_fast16_t aIndexStart = 0;

    for (xA = 0; xA < arows; ++xA)
    {
        end = aIndexStart + bcols;
        indexB = 0;
        for (xB = 0; xB < brows; ++xB)
        {
            indexA = aIndexStart;
            al_matrix_data_t total = 0;

            while (indexA < end)
            {
                total += adata[indexA++] * bdata[indexB++];
            }

            cdata[cIndex++] += total;
        }
        aIndexStart += acols;
    }
}

/*!
* \brief Performs a matrix multiplication with transposed B and scales the
* 		 result such that {\ref c} = {\ref a} * {\ref b'} * {\ref scale}
* \param[in] a Matrix A
* \param[in] b Matrix B
* \param[in] scale Scaling factor
* \param[in] c Resulting matrix C(will be overwritten)
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
void al_matrix_multscale_transb(const al_matrix_t *const a,
								const al_matrix_t *const b,
								register const al_matrix_data_t scale,
								const al_matrix_t *__restrict c)
{
    register uint_fast16_t xA, xB, indexA, indexB, end;
    const uint_fast8_t bcols = b->cols;
    const uint_fast8_t brows = b->rows;
    const uint_fast8_t arows = a->rows;
    const uint_fast8_t acols = a->cols;

    al_matrix_data_t *const adata = a->data;
    al_matrix_data_t *const bdata = b->data;
    al_matrix_data_t *__restrict const cdata = c->data;

    uint_fast16_t cIndex = 0;
    uint_fast16_t aIndexStart = 0;

    for (xA = 0; xA < arows; ++xA)
    {
        end = aIndexStart + bcols;
        indexB = 0;
        for (xB = 0; xB < brows; ++xB)
        {
            indexA = aIndexStart;
            al_matrix_data_t total = 0;

            while (indexA < end)
            {
                total += adata[indexA++] * bdata[indexB++];
            }

            cdata[cIndex++] = total * scale;
        }
        aIndexStart += acols;
    }
}

/*!
* \brief Performs a matrix multiplication such that {\ref c} = {\ref x} * {\ref b}
* \param[in] a Matrix A
* \param[in] x Vector x
* \param[in] c Resulting vector C (will be overwritten)
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
void al_matrix_mult_rowvector(const al_matrix_t *__restrict const a,
							  const al_matrix_t *__restrict const x,
							  al_matrix_t *__restrict const c)
{
    uint_fast16_t i, j;
    const uint_fast8_t arows = a->rows;
    const uint_fast8_t acols = a->cols;

    const al_matrix_data_t *__restrict const adata = a->data;
    const al_matrix_data_t *__restrict const xdata = x->data;
    al_matrix_data_t *__restrict const cdata = c->data;

    uint_fast16_t indexA = 0;
    uint_fast16_t cIndex = 0;
    al_matrix_data_t b0 = xdata[0];

    for (i = 0; i < arows; ++i)
    {
        al_matrix_data_t total = adata[indexA++] * b0;

        for (j = 1; j < acols; ++j)
        {
            total += adata[indexA++] * xdata[j];
        }

        cdata[cIndex++] = total;
    }
}

/*!
* \brief Performs a matrix multiplication such that
*        {\ref c} = {\ref c} + {\ref x} * {\ref b}
* \param[in] a Matrix A
* \param[in] x Vector x
* \param[in] c Resulting vector C (will be added to)
* \param[in] aux Auxiliary vector that can hold a column of {\ref b}
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
void al_matrix_multadd_rowvector(const al_matrix_t *__restrict const a,
								 const al_matrix_t *__restrict const x,
								 al_matrix_t *__restrict const c)
{
    uint_fast16_t i, j;
    const uint_fast8_t arows = a->rows;
    const uint_fast8_t acols = a->cols;

    const al_matrix_data_t *__restrict const adata = a->data;
    const al_matrix_data_t *__restrict const xdata = x->data;
    al_matrix_data_t *__restrict const cdata = c->data;

    uint_fast16_t indexA = 0;
    uint_fast16_t cIndex = 0;
    al_matrix_data_t b0 = xdata[0];

    for (i = 0; i < arows; ++i)
    {
        al_matrix_data_t total = adata[indexA++] * b0;

        for (j = 1; j < acols; ++j)
        {
            total += adata[indexA++] * xdata[j];
        }

        cdata[cIndex++] += total;
    }
}

__END_DECLS

