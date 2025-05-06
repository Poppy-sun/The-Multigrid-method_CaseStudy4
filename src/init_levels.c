#include "init_levels.h"
#include <math.h>

void init_levels(Level *levels, int numLevels, int n0) {
    int n = n0;
    for (int lev = 0; lev < numLevels; ++lev) {
        levels[lev].n = n;
        levels[lev].h = 1.0 / (n + 1);
        int N = n + 2;
        int size = N * N;
        levels[lev].u   = calloc(size, sizeof(double));
        levels[lev].f   = calloc(size, sizeof(double));
        levels[lev].res = calloc(size, sizeof(double));
        /* next coarser grid */
        n = (n - 1) / 2;
    }
}
