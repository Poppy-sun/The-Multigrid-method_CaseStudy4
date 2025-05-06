#include "prolongation.h"

void prolongate_and_add(Level *coarse, Level *fine) {
    int nc = coarse->n;
    /* 1) inject coarse points into even-even fine */
    for (int i = 1; i <= nc; ++i)
      for (int j = 1; j <= nc; ++j)
        fine->u[IDX(fine,2*i,2*j)] += coarse->u[IDX(coarse,i,j)];

    /* 2) horizontal midpoints */
    for (int i = 1; i <= nc; ++i)
      for (int j = 1; j < nc; ++j) {
        double v = 0.5*(coarse->u[IDX(coarse,i,j)] +
                        coarse->u[IDX(coarse,i,j+1)]);
        fine->u[IDX(fine,2*i,2*j+1)] += v;
      }

    /* 3) vertical midpoints */
    for (int i = 1; i < nc; ++i)
      for (int j = 1; j <= nc; ++j) {
        double v = 0.5*(coarse->u[IDX(coarse,i,j)] +
                        coarse->u[IDX(coarse,i+1,j)]);
        fine->u[IDX(fine,2*i+1,2*j)] += v;
      }

    /* 4) cell centers */
    for (int i = 1; i < nc; ++i)
      for (int j = 1; j < nc; ++j) {
        double v = 0.25*( coarse->u[IDX(coarse,i,j)]     +
                          coarse->u[IDX(coarse,i+1,j)]   +
                          coarse->u[IDX(coarse,i,j+1)]   +
                          coarse->u[IDX(coarse,i+1,j+1)] );
        fine->u[IDX(fine,2*i+1,2*j+1)] += v;
      }
}
