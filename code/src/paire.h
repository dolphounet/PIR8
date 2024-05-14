#ifndef PAIRE_H
#define PAIRE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "dessiner.h"

double centerx, centery, rayonn, centery_dessin, centerx_dessin, rayondessinn;
int nb_point, k;

void pairePoint(POINT *tab, DROITE d);
void mediatrice(DROITE p, double x, double y);

#endif
