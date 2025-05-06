#ifndef RESTRICTION_H
#define RESTRICTION_H

#include "init_levels.h"

/* Full-weighting restriction: fine->res → coarse->f */
void restrict_residual(Level *fine, Level *coarse);

#endif
