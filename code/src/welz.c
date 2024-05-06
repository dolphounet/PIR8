#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "incercle.h"

double distance(POINT p1, POINT p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

CERCLE algo_welz(POINT* tab, int n){
    CERCLE res_welz;
    if (n == 0) {
        res_welz.x_cercle = 0; 
        res_welz.y_cercle = 0; 
        res_welz.rayon_cercle = 0;
        return (res_welz);
    }
    // Cas de base : un point
    else if (n == 1) {
        res_welz.x_cercle = tab[0].x; 
        res_welz.y_cercle = tab[0].y; 
        res_welz.rayon_cercle = 0;
        return (res_welz);
    }
    // Cas de base : deux points
    else if (n == 2) {
        res_welz.x_cercle = (tab[0].x + tab[1].x) / 2;
        res_welz.y_cercle = (tab[0].y + tab[1].y) / 2;
        res_welz.rayon_cercle = sqrt(pow(tab[0].x - tab[1].x, 2) + pow(tab[0].y - tab[1].y, 2));
        return (res_welz);
    }
    // Cas général
    else {
        // Sélectionnez un point aléatoire
        int randomIndex = rand()%n;
        POINT randomPoint = tab[randomIndex];

        // Supprimez ce point de la liste
        for (int i = randomIndex; i < n - 1; ++i) {
            tab[i] = tab[i + 1];
        }

        // Appel récursif pour les points restants
        res_welz = algo_welz(tab, n - 1);

        // Si le point n'est pas dans le cercle, agrandissez le cercle pour l'inclure
        if (point_in_cercle(randomPoint, res_welz.x_cercle, res_welz.y_cercle, res_welz.rayon_cercle)==0) {
            // Créez un cercle avec le point comme seul point du contour
            res_welz.x_cercle = randomPoint.x;
            res_welz.y_cercle = randomPoint.y;
            res_welz.rayon_cercle = 0;

            // Trouvez le cercle minimum contenant les points restants
            for (int i = 0; i < n - 1; ++i) {
                if (point_in_cercle(tab[i], res_welz.x_cercle, res_welz.y_cercle, res_welz.rayon_cercle)==0) {
                    // Sélectionnez deux points
                    res_welz.x_cercle = (tab[i].x + randomPoint.x) / 2;
                    res_welz.y_cercle = (tab[i].y + randomPoint.y) / 2;
                    res_welz.rayon_cercle = distance(tab[i], randomPoint) / 2;
                    for (int j = 0; j < i; ++j) {
                        if (j>0) {
                            // Calculez le cercle contenant les trois points
                            res_welz.x_cercle = (tab[i].x + tab[j].x) / 2;
                            res_welz.y_cercle = (tab[i].y + tab[j].y) / 2;
                            res_welz.rayon_cercle = distance(tab[i], tab[j]) / 2;
                            break;
                        }
                    }
                }
            }
        }

        return res_welz;
    }


}