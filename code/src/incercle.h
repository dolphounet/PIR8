#ifndef INCERCLE_H
#define INCERCLE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"

int in_cercle_deux_points (POINT a, POINT b, POINT d);
int in_cercle_trois_points (POINT a, POINT b, POINT c, POINT d);
int determinant (int a, int b, int c, int d );

#endif
