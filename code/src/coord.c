#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structures.h"
#include "global.h"

int xx, yy;

int rand_a_b (int a, int b){
  // Retourne un nombre aléatoire entre a (inclus) et b (exclus).
  // Prend deux entiers a et b comme arguments, représentant les bornes inférieure et supérieure.
  return rand() % (b - a) + a;
}

void coord_aleatoires(POINT* tab){
  // Remplit le tableau de points avec des coordonnées aléatoires dans les limites spécifiées.
  // Prend un pointeur vers un tableau de POINT comme argument.
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
    // Ajuste inf et sup si ils sont égaux pour éviter une échelle nulle
    inf = sup - 1; 
    sup = sup+1;
  }
}