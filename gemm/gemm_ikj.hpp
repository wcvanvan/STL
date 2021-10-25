#define A(i, j) A[(i)*K + (j)]
#define B(i, j) B[(i)*N + (j)]
#define C(i, j) C[(i)*N + (j)]

void gemm_ikj(float* A, float *B, float *C, int M, int N, int K);

/*
M: rows of C, rows of A
N: columns of C, columns of B
K: columns of A, rows of B
*/
void gemm_ikj(float* A, float *B, float *C, int M, int N, int K) {
    for (int i = 0; i < M; i++)
    {
        for (int k = 0; k < K; k++)
        {
            for (int j = 0; j < N; j++)
            {
                C(i, j) += A(i, k) * B(k, j);
            } 
        }
    }  
}


