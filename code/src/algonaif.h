#ifndef ALGONAIF_H
#define ALGONAIF_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "incercle.h"
#include "fonctions.h"  
#include "dessiner.h"


char* dessinerCercle_naif(FILE *file, double x, double y, double r);
int test_cercle_naif(POINT p, POINT q, POINT r);

void findCircle_deux_points(POINT p1, POINT p2, double *centerX, double *centerY, double *rayon) ;
void findCircle(POINT p1, POINT p2, POINT p3, double *centerX, double *centerY, double *rayon);

int tous_les_points_dans_cercle_trois_points (POINT* tab, POINT a, POINT b, POINT c);
int tous_les_points_dans_cercle(POINT* tab, double *centerX, double *centerY, double *rayon);

void algo_naif (FILE *file,POINT* tab, int N);
void solution_algo_naif(POINT tab[],FILE* file,int N);

#endif