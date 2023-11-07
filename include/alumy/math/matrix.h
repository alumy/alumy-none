#ifndef __AL_MATH_MATRIX_H
#define __AL_MATH_MATRIX_H 1

#include <stdint.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

/**
* Matrix data type definition.
*/
typedef float al_matrix_data_t;

/**
* \brief Matrix definition
*/
typedef struct {
    /**
    * \brief Number of rows
    */
    uint_fast8_t rows;

    /**
    * \brief Number of columns
    */
    uint_fast8_t cols;

    /**
    * \brief Pointer to the data array of size {\see rows} x {\see cols}.
    */
    al_matrix_data_t *data;
} al_matrix_t;

/**
* \brief Initializes a matrix structure.
* \param[in] mat The matrix to initialize
* \param[in] rows The number of rows
* \param[in] cols The number of columns
* \param[in] buffer The data buffer (of size {\see rows} x {\see cols}).
*/
void al_matrix_init(al_matrix_t *const  mat,
					const uint_fast8_t rows, const uint_fast8_t cols,
					al_matrix_data_t *const buffer);

/**
* \brief Inverts a lower triangular matrix.
* \param[in] lower The lower triangular matrix to be inverted.
* \param[in] inverse The calculated inverse of the lower triangular matrix.
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
void al_matrix_invert_lower(const al_matrix_t *__restrict const lower,
							al_matrix_t *__restrict inverse) __hot;

/*!
* \brief Performs a matrix multiplication such that
* 		 {\ref c} = {\ref x} * {\ref b}
* \param[in] a Matrix A
* \param[in] x Vector x
* \param[in] c Resulting vector C (will be overwritten)
* \param[in] aux Auxiliary vector that can hold a column of {\ref b}
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
void al_matrix_mult_rowvector(const al_matrix_t *__restrict const a,
							  const al_matrix_t *__restrict const x,
							  al_matrix_t *__restrict const c)__hot;

/*!
* \brief Performs a matrix multiplication such that
* 		 {\ref c} = {\ref c} + {\ref x} * {\ref b}
* \param[in] a Matrix A
* \param[in] x Vector x
* \param[in] c Resulting vector C (will be added to)
* \param[in] aux Auxiliary vector that can hold a column of {\ref b}
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
void al_matrix_multadd_rowvector(const al_matrix_t *__restrict const a,
								 const al_matrix_t *__restrict const x,
								 al_matrix_t *__restrict const c) __hot;

/*!
* \brief Performs a matrix multiplication such that 
		 {\ref c} = {\ref a} * {\ref b}
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
					al_matrix_data_t *const baux) __hot;

/*!
* \brief Performs a matrix multiplication with transposed B such that 
		 {\ref c} = {\ref a} * {\ref b'}
* \param[in] a Matrix A
* \param[in] b Matrix B
* \param[in] c Resulting matrix C (will be overwritten)
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
void al_matrix_mult_transb(const al_matrix_t *const a,
						   const al_matrix_t *const b,
						   const al_matrix_t *__restrict c) __hot;

/*!
* \brief Performs a matrix multiplication with transposed B and adds the result
		 to {\ref c} such that {\ref c} = {\ref c} + {\ref a} * {\ref b'}
* \param[in] a Matrix A
* \param[in] b Matrix B
* \param[in] c Resulting matrix C (will be added to)
*
* Kudos: https://code.google.com/p/efficient-java-matrix-library
*/
void al_matrix_multadd_transb(const al_matrix_t *const a,
							  const al_matrix_t *const b,
							  const al_matrix_t *__restrict c) __hot;

/*!
* \brief Performs a matrix multiplication with transposed B and scales the 
		 result such that {\ref c} = {\ref a} * {\ref b'} * {\ref scale}
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
								const al_matrix_t *__restrict c) __hot;

/*!
* \brief Gets a matrix element
* \param[in] mat The matrix to get from
* \param[in] rows The row
* \param[in] cols The column
* \return The value at the given cell.
*/
__pure __static_inline__
al_matrix_data_t al_matrix_get(const al_matrix_t *const mat,
							   const register uint_fast8_t row,
							   const register uint_fast8_t column)
{
    register uint_fast16_t address = row * mat->cols + column;
    return mat->data[address];
}

/*!
* \brief Sets a matrix element
* \param[in] mat The matrix to set
* \param[in] rows The row
* \param[in] cols The column
* \param[in] value The value to set
*/
__static_inline__
void al_matrix_set(al_matrix_t *mat, const register uint_fast8_t row,
				   const register uint_fast8_t column,
				   const register al_matrix_data_t value)
{
    register uint_fast16_t address = row * mat->cols + column;
    mat->data[address] = value;
}

/*!
* \brief Sets matrix elements in a symmetric matrix
* \param[in] mat The matrix to set
* \param[in] rows The row
* \param[in] cols The column
* \param[in] value The value to set
*/
__static_inline__
void al_matrix_set_symmetric(al_matrix_t *mat,
							 const register uint_fast8_t row,
							 const register uint_fast8_t column,
							 const register al_matrix_data_t value)
{
    al_matrix_set(mat, row, column, value);
    al_matrix_set(mat, column, row, value);
}

/*!
* \brief Gets a pointer to a matrix row
* \param[in] mat The matrix to get from
* \param[in] rows The row
* \param[out] row_data A pointer to the given matrix row
*/
__static_inline__
void al_matrix_get_row_pointer(const al_matrix_t *const mat,
							   const register uint_fast8_t row,
							   al_matrix_data_t **row_data)
{
    register uint_fast16_t address = row * mat->cols;
    *row_data = &mat->data[address];
}

/*!
* \brief Gets a copy of a matrix column
* \param[in] mat The matrix to initialize
* \param[in] rows The column
* \param[in] row_data Pointer to an array of the correct length to hold 
			 a column of matrix {\ref mat}.
*/
__hot __static_inline__
void al_matrix_get_column_copy(const al_matrix_t *const mat,
							   const register uint_fast8_t column,
							   register al_matrix_data_t *const row_data)
{
    // start from the back, so target index is equal to the
	// index of the last row.
    register uint_fast8_t target_index = mat->rows - 1;

    // also, the source index is the column..th index
    const register int_fast16_t stride = mat->cols;
    register int_fast16_t source_index = target_index * stride + column;

    // fetch data
    row_data[target_index] = mat->data[source_index];
    while (target_index != 0)
    {
        --target_index;
        source_index -= stride;

        row_data[target_index] = mat->data[source_index];
    }
}

/*!
* \brief Gets a copy of a matrix row
* \param[in] mat The matrix to initialize
* \param[in] rows The row
* \param[in] row_data Pointer to an array of the correct length to hold 
			 a row of matrix {\ref mat}.
*/
__static_inline__
void al_matrix_get_row_copy(const al_matrix_t *const mat,
							const register uint_fast8_t row,
							register al_matrix_data_t *const row_data)
{
    register uint_fast8_t target_index = mat->cols - 1;
    register int_fast16_t source_index = (row + 1) * mat->cols - 1;

    // fetch data
    row_data[target_index] = mat->data[source_index];
    while (target_index != 0)
    {
        --target_index;
        --source_index;
        row_data[target_index] = mat->data[source_index];
    }
}

/*!
* \brief Copies the matrix from {\ref mat} to {\ref target}
* \param[in] mat The matrix to copy
* \param[in] target The matrix to copy to
*/
__static_inline__
void al_matrix_copy(const al_matrix_t *const mat, al_matrix_t *const target)
{
    register const uint_fast16_t count = mat->cols * mat->rows;
    register int_fast16_t index = 0;

    const al_matrix_data_t *__restrict const A = mat->data;
    al_matrix_data_t *__restrict const B = target->data;

    // fetch data
    for (index = count - 1; index >= 0; --index)
    {
        B[index] = A[index];
    }
}

/*!
* \brief Subtracts two matrices, using {\ref c} = {\ref a} - {\ref b}
* \param[in] a The matrix to subtract from
* \param[in] b The values to subtract
* \param[in] c The output
*/
__hot __static_inline__ void al_matrix_sub(const al_matrix_t *const a,
										   const al_matrix_t *const b,
										   const al_matrix_t *c)
{
    register const uint_fast16_t count = a->cols * a->rows;
    register int_fast16_t index = 0;

    al_matrix_data_t *__restrict const A = a->data;
    al_matrix_data_t *const B = b->data;
    al_matrix_data_t *C = c->data;

    // subtract data
    for (index = count - 1; index >= 0; --index)
    {
        C[index] = A[index] - B[index];
    }
}

/*!
* \brief Subtracts two matrices in place, using {\ref b} = {\ref a} - {\ref b}
* \param[in] a The matrix to subtract from
* \param[in] b The values to subtract, also the output
*/
__hot __static_inline__
void al_matrix_sub_inplace_b(const al_matrix_t *__restrict const a,
							 const al_matrix_t *__restrict b)
{
    register const uint_fast16_t count = a->cols * a->rows;
    register int_fast16_t index = 0;

    al_matrix_data_t *__restrict const A = a->data;
    al_matrix_data_t *__restrict B = b->data;

    // subtract data
    for (index = count - 1; index >= 0; --index)
    {
        B[index] = A[index] - B[index];
    }
}

/*!
* \brief Adds two matrices in place, using {\ref b} = {\ref a} + {\ref b}
* \param[in] a The matrix to add to, also the output
* \param[in] b The values to add
*/
__hot __static_inline__ void al_matrix_add_inplace(const al_matrix_t * a,
												   const al_matrix_t *const b)
{
    register const uint_fast16_t count = a->cols * a->rows;
    register int_fast16_t index = 0;

    al_matrix_data_t *__restrict A = a->data;
    al_matrix_data_t *__restrict const B = b->data;

    // subtract data
    for (index = count - 1; index >= 0; --index)
    {
        A[index] += B[index];
    }
}

__END_DECLS

#endif

