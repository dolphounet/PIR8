#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"

double px, py;
double x, y, r;
double cx, cy, cr;
int nb_point, n;
CERCLE res_bf;


// Calcul des coordonnées du centre selon le point (x,y)
double xycentre(DROITE d, double x, double y) {
    DROITE p;
    if(d.pente == 0) {
        p.pente = 9999999999;
        p.ordonnee =  y - x * p.pente;
    }
    else {
        p.pente = -(1 / d.pente);
        p.ordonnee = y - x * p.pente;
    }
    cx = (p.ordonnee - d.ordonnee) / (d.pente - p.pente);
    cy = d.pente * centerX + d.ordonnee;
    cr = sqrt(pow(x - cx, 2) + pow(y - cy, 2));
    return cr;
}


// Compte le nombre de points dans le cercle
int countPointsInCircle(POINT *tab, double x, double y, double r) {
    int count = 0;
    for (int i = 0; i < N-1; i++) {
        // Calcul de la distance entre le point (tab[i].x, tab[i].y) et le centre (cx, cy)
        double distance = sqrt(pow(tab[i].x - x, 2) + pow(tab[i].y - y, 2));
        // Vérification si la distance est inférieure ou égale au rayon du cercle
        if (distance <= r) {
            count++;
        }
    }
    return count;
}


void recherche(POINT *tab, DROITE d) {
    px = tab[0].x;
    py = tab[0].y;

    // initialise le rayon potentiel
    rayon = xycentre(d, px, py);
    centerX = cx;
    centerY = cy;
    nb_point = countPointsInCircle(tab, centerX, centerY, rayon);

    for (int i = 1; i < N-1; i++) {
        r = xycentre(d, tab[i].x, tab[i].y);
        x = cx;
        y = cy;
        n = countPointsInCircle(tab, x, y, r);
        if(nb_point < n) {
            if(r <= rayon) {
                nb_point = n;
                rayon = r;
                centerX = x;
                centerY = y;
            }
            printf("%d\n", nb_point);
        }
    }
    printf("%f %f", centerX, centerY);

}
