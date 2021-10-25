#include <cmath>
#define A(i, j) A[(i)*K + (j)]
#define B(i, j) B[(i)*N + (j)]
#define C(i, j) C[(i)*N + (j)]

void gemm_4x4(float *&A, float *&B, float *&C, int M, int N, int K);
void addDot_4x4(float *&A, float *&B, float *&C, int M, int N, int K);
/*
pass matrices in the form of 1d array using reference
M: rows of C, rows of A
N: columns of C, columns of B
K: columns of A, rows of B
*/
void gemm_4x4(const float const *&A, float *&B, float *&C, int M, int N, int K) {
  int bigBlockCountInRow = M / 16;
  for (int z = 0; z < pow(bigBlockCountInRow, 2); z++) {
    int newI = z / bigBlockCountInRow * 16;
    int newJ = z % bigBlockCountInRow * 16;
    for (int i = newI; i < newI + 16; i += 4) {
      for (int j = newJ; j < newJ + 16; j += 4) {
        addDot_4x4(&A(i, 0), &B(0, j), &C(i, j), M, N, K);
      }
    }
  }
}

void addDot_4x4(float *&A, float *&B, float *&C, int M, int N, int K) {
  register float c_00_reg, c_01_reg, c_02_reg, c_03_reg, c_10_reg, c_11_reg,
      c_12_reg, c_13_reg, c_20_reg, c_21_reg, c_22_reg, c_23_reg, c_30_reg,
      c_31_reg, c_32_reg, c_33_reg, a_0p_reg, a_1p_reg, a_2p_reg, a_3p_reg,
      b_p0_reg, b_p1_reg, b_p2_reg, b_p3_reg;

  float *b_p0_ptr = &B(0, 0), *b_p1_ptr = &B(0, 1), *b_p2_ptr = &B(0, 2),
        *b_p3_ptr = &B(0, 3);

  c_00_reg = 0.0;
  c_01_reg = 0.0;
  c_02_reg = 0.0;
  c_03_reg = 0.0;
  c_10_reg = 0.0;
  c_11_reg = 0.0;
  c_12_reg = 0.0;
  c_13_reg = 0.0;
  c_20_reg = 0.0;
  c_21_reg = 0.0;
  c_22_reg = 0.0;
  c_23_reg = 0.0;
  c_30_reg = 0.0;
  c_31_reg = 0.0;
  c_32_reg = 0.0;
  c_33_reg = 0.0;

  for (int p = 0; p < K; p++) {
    a_0p_reg = A(0, p);
    a_1p_reg = A(1, p);
    a_2p_reg = A(2, p);
    a_3p_reg = A(3, p);

    b_p0_reg = *b_p0_ptr;
    b_p0_ptr += N;
    b_p1_reg = *b_p1_ptr;
    b_p1_ptr += N;
    b_p2_reg = *b_p2_ptr;
    b_p2_ptr += N;
    b_p3_reg = *b_p3_ptr;
    b_p3_ptr += N;

    /* First row and second rows */
    c_00_reg += a_0p_reg * b_p0_reg;
    c_10_reg += a_1p_reg * b_p0_reg;

    c_01_reg += a_0p_reg * b_p1_reg;
    c_11_reg += a_1p_reg * b_p1_reg;

    c_02_reg += a_0p_reg * b_p2_reg;
    c_12_reg += a_1p_reg * b_p2_reg;

    c_03_reg += a_0p_reg * b_p3_reg;
    c_13_reg += a_1p_reg * b_p3_reg;

    /* Third and fourth rows */
    c_20_reg += a_2p_reg * b_p0_reg;
    c_30_reg += a_3p_reg * b_p0_reg;

    c_21_reg += a_2p_reg * b_p1_reg;
    c_31_reg += a_3p_reg * b_p1_reg;

    c_22_reg += a_2p_reg * b_p2_reg;
    c_32_reg += a_3p_reg * b_p2_reg;

    c_23_reg += a_2p_reg * b_p3_reg;
    c_33_reg += a_3p_reg * b_p3_reg;
  }

  C(0, 0) += c_00_reg;
  C(0, 1) += c_01_reg;
  C(0, 2) += c_02_reg;
  C(0, 3) += c_03_reg;
  C(1, 0) += c_10_reg;
  C(1, 1) += c_11_reg;
  C(1, 2) += c_12_reg;
  C(1, 3) += c_13_reg;
  C(2, 0) += c_20_reg;
  C(2, 1) += c_21_reg;
  C(2, 2) += c_22_reg;
  C(2, 3) += c_23_reg;
  C(3, 0) += c_30_reg;
  C(3, 1) += c_31_reg;
  C(3, 2) += c_32_reg;
  C(3, 3) += c_33_reg;
}