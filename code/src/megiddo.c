#include "megiddo.h"
#include "array.h"

DROITE* creation_bissectrices(POINT* tab, int n){
  DROITE* droite_tab = malloc(n/2 * sizeof(DROITE));
  POINT midpoint;
  for (int i = 1 ; i <= n/2 ; i++){
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

int compare(const void *a, const void *b){
  return (*(double*)a - *(double*)b);
}

void rotation_plan(POINT* tab, int n, double angle_m){
  for (int i = 0; i < n ; i++){
    tab[i].x = tab[i].x * cos(angle_m) - tab[i].y * sin(angle_m);
    tab[i].y = tab[i].x * sin(angle_m) + tab[i].y * cos(angle_m);
  }
}

array calcul_angles(DROITE* droite_tab, int n){
  array angles = make_array(n/2, double);
  for (int i = 0; i < n/2 ; i++){
    *grow(&angles, double) = atan(droite_tab[i].pente);
  }

  return angles;
}

DROITE* algo_megiddo(POINT* tab, int n){
  DROITE* droite_tab = creation_bissectrices(tab, n);
  array angles = calcul_angles(droite_tab, n/2);
  double angle_m = find_median(&angles);

  free_array(&angles);
  return droite_tab;
}
