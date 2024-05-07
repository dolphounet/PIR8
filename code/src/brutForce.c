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

double centery_dessin, centerx_dessin, rayondessinn,centerx, centery, rayonn;

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
            centerx = x;
            centery = y;
            j = i;
        }
        else if(nb_point == n) {
            if(r <= rayon)
            {
                nb_point = n;
                rayon = r;
                centerx = x;
                centery = y;
                j = i;
            }
        }
} */

void formatSVG(POINT *tab) {
    centerx_dessin = ((centerx-inf)*1800/(sup-inf))+100;
    centery_dessin = ((centery-inf)*1800/(sup-inf))+100;
    double x_des = ((tab[j].x-inf)*1800/(sup-inf))+100;
    double y_des = ((tab[j].y-inf)*1800/(sup-inf))+100;
    rayondessinn = sqrt(pow(centerx_dessin - x_des, 2) + pow(centery_dessin - y_des, 2));
}

void recherche(POINT *tab, DROITE d)
{
    px = tab[0].x;
    py = tab[0].y;
    // initialise le rayon potentiel
    rayonn = xycentre(d, px, py);
    centerx = cx;
    centery = cy;
    nb_point = countPointsInCircle(tab, centerx, centery, rayonn);
    printf("\n%f %d\n",rayonn,nb_point);
    for (int i = 1; i < N; i++)
    {
        r = xycentre(d, tab[i].x, tab[i].y);
        x = cx;
        y = cy;
        n = countPointsInCircle(tab, x, y, r);
        if(nb_point < n) {
            nb_point = n;
            rayonn = r;
            centerx = x;
            centery = y;
            j = i;
        }
        else if(nb_point == n) {
            if(r <= rayonn)
            {
                nb_point = n;
                rayonn = r;
                centerx = x;
                centery = y;
                j = i;
            }
        }        
        printf("%f %d\n",r,n);
    }
    printf("\nNombre de points dans le cercle : %d/%d", nb_point, N);
    printf("\nVoici les coordonnées du centre (%.2f,%.2f) ainsi que le rayon du cercle %.2f\n\n", centerx, centery, rayonn);
    formatSVG(tab);
    dessinerCercle(file, centerx_dessin, centery_dessin, rayondessinn,1);
    dessinerCentre(file, centerx_dessin, centery_dessin);
}
