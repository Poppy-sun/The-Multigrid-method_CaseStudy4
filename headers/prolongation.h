#ifndef PROLONGATION_H
#define PROLONGATION_H

#include "init_levels.h"

/* Bilinear interpolation: add coarse->u into fine->u */
void prolongate_and_add(Level *coarse, Level *fine);

#endif
