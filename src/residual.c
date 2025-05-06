#include "residual.h"
#include <math.h>

void compute_residual(Level *lvl) {
    int n    = lvl->n;
    double h = lvl->h;
    double h2 = h*h;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            double Au = (
                lvl->u[IDX(lvl,i-1,j)] +
                lvl->u[IDX(lvl,i+1,j)] +
                lvl->u[IDX(lvl,i,j-1)] +
                lvl->u[IDX(lvl,i,j+1)]
                - 4.0 * lvl->u[IDX(lvl,i,j)]
            ) / h2;
            lvl->res[IDX(lvl,i,j)] = lvl->f[IDX(lvl,i,j)] - Au;
        }
    }
}
