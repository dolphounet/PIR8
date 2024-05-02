#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"

double x, y;
CERCLE res_bf;


void xycentre(DROITE d, double x, double y) {
    DROITE p;
    if(d.pente == 0) {
        p.pente = 9999999999;
        p.ordonnee =  y - x * p.pente;
    }
    else {
        p.pente = -(1 / d.pente);
        p.ordonnee = y - x * p.pente;
    }
    centerX = (p.ordonnee - d.ordonnee) / (d.pente - p.pente);
    centerY = d.pente * centerX + d.ordonnee ;
}


void recherche(POINT *tab, DROITE d) {
    x = tab[0].x;
    y = tab[0].y;
    xycentre(d, x, y);
    for (int i = 1; i < N-1; i++) {
        // comparaison du rayon initial avec toutes les autres possibilités
    }
    printf("%f %f", centerX, centerY);

}
