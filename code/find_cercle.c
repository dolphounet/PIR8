#include <math.h>
#include "structures.h"

// Fonction pour trouver le cercle passant par deux points
void findCircle_deux_points(POINT p1, POINT p2, double *centerX, double *centerY, double *rayon) {
    *centerX = (p1.x + p2.x) / 2;
    *centerY = (p1.y + p2.y) / 2;
    *rayon = sqrt(pow(*centerX - p1.x, 2) + pow(*centerY - p1.y, 2));
}

// Fonction pour trouver le cercle passant par trois points
void findCircle(POINT p1, POINT p2, POINT p3, double *centerX, double *centerY, double *rayon) {
    // Calcul des coordonnées du centre potentiel du cercle
    double m1 = (p2.y - p1.y) / (p2.x - p1.x);
    double m2 = (p3.y - p2.y) / (p3.x - p2.x);

    *centerX = (m1 * m2 * (p3.y - p1.y) + m1 * (p2.x + p3.x) - m2 * (p1.x + p2.x)) / (2 * (m1 - m2));
    *centerY = -1 * (*centerX - (p1.x + p2.x) / 2) / m1 + (p1.y + p2.y) / 2;
    *rayon = sqrt(pow(*centerX - p1.x, 2) + pow(*centerY - p1.y, 2));
}