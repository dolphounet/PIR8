#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "dessiner.h"

DROITE p, med;
double xm, ym, cxx, cyy, crr, X, Y, R;
double rrayon,ccenterx,ccentery;
double centerx_mon_dessin,centery_mon_dessin,rayon_mon_dessin;

int kk, length, n_des_points, nn;
POINT* oncirle;
POINT ccentre;

int count_PointsInCircle(POINT *tab, double x, double y, double r)
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

// Calcul de la médiatrice de AB
void mediatrice(DROITE p, double X, double Y) {
    if (p.pente == 0)
    {
        med.pente = 9999999999;
        med.ordonnee = Y - X * med.pente;
    }
    else
    {
        med.pente = -(1 / p.pente);
        med.ordonnee = Y - X * med.pente;
    }
}

// Calcul du centre du cercle selon d et la médiatrice de AB 
double intersection(DROITE d, DROITE med)
{
    cxx = (d.ordonnee - med.ordonnee) / (med.pente - d.pente);
    cyy = d.pente * cxx + d.ordonnee;
    crr = sqrt(pow(cxx - p.x_a, 2) + pow(cyy - p.y_a, 2));
    return crr;
}

void pointOnCircle(POINT *tab) 
{
    length = 0;
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        double d = sqrt(pow(tab[i].x - ccentre.x, 2) + pow(tab[i].y - ccentre.y, 2));
        if (d == rrayon) 
        {
            length++;
        }
    }
    oncirle = malloc (sizeof(POINT) * length);
    for (int i = 0; i < N; i++)
    {
        double d = sqrt(pow(tab[i].x - ccentre.x, 2) + pow(tab[i].y - ccentre.y, 2));
        if (d == rrayon) 
        {
            oncirle[count] = tab[i];
            count++;
        }
    }   
}

// Calcul les coordonnées du point pour la représentation SVG
void formatSVG(POINT *tab) 
{
    centerx_mon_dessin= ((ccenterx-inf)*1800/(sup-inf))+100;
    centery_mon_dessin= ((ccentery-inf)*1800/(sup-inf))+100;
    double x_des = ((tab[kk].x-inf)*1800/(sup-inf))+100;
    double y_des = ((tab[kk].y-inf)*1800/(sup-inf))+100;
    rayon_mon_dessin = sqrt(pow(centerx_mon_dessin - x_des, 2) + pow(centery_mon_dessin - y_des, 2));
}



void pairePoint(POINT *tab, DROITE d)
{
    for (int i = 0; i < N; i++)
    {
        p.x_a = tab[i].x;
        p.y_a = tab[i].y;
        for (int j = 0; j < N; j++)
        {
            p.x_b = tab[j].x;
            p.y_b = tab[j].y;
            // Calcul de la droite AB 
            p.pente = (p.y_b - p.y_a) / (p.x_b - p.x_a);
            p.ordonnee = p.y_a - p.pente * p.x_a;
            // Calcul du milieu de AB par lequel passe la médiatrice
            xm = fabs(p.x_a + p.x_b)/2;
            ym = fabs(p.y_a + p.y_b)/2;
            mediatrice(p, xm, ym);
            R = intersection(d, med);
            X = cxx;
            Y = cyy;
            nn = count_PointsInCircle(tab, X, Y, R);
            if(n_des_points < nn) {
                n_des_points = nn;
                rrayon = R;
                ccenterx = X;
                ccentery = Y;
                kk = i;
            }
            else if(n_des_points == nn) {
                if(R <= rrayon)
                {
                    n_des_points = nn;
                    rrayon = R;
                    ccenterx = X;
                    ccentery = Y;
                    kk = i;
                }
            }        
        }   
    }
    if (n_des_points == N) {
        formatSVG(tab);
        printf("\nNombre de points dans le cercle : %d/%d", n_des_points, N);
        printf("\nVoici les coordonnées du centre (%.2f,%.2f) ainsi que le rayon du cercle %.2f\n\n", ccenterx, ccentery, rrayon);
        dessinerCercle(file, centerx_mon_dessin, centery_mon_dessin, rayon_mon_dessin, 1);
        dessinerCentre(file, centerx_mon_dessin, centery_mon_dessin);
        // Affectation des variables globales 
        ccentre.x = ccenterx;
        ccentre.y = ccentery;
        // Inventaire des points présents sur le cercle
        pointOnCircle(tab);
        printf("Voici les points présents sur le cercle :\n");
        for (int i = 0; i < length; i++)
        {
            printf("\t* %f\t%f\n", oncirle[i].x, oncirle[i].y);
        }  
        printf("\n");     
    }
    else {
        printf("\nLe nombre de points contenu dans le cercle est inférieur à %d.\nIl n'y a pas de cercle englobant pour cette configuration en utilisant la méthode brutforce.\n\n", N);
    }
}
