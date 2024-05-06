#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "global.h"


int test_cercle(POINT p, POINT q, POINT r){
    double d = (p.x * (q.y - r.y) + q.x * (r.y - p.y) + r.x * (p.y - q.y)) * 2 ;
    if (d>=0){
        return 1; //INTERIEUR
    }else{
        return 0; //EXTERIEUR 
    }
}