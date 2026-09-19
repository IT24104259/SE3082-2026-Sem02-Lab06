#include <stdio.h>
#include <omp.h>

#define NPOINTS 1000
#define MAXITER 2000

struct d_complex {
    double r;
    double i;
};

int testpoint(struct d_complex c) {
    struct d_complex z;
    int iter;
    double temp;

    z = c;
    for (iter = 0; iter < MAXITER; iter++) {
        temp = (z.r * z.r) - (z.i * z.i) + c.r;
        z.i = 2.0 * z.r * z.i + c.i;
        z.r = temp;
        if ((z.r * z.r + z.i * z.i) > 4.0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int numoutside = 0;
    double area, error;

    double tstart = omp_get_wtime();

    #pragma omp parallel
    {
        int i, j;
        struct d_complex c;   // private: each thread needs its own c to test independently

        #pragma omp for reduction(+:numoutside)
        for (i = 0; i < NPOINTS; i++) {
            for (j = 0; j < NPOINTS; j++) {
                c.r = -2.0 + 2.5 * (double)i / (double)NPOINTS;
                c.i = 1.125 * (double)j / (double)NPOINTS;

                if (testpoint(c) == 0) {
                }
    return 0;
}    printf("Time taken: %f seconds\n", tcalc);


    printf("Area of Mandelbrot set = %12.8f +/- %12.8f\n", area, error);
    }
    double tcalc = tstop - tstart;

    double tstop = omp_get_wtime();
    area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) / (double)(NPOINTS * NPOINTS);
    error = area / (double)NPOINTS;

            }
        }

