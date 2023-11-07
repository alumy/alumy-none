#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "alumy/test_init.h"
#include "alumy.h"
#include "test.h"

__BEGIN_DECLS

TEST_GROUP(math_matrix);

TEST_SETUP(math_matrix)
{

}

TEST_TEAR_DOWN(math_matrix)
{

}

TEST(math_matrix, matrix_inverse)
{
    int_t ret;

    // data buffer for the original and decomposed matrix
    al_matrix_data_t d[3 * 3] = {
		1, 0.5, 0,
        0.5, 1, 0,
        0, 0, 1 };

    // data buffer for the inverted matrix
    al_matrix_data_t di[3 * 3] = {
		0, 0, 0,
        0, 0, 0,
        0, 0, 0 };

    // prepare matrix structures
    al_matrix_t m, mi;

    // initialize the matrices
    al_matrix_init(&m, 3, 3, d);
    al_matrix_init(&mi, 3, 3, di);

    // decompose matrix to lower triangular
    ret = al_cholesky_decompose_lower(&m);
	TEST_ASSERT(ret == 0);

    // invert matrix using lower triangular
    al_matrix_invert_lower(&m, &mi);

    // test the result
    al_matrix_data_t test = al_matrix_get(&mi, 1, 1);
    TEST_ASSERT(test >= 1.3);
}

TEST(math_matrix, matrix_copy_cols_and_rows)
{
    // data buffer for the original and decomposed matrix
    al_matrix_data_t d[3 * 4] = { 1, 2, 3, 10,
        4, 5, 6, 11,
        7, 8, 9, 12 };

    // data buffer for the copied row
    al_matrix_data_t v[4] = { 0, 0, 0 };
    al_matrix_data_t *vp;

    // prepare matrix structure
    al_matrix_t m;

    // initialize the matrix
    al_matrix_init(&m, 3, 4, d);

    // fetch the column
    al_matrix_get_column_copy(&m, 2, v);
    TEST_ASSERT(v[0] == 3);
    TEST_ASSERT(v[1] == 6);
    TEST_ASSERT(v[2] == 9);

    // fetch the row
    al_matrix_get_row_copy(&m, 2, v);
    TEST_ASSERT(v[0] == 7);
    TEST_ASSERT(v[1] == 8);
    TEST_ASSERT(v[2] == 9);
    TEST_ASSERT(v[3] == 12);

    // fetch the row
    al_matrix_get_row_pointer(&m, 2, &vp);
    TEST_ASSERT(vp[0] == 7);
    TEST_ASSERT(vp[1] == 8);
    TEST_ASSERT(vp[2] == 9);
    TEST_ASSERT(vp[3] == 12);
}

/*!
*  \brief Tests matrix multiplication
*/
TEST(math_matrix, matrix_multiply_aux)
{
    al_matrix_data_t ad[3 * 3] = { 1, 0.5, 0,
        0.5, 1, 0,
        0, 0, 1 };

    al_matrix_data_t bd[3 * 4] = { 1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12 };

    al_matrix_data_t cd[3 * 4] = { 0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0 };

    al_matrix_data_t aux[3] = { 0, 0, 0 };

    // prepare matrix structures
    al_matrix_t a, b, c;

    // initialize the matrices
    al_matrix_init(&a, 3, 3, ad);
    al_matrix_init(&b, 3, 4, bd);
    al_matrix_init(&c, 3, 4, cd);

    // multiply
    al_matrix_mult(&a, &b, &c, aux);
    TEST_ASSERT(cd[0] == 3.5);
    TEST_ASSERT(cd[1] == 5);
    TEST_ASSERT(cd[4] == 5.5);
    TEST_ASSERT(cd[11] == 12);
}

/*!
*  \brief Tests matrix multiplication with transposed B
*/
TEST(math_matrix, matrix_multiply_transb)
{
    al_matrix_data_t ad[3 * 3] = { 1, 0.5, 0,
        0.5, 1, 0,
        0, 0, 1 };

    al_matrix_data_t bd[3 * 3] = { 1, 2, 3,
        5, 6, 7,
        9, 10, 11 };

    al_matrix_data_t cd[3 * 3] = { 0, 0, 0,
        0, 0, 0,
        0, 0, 0 };

    // prepare matrix structures
    al_matrix_t a, b, c;

    // initialize the matrices
    al_matrix_init(&a, 3, 3, ad);
    al_matrix_init(&b, 3, 3, bd);
    al_matrix_init(&c, 3, 3, cd);

    // multiply
    al_matrix_mult_transb(&a, &b, &c);
    TEST_ASSERT(cd[0] == 2);
    TEST_ASSERT(cd[1] == 8);
    TEST_ASSERT(cd[4] == 8.5);
    TEST_ASSERT(cd[8] == 11);
}

/*!
*  \brief Tests matrix multiplication with transposed B
*/
TEST(math_matrix, matrix_multscale_transb)
{
    al_matrix_data_t ad[3 * 3] = { 1, 0.5, 0,
        0.5, 1, 0,
        0, 0, 1 };

    al_matrix_data_t bd[3 * 3] = { 1, 2, 3,
        5, 6, 7,
        9, 10, 11 };

    al_matrix_data_t cd[3 * 3] = { 0, 0, 0,
        0, 0, 0,
        0, 0, 0 };

    // prepare matrix structures
    al_matrix_t a, b, c;

    // initialize the matrices
    al_matrix_init(&a, 3, 3, ad);
    al_matrix_init(&b, 3, 3, bd);
    al_matrix_init(&c, 3, 3, cd);

    // multiply
    al_matrix_multscale_transb(&a, &b, 2, &c);
    TEST_ASSERT(cd[0] == 2 * 2);
    TEST_ASSERT(cd[1] == 8 * 2);
    TEST_ASSERT(cd[4] == 8.5 * 2);
    TEST_ASSERT(cd[8] == 11 * 2);
}

/*!
*  \brief Tests matrix multiplication with transposed B
*/
TEST(math_matrix, matrix_multadd_transb)
{
    al_matrix_data_t ad[3 * 3] = { 1, 0.5, 0,
        0.5, 1, 0,
        0, 0, 1 };

    al_matrix_data_t bd[3 * 3] = { 1, 2, 3,
        5, 6, 7,
        9, 10, 11 };

    al_matrix_data_t cd[3 * 3] = { 10, 20, 30,
        40, 50, 60,
        70, 80, 90 };

    // prepare matrix structures
    al_matrix_t a, b, c;

    // initialize the matrices
    al_matrix_init(&a, 3, 3, ad);
    al_matrix_init(&b, 3, 3, bd);
    al_matrix_init(&c, 3, 3, cd);

    // multiply
    al_matrix_multadd_transb(&a, &b, &c);
    TEST_ASSERT(cd[0] == 2 + 10);
    TEST_ASSERT(cd[1] == 8 + 20);
    TEST_ASSERT(cd[4] == 8.5 + 50);
    TEST_ASSERT(cd[8] == 11 + 90);
}

/*!
*  \brief Tests matrix multiplication
*/
TEST(math_matrix, matrix_multiply_vector)
{
    al_matrix_data_t ad[3 * 3] = { 1, 0.5, 0,
        0.5, 1, 0,
        0, 0, 1 };

    al_matrix_data_t bd[3 * 1] = { 1, 2, 3 };

    al_matrix_data_t cd[3 * 1] = { 1, 2, 3 };

    // prepare matrix structures
    al_matrix_t a, b, c;

    // initialize the matrices
    al_matrix_init(&a, 3, 3, ad);
    al_matrix_init(&b, 3, 1, bd);
    al_matrix_init(&c, 3, 1, cd);

    // multiply
    al_matrix_mult_rowvector(&a, &b, &c);
    TEST_ASSERT(cd[0] == 2);
    TEST_ASSERT(cd[1] == 2.5);
    TEST_ASSERT(cd[2] == 3);
}

/*!
*  \brief Tests matrix multiplication
*/
TEST(math_matrix, matrix_multiplyadd_vector)
{
    al_matrix_data_t ad[3 * 3] = { 1, 0.5, 0,
        0.5, 1, 0,
        0, 0, 1 };

    al_matrix_data_t bd[3 * 1] = { 1, 2, 3 };

    al_matrix_data_t cd[3 * 1] = { 10, 20, 30 };

    // prepare matrix structures
    al_matrix_t a, b, c;

    // initialize the matrices
    al_matrix_init(&a, 3, 3, ad);
    al_matrix_init(&b, 3, 1, bd);
    al_matrix_init(&c, 3, 1, cd);

    // multiply
    al_matrix_multadd_rowvector(&a, &b, &c);
    TEST_ASSERT(cd[0] == 12);
    TEST_ASSERT(cd[1] == 22.5);
    TEST_ASSERT(cd[2] == 33);
}

/*!
*  \brief Tests matrix addition with B
*/
TEST(math_matrix, matrix_add_inplace)
{
    al_matrix_data_t ad[3 * 3] = { 1, 0.5, 0,
        0.5, 1, 0,
        0, 0, 1 };

    al_matrix_data_t bd[3 * 3] = { 1, 2, 3,
        5, 6, 7,
        9, 10, 11 };

    // prepare matrix structures
    al_matrix_t a, b;

    // initialize the matrices
    al_matrix_init(&a, 3, 3, ad);
    al_matrix_init(&b, 3, 3, bd);

    // multiply
    al_matrix_add_inplace(&a, &b);
    TEST_ASSERT(ad[0] == 2);
    TEST_ASSERT(ad[1] == 2.5);
    TEST_ASSERT(ad[4] == 7);
    TEST_ASSERT(ad[8] == 12);
}

/*!
*  \brief Tests matrix subtraction with B
*/
TEST(math_matrix, matrix_sub_inplace_b)
{
    al_matrix_data_t ad[3 * 3] = { 1, 0.5, 0,
        0.5, 1, 0,
        0, 0, 1 };

    al_matrix_data_t bd[3 * 3] = { 1, 2, 3,
        5, 6, 7,
        9, 10, 11 };

    // prepare matrix structures
    al_matrix_t a, b;

    // initialize the matrices
    al_matrix_init(&a, 3, 3, ad);
    al_matrix_init(&b, 3, 3, bd);

    // multiply
    al_matrix_sub_inplace_b(&a, &b);
    TEST_ASSERT(bd[0] == 1 - 1);
    TEST_ASSERT(bd[1] == 0.5 - 2);
    TEST_ASSERT(bd[4] == 1 - 6);
    TEST_ASSERT(bd[8] == 1 - 11);
}

/*!
*  \brief Tests matrix subtraction with B
*/
TEST(math_matrix, matrix_sub)
{
    al_matrix_data_t ad[3 * 3] = { 1, 0.5, 0,
        0.5, 1, 0,
        0, 0, 1 };

    al_matrix_data_t bd[3 * 3] = { 1, 2, 3,
        5, 6, 7,
        9, 10, 11 };

    // prepare matrix structures
    al_matrix_t a, b;

    // initialize the matrices
    al_matrix_init(&a, 3, 3, ad);
    al_matrix_init(&b, 3, 3, bd);

    // multiply
    al_matrix_sub(&a, &b, &a);
    TEST_ASSERT(ad[0] == 1 - 1);
    TEST_ASSERT(ad[1] == 0.5 - 2);
    TEST_ASSERT(ad[4] == 1 - 6);
    TEST_ASSERT(ad[8] == 1 - 11);
}

/*!
*  \brief Tests matrix copying
*/
TEST(math_matrix, matrix_copy)
{
    al_matrix_data_t ad[3 * 3] = { 1, 0.5, 0,
        0.5, 1, 0,
        0, 0, 1 };

    al_matrix_data_t bd[3 * 3] = { 1, 2, 3,
        5, 6, 7,
        9, 10, 11 };

    // prepare matrix structures
    al_matrix_t a, b;

    // initialize the matrices
    al_matrix_init(&a, 3, 3, ad);
    al_matrix_init(&b, 3, 3, bd);

    // multiply
    al_matrix_copy(&b, &a);
    TEST_ASSERT(ad[0] == 1);
    TEST_ASSERT(ad[1] == 2);
    TEST_ASSERT(ad[4] == 6);
    TEST_ASSERT(ad[8] == 11);
}

TEST_GROUP_RUNNER(math_matrix)
{
    RUN_TEST_CASE(math_matrix, matrix_inverse);
	RUN_TEST_CASE(math_matrix, matrix_copy_cols_and_rows);
	RUN_TEST_CASE(math_matrix, matrix_multiply_aux);
	RUN_TEST_CASE(math_matrix, matrix_multiply_transb);
	RUN_TEST_CASE(math_matrix, matrix_multscale_transb);
	RUN_TEST_CASE(math_matrix, matrix_multadd_transb);
	RUN_TEST_CASE(math_matrix, matrix_multiply_vector);
	RUN_TEST_CASE(math_matrix, matrix_multiplyadd_vector);
	RUN_TEST_CASE(math_matrix, matrix_add_inplace);
	RUN_TEST_CASE(math_matrix, matrix_sub_inplace_b);
	RUN_TEST_CASE(math_matrix, matrix_sub);
	RUN_TEST_CASE(math_matrix, matrix_copy);
}

static int32_t __add_math_al_matrix_tests(void)
{
    RUN_TEST_GROUP(math_matrix);
    return 0;
}

al_test_suite_init(__add_math_al_matrix_tests);

__END_DECLS

