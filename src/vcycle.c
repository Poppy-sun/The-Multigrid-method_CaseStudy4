#include "vcycle.h"
#include "smooth.h"
#include "residual.h"
#include "restriction.h"
#include "prolongation.h"
#include <string.h>  /* for memset */

/* define the global counter */
long coarse_solve_count = 0;

void vcycle(Level *levels,
            int level,
            int numLevels,
            int nu1,
            int nu2)
{
    /* if on coarsest level, just smooth and count */
    if (level == numLevels - 1) {
        coarse_solve_count++;               /* ++ when we hit coarsest */
        smooth(&levels[level], nu1+nu2);
        return;
    }

    Level *lvl    = &levels[level];
    Level *coarse = &levels[level+1];

    /* 1. Pre-smoothing */
    smooth(lvl, nu1);

    /* 2. Compute residual on fine */
    compute_residual(lvl);

    /* 3. Restrict to coarse f, zero coarse u */
    memset(coarse->u,   0,
      (coarse->n+2)*(coarse->n+2)*sizeof(double));
    restrict_residual(lvl, coarse);

    /* 4. Recursive V-cycle on coarse */
    vcycle(levels, level+1, numLevels, nu1, nu2);

    /* 5. Prolongate correction back and add */
    prolongate_and_add(coarse, lvl);

    /* 6. Post-smoothing */
    smooth(lvl, nu2);
}
