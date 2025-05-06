#ifndef RESIDUAL_H
#define RESIDUAL_H

#include "init_levels.h"

/* Compute residual r = f – A·u on this level, store in lvl->res */
void compute_residual(Level *lvl);

#endif
