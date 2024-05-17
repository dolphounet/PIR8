#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "global.h"


double distance(POINT p1, POINT p2) {
    // Calcule la distance entre deux points.
    // Prend deux points p1 et p2 de type POINT comme arguments.
    // Retourne la distance entre les deux points en utilisant la formule de la distance euclidienne.
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}