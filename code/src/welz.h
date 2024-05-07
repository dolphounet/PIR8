#ifndef WELZ_H
#define WELZ_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "dessiner.h"
#include "incercle.h"
#include "fonctions.h"
#include "algonaif.h"

double dista(POINT p1, POINT p2);
int cercle_possible(POINT p, POINT q, POINT r);
int is_inside(CERCLE c , POINT p);
int is_valid_circle(CERCLE c, POINT *P, int size) ;
void val_dessin (POINT p1, double centrex,double centrey);
CERCLE findCircle_welz(POINT p1, POINT p2, POINT p3);
CERCLE min_cercle_trivial(int size_points,POINT* R, int size_R);
CERCLE welz (POINT* tab_copy, POINT* R, int N, int size_R);
CERCLE welz_init (POINT* tab , int N);
int point_in_cercle_welz(POINT test, double cx, double cy, double r);
void solution_welz (POINT* tab,FILE *file, int N);

#endif
