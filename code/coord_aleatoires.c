#include <math.h>
#include <stdio.h>
#include "structures.h"
#include "global.h"

int x,y;

void coord_aleatoires(POINT* tab){
  for (int i=0;i<N;i++){
    if (xmin != xmax){
      x=rand_a_b(xmin,xmax);
    }else{
      x = xmin;
    } 
    if (ymin != ymax){
      y=rand_a_b(ymin,ymax);
    }else{
      y = ymin;
    } 
    tab[i].x= x;
    tab[i].y= y;
    printf("%d , %d \n", x,y);
  }
  if (inf == sup ){
    inf = sup - 1; 
    sup = sup+1;
  }
}