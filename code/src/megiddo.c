#include "megiddo.h"

DROITE* algo_megiddo(POINT* tab, int n){
  DROITE* droite_tab = malloc(n * sizeof(DROITE));
  POINT midpoint;
  for (int i = 1 ; i < n/2 ; i++){
    midpoint.x = (tab[2*i-1].x + tab[2*i].x) / 2;
    midpoint.y = (tab[2*i-1].y + tab[2*i].y) / 2;
    droite_tab[i-1].pente = -1 / ((tab[2*i].y - tab[2*i-1].y) / (tab[2*i].x - tab[2*i-1].x));
    droite_tab[i-1].ordonnee = midpoint.y - midpoint.x * droite_tab[i-1].pente;
    droite_tab[i-1].x_a = midpoint.x -5;
    droite_tab[i-1].x_b = midpoint.x +5;
    droite_tab[i-1].y_a = midpoint.y -5 * droite_tab[i-1].pente;
    droite_tab[i-1].y_b = midpoint.y +5 * droite_tab[i-1].pente;
  }

  return droite_tab;
}
