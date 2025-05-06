#ifndef SMOOTH_H
#define SMOOTH_H

#include "init_levels.h"

/* Perform nu iterations of Gauss–Seidel on lvl: A u = f */
void smooth(Level *lvl, int nu);

#endif
