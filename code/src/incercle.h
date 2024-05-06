#ifndef INCERCLE_H
#define INCERCLE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
int point_in_cercle(POINT test, double centerX, double centerY, double rayon);
int point_in_cercle_trois_points (POINT a, POINT b, POINT c, POINT test);
int determinant (int a, int b, int c, int d );

#endif
