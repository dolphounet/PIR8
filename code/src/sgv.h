#ifndef SGV_H
#define SGV_H
#include <math.h>
#include <stdio.h>
#include "global.h"
#include "structures.h"
#include "dessiner.h"
#include "calculs.h"

//Dessine les points et le cercle dans le SVG
void ecritureSVG(POINT tab[], FILE* file , int N);
void GenerationFichierSVG(POINT* tab , int N, int choix, DROITE* droite_tab);

#endif
