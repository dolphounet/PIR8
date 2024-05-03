#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structures.h"
#include "global.h"

int xx, yy;

int rand_a_b (int a, int b){
  return rand() % (b - a) + a;
}

void coord_aleatoires(POINT* tab){
  for (int i = 0 ; i < N ; i++){
    if (xmin != xmax){
      xx = rand_a_b(xmin, xmax);
    }else{
      xx = xmin;
    } 
    if (ymin != ymax){
      yy = rand_a_b(ymin, ymax);
    }else{
      yy = ymin;
    } 
    tab[i].x = xx;
    tab[i].y = yy;
    printf("%d , %d \n", xx,yy);
  }
  if (inf == sup ){
    inf = sup - 1; 
    sup = sup+1;
  }
}