#include <immintrin.h>
#include <omp.h>

#include <cmath>
#define A(i, j) (A[(i)*K + (j)])
#define B(i, j) (B[(i)*N + (j)])
#define C(i, j) (C[(i)*N + (j)])

void gemm_16x16(float *A, float *B, float *C, int M, int N, int K);
void addDot_16x16(float *A, float *B, float *C, int M, int N, int K);
/*
M: rows of C, rows of A
N: columns of C, columns of B
K: columns of A, rows of B
*/
void gemm_16x16(float *A, float *B, float *C, int M, int N, int K) {
#pragma omp for parallel
  for (int i = 0; i < M / 16; i++) {
    for (int j = 0; j < N / 16; j++) {
        addDot_16x16(&A(i, j), &B(i, j), &C(i, j), M, N, K);
    }
  }
}

void addDot_16x16(float *A, float *B, float *C, int M, int N, int K) {
  __m256 b;
  __m256 c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15;

  for (int i = 0; i < 16; i++) {
    b = _mm256_load_ps(&B(i, 0));
    c0 += A(0, 0) * b;
    c1 += A(1, 0) * b;
    c2 += A(2, 0) * b;
    c3 += A(3, 0) * b;
    c4 += A(4, 0) * b;
    c5 += A(5, 0) * b;
    c6 += A(6, 0) * b;
    c7 += A(7, 0) * b;
    c8 += A(8, 0) * b;
    c9 += A(9, 0) * b;
    c10 += A(10, 0) * b;
    c11 += A(11, 0) * b;
    c12 += A(12, 0) * b;
    c13 += A(13, 0) * b;
    c14 += A(14, 0) * b;
    c15 += A(15, 0) * b;
  }
  _mm256_store_ps(&C(0, 0), c0);
  _mm256_store_ps(&C(1, 0), c1);
  _mm256_store_ps(&C(2, 0), c2);
  _mm256_store_ps(&C(3, 0), c3);
  _mm256_store_ps(&C(4, 0), c4);
  _mm256_store_ps(&C(5, 0), c5);
  _mm256_store_ps(&C(6, 0), c6);
  _mm256_store_ps(&C(7, 0), c7);
  _mm256_store_ps(&C(8, 0), c8);
  _mm256_store_ps(&C(9, 0), c9);
  _mm256_store_ps(&C(10, 0), c10);
  _mm256_store_ps(&C(11, 0), c11);
  _mm256_store_ps(&C(12, 0), c12);
  _mm256_store_ps(&C(13, 0), c13);
  _mm256_store_ps(&C(14, 0), c14);
  _mm256_store_ps(&C(15, 0), c15);
}