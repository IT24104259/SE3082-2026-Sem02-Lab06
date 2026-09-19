#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000
#define STRIP_SIZE 8   // aligns with common SIMD width (e.g., AVX = 8 floats / 4 doubles per instruction)

int main() {
    double *A = malloc(N * sizeof(double));
    double *B = malloc(N * sizeof(double));
    double *C = malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        A[i] = i * 0.5;
        B[i] = i * 2.0;
    }

    double tstart = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for (int strip_start = 0; strip_start < N; strip_start += STRIP_SIZE) {
        int strip_end = strip_start + STRIP_SIZE;
        if (strip_end > N) strip_end = N;   // handle the last, possibly-shorter strip

        #pragma omp simd
        for (int i = strip_start; i < strip_end; i++) {
            C[i] = A[i] * B[i];
        }
    }

    double tstop = omp_get_wtime();
    double tcalc = tstop - tstart;

    printf("Sample check: C[100] = %f (expected %f)\n", C[100], A[100] * B[100]);
    printf("Time taken: %f seconds\n", tcalc);

    free(A); free(B); free(C);
    return 0;
}
