#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "fonctions.h"
#include "coord.h"
#include "svg.h"
#include "welz.h"
#include "megiddo.h"
#include "algonaif.h"
#include "dessiner.h"
#include "array.h"
#include "median.h"
#include "dessiner.h"


int choix;

int main(int argc, char* argv[]){

  // Génère un nombre aléatoire basé sur le temps actuel
  srand(time(NULL));
  // Vérifie que le nombre correct d'arguments est passé
  if (argc!=6){
    printf ("nb invalide d'arguments\n");
    printf("usage: %s <nbDePoints> <xmin> <xmax> <ymin> <ymax>\n", argv[0]);
    return 1;
  }
  // Convertit les arguments en entiers
  N = atoi(argv[1]); 
  printf ("%d \n", N);  // Affiche le nombre de points générés

  xmin = atoi(argv[2]);   
  xmax = atoi(argv[3]);
  ymin = atoi(argv[4]);
  ymax = atoi(argv[5]);

  // Définition des limites pour l'affichage
  inf = xmin;
  sup = xmax; 
  if (ymax > sup){
    sup = ymax;
  }
  if (ymin < inf){
    inf = ymin;
  }

  // Allocation dynamique du tableau de points
  POINT* tab = malloc (sizeof(POINT) * N);
  coord_aleatoires(tab);
  
  // Demande à l'utilisateur de choisir un algorithme
  printf("\n\nQuel algorithme voulez-vous utiliser ?\n1. Algo naif\n2. Welz\n3. Force brute\n4. Algo Meggido\nRépondez par 1, 2, 3 ou 4 : ");

  while(1) {
    scanf("%d", &choix);
    if ( choix == 1 || choix == 2 || choix == 3 || choix == 4){
      GenerationFichierSVG(tab, N, choix);
      return 0;
    }else {
      printf("\nRéponse incorrecte, répondez par 1, 2, 3 ou 4 : ");
    }
  }
 }   
