#include <math.h>
#include <stdio.h>
#include "structures.h"

#include "global.h"

int verification (POINT* tab, double *centerX, double *centerY, double *rayon){
  for (int i = 0; i < N; i++) {
    POINT p;
    p.x = tab[i].x;
    p.y = tab[i].y;
    double distance = sqrt(pow(*centerX - p.x, 2) + pow(*centerY - p.y, 2));
    if (distance > *rayon) {
      return 0;
    }
  }
  return 1;
}

void trouver_c (POINT tab[],FILE* file,int N, double *centerX, double *centerY, double *rayon){
  if(N < 2){
    centerX = 0; 
    centerY = 0; 
    rayon = 0; 
  }else{
    algo_naif(file,tab,N);
  }
}
