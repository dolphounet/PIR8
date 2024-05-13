#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "dessiner.h"
#include "paire.h"

double px, py;
double x, y, r;
double cx, cy, cr;
int nb_point, n, k;
CERCLE res_bf;

double centery_dessin, centerx_dessin, rayondessinn, centerx, centery, rayonn;


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






void recherche(POINT *tab, DROITE d)
{
    px = tab[0].x;
    py = tab[0].y;
    // initialise le rayon potentiel
    rayonn = xycentre(d, px, py);
    centerx = cx;
    centery = cy;
    nb_point = countPointsInCircle(tab, centerx, centery, rayonn);
    printf("\n%f %d\n",rayonn, nb_point);
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
            k = i;
            printf("%f %d\n", r, n);
        }
        else if(nb_point == n) {
            if(r <= rayonn)
            {
                nb_point = n;
                rayonn = r;
                centerx = x;
                centery = y;
                k = i;
                printf("%f %d\n", r, n);
            }
        }        
    }
    pairePoint(tab, d);
}
