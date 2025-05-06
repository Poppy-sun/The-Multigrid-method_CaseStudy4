#ifndef SETUP_H
#define SETUP_H

#include "init_levels.h"

/* 
  Read command line:
    argv[1]=n0     (fine-grid interior pts)
    argv[2]=numLv  (number of levels)
    argv[3]=nu1    (pre-smooth iterations)
    argv[4]=nu2    (post-smooth iterations)
    argv[5]=tol    (residual tolerance)
    argv[6]=maxCycles
*/
void parse_input(int argc, char *argv[],
                 int *n0, int *numLevels,
                 int *nu1, int *nu2,
                 double *tol, int *maxCycles);

/* Free all arrays in levels[0..numLevels-1] */
void free_levels(Level *levels, int numLevels);

#endif
