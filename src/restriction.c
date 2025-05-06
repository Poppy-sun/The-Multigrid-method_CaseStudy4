#include "restriction.h"

void restrict_residual(Level *fine, Level *coarse) {
    int nc = coarse->n;

    for (int i = 1; i <= nc; ++i) {
      for (int j = 1; j <= nc; ++j) {
        int fi = 2*i, fj = 2*j;
        double sum = 0.0;
        /* center */
        sum += 4.0 * fine->res[IDX(fine,fi,fj)];
        /* edge neighbors */
        sum += 2.0 * (
          fine->res[IDX(fine,fi-1,fj)] +
          fine->res[IDX(fine,fi+1,fj)] +
          fine->res[IDX(fine,fi,fj-1)] +
          fine->res[IDX(fine,fi,fj+1)]
        );
        /* corner neighbors */
        sum += (
          fine->res[IDX(fine,fi-1,fj-1)] +
          fine->res[IDX(fine,fi-1,fj+1)] +
          fine->res[IDX(fine,fi+1,fj-1)] +
          fine->res[IDX(fine,fi+1,fj+1)]
        );
        coarse->f[IDX(coarse,i,j)] = sum / 16.0;
      }
    }
}
