#include <stdio.h>
#include <omp.h>

#define NPOINTS 1000        // grid resolution (NPOINTS x NPOINTS)
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
            return 0;   // escaped - outside the set
        }
    }
    return 1;   // did not escape - inside the set
}

int main() {
    int i, j, numoutside = 0;
    double area, error;
    struct d_complex c;

    double tstart = omp_get_wtime();

    for (i = 0; i < NPOINTS; i++) {
        for (j = 0; j < NPOINTS; j++) {
            // sample the box [-2, 0.5] x [0, 1.125] (upper half only, by symmetry)
            c.r = -2.0 + 2.5 * (double)i / (double)NPOINTS;
            c.i = 1.125 * (double)j / (double)NPOINTS;

            if (testpoint(c) == 0) {
                numoutside++;
            }
        }
    }

    // total sampled area x fraction inside x 2 (for symmetry, lower half mirrors upper half)
    area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) / (double)(NPOINTS * NPOINTS);
    error = area / (double)NPOINTS;

    double tstop = omp_get_wtime();
    double tcalc = tstop - tstart;

    printf("Area of Mandelbrot set = %12.8f +/- %12.8f\n", area, error);
    printf("Time taken: %f seconds\n", tcalc);

    return 0;
}
