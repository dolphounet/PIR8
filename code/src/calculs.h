#ifndef CALCULS_H
#define CALCULS_H

#include <stdio.h>
#include <math.h>
#include "structures.h"
#include "global.h"  
#include "dessiner.h"

void findCircle_deux_points(POINT p1, POINT p2, double *centerX, double *centerY, double *rayon) ;
void findCircle(POINT p1, POINT p2, POINT p3, double *centerX, double *centerY, double *rayon);
int verification_cercle_trois_points (POINT* tab, POINT a, POINT b, POINT c);
int verification_cercle_deux_points (POINT* tab, POINT a, POINT b);
void algo_naif (FILE *file,POINT* tab, int N);
void trouver_c (POINT tab[],FILE* file,int N);

#endif
