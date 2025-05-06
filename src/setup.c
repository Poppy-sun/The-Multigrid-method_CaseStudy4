#include "setup.h"
#include <stdlib.h>
#include <stdio.h>

void parse_input(int argc, char *argv[],
                 int *n0, int *numLevels,
                 int *nu1, int *nu2,
                 double *tol, int *maxCycles)
{
    if (argc != 7) {
        fprintf(stderr,
          "Usage: %s n0 numLevels nu1 nu2 tol maxCycles\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    *n0        = atoi(argv[1]);
    *numLevels = atoi(argv[2]);
    *nu1       = atoi(argv[3]);
    *nu2       = atoi(argv[4]);
    *tol       = atof(argv[5]);
    *maxCycles = atoi(argv[6]);
}

void free_levels(Level *levels, int numLevels) {
    for (int lev = 0; lev < numLevels; ++lev) {
        free(levels[lev].u);
        free(levels[lev].f);
        free(levels[lev].res);
    }
    free(levels);
}
