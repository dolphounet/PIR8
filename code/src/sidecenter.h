#ifndef SODECENTER_H
#define SIDECENTER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"

int in_convex(POINT center, POINT* I, int N);
int side_center (POINT center, POINT* contour, int longueur);

#endif