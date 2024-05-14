#ifndef BRUTFORCE_H
#define BRUTFORCE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "paire.h"

double centerx, centery, rayonn, centery_dessin, centerx_dessin, rayondessinn;
int nb_point, k;

void recherche(POINT *tab, DROITE d);
double xycentre(DROITE d, double x, double y);
int countPointsInCircle(POINT *tab, double x, double y, double r);

#endif
