#ifndef DESSINER_H
#define DESSINER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "global.h"

char* dessinerPoint(FILE *file, POINT p, int r);
char* dessinerCercle(FILE *file, double x, double y, double r);
char* dessinerDroite(FILE *file, DROITE d);
char* dessinerCentre(FILE *file, double x, double y);

#endif
