#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "dessiner.h"
#include "brutForce.h"

DROITE p, med;
double xm, ym, cx, cy, cr;
double x, y, r;
int n;

// Calcul de la médiatrice de AB
void mediatrice(DROITE p, double x, double y) {
    if (p.pente == 0)
    {
        med.pente = 9999999999;
        med.ordonnee = y - x * med.pente;
    }
    else
    {
        med.pente = -(1 / p.pente);
        med.ordonnee = y - x * med.pente;
    }
}

// Calcul du centre du cercle selon d et la médiatrice de AB 
double intersection(DROITE d, DROITE med)
{
    cx = (d.ordonnee - med.ordonnee) / (med.pente - d.pente);
    cy = d.pente * cx + d.ordonnee;
    cr = sqrt(pow(cx - p.x_a, 2) + pow(cy - p.y_a, 2));
    return cr;
}

// Calcul les coordonnées du point pour la représentation SVG
void formatSVG(POINT *tab) 
{
    centerx_dessin = ((centerx-inf)*1800/(sup-inf))+100;
    centery_dessin = ((centery-inf)*1800/(sup-inf))+100;
    double x_des = ((tab[k].x-inf)*1800/(sup-inf))+100;
    double y_des = ((tab[k].y-inf)*1800/(sup-inf))+100;
    rayondessinn = sqrt(pow(centerx_dessin - x_des, 2) + pow(centery_dessin - y_des, 2));
}



void pairePoint(POINT *tab, DROITE d)
{
    for (int i = 0; i < N-1; i++)
    {
        p.x_a = tab[i].x;
        p.y_a = tab[i].y;
        for (int j = i+1; j < N; j++)
        {
            p.x_b = tab[j].x;
            p.y_b = tab[j].y;
            // Calcul de la droite AB 
            p.pente = (p.y_b - p.y_a) / (p.x_b - p.x_a);
            p.ordonnee = p.y_a - p.pente * p.x_a;
            // Calcul du milieu de AB par lequel passe la médiatrice
            xm = fabs(p.x_a - p.x_b)/2;
            ym = fabs(p.y_a - p.y_b)/2;
            mediatrice(p, xm, ym);
            r = intersection(d, med);
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
    }
    if (nb_point == N) {
        formatSVG(tab);
        printf("\nNombre de points dans le cercle : %d/%d", nb_point, N);
        printf("\nVoici les coordonnées du centre (%.2f,%.2f) ainsi que le rayon du cercle %.2f\n\n", centerx, centery, rayonn);
        dessinerCercle(file, centerx_dessin, centery_dessin, rayondessinn, 1);
        dessinerCentre(file, centerx_dessin, centery_dessin);
    }
    else {
        printf("\nLe nombre de points contenu dans le cercle est inférieur à %d.\nIl n'y a pas de cercle englobant pour cette configuration en utilisant la méthode brutforce.\n\n", N);
    }
}