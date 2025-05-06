#include "smooth.h"

void smooth(Level *lvl, int nu) {
    int n    = lvl->n;
    double h = lvl->h;
    double h2 = h*h;

    for (int it = 0; it < nu; ++it) {
      for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
          lvl->u[IDX(lvl,i,j)] = 0.25 * (
              lvl->u[IDX(lvl,i-1,j)] +
              lvl->u[IDX(lvl,i+1,j)] +
              lvl->u[IDX(lvl,i,j-1)] +
              lvl->u[IDX(lvl,i,j+1)]
            - h2 * lvl->f[IDX(lvl,i,j)]
          );
        }
      }
    }
}
