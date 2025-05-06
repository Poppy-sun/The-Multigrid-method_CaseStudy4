#ifndef INIT_LEVELS_H
#define INIT_LEVELS_H

#include <stdlib.h>
#include <stdio.h>


typedef struct {
    int    n;        /* # interior points in each direction */
    double h;        /* grid spacing */
    double *u;       /* solution array [(n+2)*(n+2)] */
    double *f;       /* RHS array      [(n+2)*(n+2)] */
    double *res;     /* residual array [(n+2)*(n+2)] */
} Level;

/* Macro: 2D → 1D index on an (n+2)x(n+2) grid */
#define IDX(lvl,i,j)  ( (i)*((lvl)->n+2) + (j) )

/* Allocate and initialize numLevels of grids, finest has n0 interior pts */
void init_levels(Level *levels, int numLevels, int n0);

#endif
