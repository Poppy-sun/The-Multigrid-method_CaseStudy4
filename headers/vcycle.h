#ifndef VCYCLE_H
#define VCYCLE_H

#include "init_levels.h"

/* count how many times we solve on the coarsest grid */
extern long coarse_solve_count;

/* Recursive V-cycle */
void vcycle(Level *levels,
            int level,
            int numLevels,
            int nu1,
            int nu2);

#endif
