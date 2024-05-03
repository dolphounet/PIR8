#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "dessiner.h"

double px, py;
double x, y, r;
double cx, cy, cr;
int nb_point, n, j;
CERCLE res_bf;

// Calcul des coordonnées du centre selon le point (x,y)
double xycentre(DROITE d, double x, double y)
{
    DROITE p;
    if (d.pente == 0)
    {
        p.pente = 9999999999;
        p.ordonnee = y - x * p.pente;
    }
    else
    {
        p.pente = -(1 / d.pente);
        p.ordonnee = y - x * p.pente;
    }
    cx = (p.ordonnee - d.ordonnee) / (d.pente - p.pente);
    cy = d.pente * cx + d.ordonnee;
    cr = sqrt(pow(cx - x, 2) + pow(cy - y, 2));
    return cr;
}

// Compte le nombre de points dans le cercle
int countPointsInCircle(POINT *tab, double x, double y, double r)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        // Calcul de la distance entre le point (tab[i].x, tab[i].y) et le centre (cx, cy)
        double distance = sqrt(pow(tab[i].x - x, 2) + pow(tab[i].y - y, 2));
        // Vérification si la distance est inférieure ou égale au rayon du cercle
        if (distance <= r)
        {
            count++;
        }
    }
    return count;
}

/* void meilleurCentre(int nb_point, int n, double rayon, double r, int i) {
    if(nb_point < n) {
            nb_point = n;
            rayon = r;
            centerX = x;
            centerY = y;
            j = i;
        }
        else if(nb_point == n) {
            if(r <= rayon)
            {
                nb_point = n;
                rayon = r;
                centerX = x;
                centerY = y;
                j = i;
            }
        }
} */

void formatSVG(POINT *tab) {
    centerX_dessin = ((centerX-inf)*1800/(sup-inf))+100;
    centerY_dessin = ((centerY-inf)*1800/(sup-inf))+100;
    double x_des = ((tab[j].x-inf)*1800/(sup-inf))+100;
    double y_des = ((tab[j].y-inf)*1800/(sup-inf))+100;
    rayondessin = sqrt(pow(centerX_dessin - x_des, 2) + pow(centerY_dessin - y_des, 2));
}

void recherche(POINT *tab, DROITE d)
{
    px = tab[0].x;
    py = tab[0].y;
    // initialise le rayon potentiel
    rayon = xycentre(d, px, py);
    centerX = cx;
    centerY = cy;
    nb_point = countPointsInCircle(tab, centerX, centerY, rayon);
    printf("\n%f %d\n",rayon,nb_point);
    for (int i = 1; i < N; i++)
    {
        r = xycentre(d, tab[i].x, tab[i].y);
        x = cx;
        y = cy;
        n = countPointsInCircle(tab, x, y, r);
        if(nb_point < n) {
            nb_point = n;
            rayon = r;
            centerX = x;
            centerY = y;
            j = i;
        }
        else if(nb_point == n) {
            if(r <= rayon)
            {
                nb_point = n;
                rayon = r;
                centerX = x;
                centerY = y;
                j = i;
            }
        }        
        printf("%f %d\n",r,n);
    }
    printf("\nNombre de points dans le cercle : %d/%d", nb_point, N);
    printf("\nVoici les coordonnées du centre (%.2f,%.2f) ainsi que le rayon du cercle %.2f\n\n", centerX, centerY, rayon);
    formatSVG(tab);
    dessinerCercle(file, centerX_dessin, centerY_dessin, rayondessin);
    dessinerCentre(file, centerX_dessin, centerY_dessin);
}
