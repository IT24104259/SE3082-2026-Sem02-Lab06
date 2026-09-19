#include <stdio.h>
#include <omp.h>

int fib(int n) {
    int i, j;
    if (n < 2)
        return n;

    #pragma omp task shared(i)
    i = fib(n - 1);

    #pragma omp task shared(j)
    j = fib(n - 2);

    #pragma omp taskwait
    return i + j;
}

int main() {
    int n = 20;
    int result;

    double tstart = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib(n);
        }
    }

    double tstop = omp_get_wtime();
    double tcalc = tstop - tstart;

    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Time taken: %f seconds\n", tcalc);

    return 0;
}
