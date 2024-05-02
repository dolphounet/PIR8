#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "coord.h"
#include "sgv.h"
#include "welz.h"
int N, choix, xmin, xmax, ymin, ymax, inf, sup;

int main(int argc, char* argv[]){

   // N = nb de points et coordonnées du cadre 
  srand(time(NULL));
  if (argc!=6){
    printf ("nb invalide d'arguments\n");
    printf("usage: %s <nbDePoints> <xmin> <xmax> <ymin> <ymax>\n", argv[0]);
    return 1;
  }
  N = atoi(argv[1]);
  printf ("%d \n", N);  // Affichage nb de points générés
  xmin = atoi(argv[2]);   
  xmax = atoi(argv[3]);
  ymin = atoi(argv[4]);
  ymax = atoi(argv[5]);
  res_rayon = INFINITY;
  inf = xmin;
  sup = xmax; 
  if (ymax > sup){
    sup = ymax;
  }
  if (ymin < inf){
    inf = ymin;
  }
  POINT* tab = malloc (sizeof(POINT) * N);
  coord_aleatoires(tab);

  GenerationFichierSVG(tab, N);
  
  /* Choix de l'algoritme */
  printf("Quel algorithme voulez-vous utiliser ?\n1. Welz\n2. Force brute\nRépondez par 1 ou 2 :\t");

  while(1) {
    scanf("%d", &choix);

    if(choix == 1)  {
      algo_welz(tab, N);  // Implementation WELZ 
      return 0;
    }
    else if (choix == 2)  {
      printf("\nGénération droite...");
      return 0; 
    }
    else {
      printf("Réponse incorrecte, répondez par 1 ou 2 :\t");
    }
  }
 }   