#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "global.h"


double distance(POINT p1, POINT p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}