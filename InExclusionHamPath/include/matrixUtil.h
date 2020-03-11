#ifndef MATRIX_UTIL_H_
#define MATRIX_UTIL_H_

int matrix_equal(int* matrixA, int* matrixB, int n);
void matrix_deep_copy(int* origin, int* copy, int n);
void matrix_multiply(int* matrixA, int* matrixB, int* result, int n);
void matrix_pow(int* matrix, int* result, int pow, int n);
void matrix_fast_pow(int* matrix, int* result, int pow, int n);
void matrix_print(int* matrix, int n);

#endif