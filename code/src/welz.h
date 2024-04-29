#ifndef WELZ_H
#define WELZ_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
double distance(POINT p1, POINT p2) ;
int pointInsideCircle(POINT p, CERCLE c) ;
CERCLE algo_welz(POINT* tab, int n);


#endif
