#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "setup.h"
#include "init_levels.h"
#include "vcycle.h"
#include "residual.h"
#include <sys/time.h> 

int main(int argc, char *argv[]) {
    int    n0, numLevels, nu1, nu2, maxCycles;
    double tol;

    /*  Read user inputs */
    parse_input(argc, argv,
                &n0, &numLevels, &nu1, &nu2, &tol, &maxCycles);

    /* Build the hierarchy */
    Level *levels = malloc(numLevels * sizeof(Level));
    init_levels(levels, numLevels, n0);

    /*  Set RHS on finest: f = 2π² sin(πx) sin(πy) */
    Level *fine = &levels[0];
    int n = fine->n;
    double h = fine->h;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        double x = i * h, y = j * h;
        fine->f[IDX(fine,i,j)] =
          2.0 * M_PI * M_PI * sin(M_PI*x) * sin(M_PI*y);
      }
    }

    /* allocate array to save residual history */
    double *res_hist = malloc(maxCycles * sizeof(double));
    int cycles_done = 0;

    /* start timer */
    struct timeval t0, t1;
    gettimeofday(&t0, NULL);

    /*  V-cycle loop */
    printf("Cycle   Residual norm\n");
    for (int k = 1; k <= maxCycles; ++k) {
      vcycle(levels, 0, numLevels, nu1, nu2);

      /* compute L2 norm of residual */
      compute_residual(fine);
      double sum = 0.0;
      for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                double r = fine->res[IDX(fine,i,j)];
                sum += r*r;
            }
        }

      double resnorm = sqrt(sum) * h;
      res_hist[k-1] = resnorm;  /* save */
      cycles_done = k;

      printf("%4d    %e\n", k, resnorm);
      if (resnorm < tol) break;
    }
    /* stop timer */
   gettimeofday(&t1, NULL);
    double elapsed = (t1.tv_sec - t0.tv_sec)
                   + 1e-6*(t1.tv_usec - t0.tv_usec);

    /* print summary */
    printf("Total time: %f s\n", elapsed);
    printf("Coarse solves: %ld\n", coarse_solve_count);

  /* dump residual history */
    FILE *fp = fopen("residuals.txt","w");
    if (fp) {
        for (int i = 0; i < cycles_done; ++i) {
            fprintf(fp, "%d  %e\n", i+1, res_hist[i]);
        }
        fclose(fp);
    } else {
        fprintf(stderr, "Error: cannot open residuals.txt for writing\n");
    }

    /*  Clean up */
    free(res_hist);
    free_levels(levels, numLevels);
    return 0;
}
