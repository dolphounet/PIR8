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

PAIRE* creation_paires(double angle_m, DROITE* droite_tab, int n){
  /*
   * WIP - Probablement pas fonctionnel
   */
  array positifs = make_array(n/4, DROITE);
  array negatifs = make_array(n/4, DROITE);
  for (int i = 0; i < n/2 ; i++){
    if (droite_tab[i].pente - angle_m > 0){
      *grow(&positifs, DROITE) = droite_tab[i];
    }
    else if (droite_tab[i].pente - angle_m < 0){
      *grow(&negatifs, DROITE) = droite_tab[i];
    }
  }
  iter j = make_iter(&positifs);
  iter k = make_iter(&negatifs);
  PAIRE* paires = malloc(n/4 * sizeof(PAIRE));
  DROITE *c1, *c2;
  int i;
  for (i = 0, c1 = cur(j, DROITE), c2 = cur(k, DROITE); c1 && c2 && i < n/4; c1 = next(&j, DROITE), c2 = next(&k, DROITE), i++){
    paires[i].i = *c1;
    paires[i].j = *c2;
    if (paires[i].i.pente != paires[i].j.pente){
      paires[i].intersec.x = (paires[i].i.ordonnee - paires[i].j.ordonnee) / (paires[i].j.pente - paires[i].i.pente);
      paires[i].intersec.y = paires[i].j.pente * paires[i].intersec.x + paires[i].j.ordonnee;
    }
    i++;
  }

  free_array(&positifs);
  free_array(&negatifs);
  return paires;
}

DROITE* algo_megiddo(POINT* tab, int n){
  DROITE* droite_tab = creation_bissectrices(tab, n);

  array angles = calcul_angles(droite_tab, n/2);
  double angle_m = find_median(&angles);
  
  PAIRE* paires = creation_paires(angle_m, droite_tab, n);
  array x = make_array(n/4, double);
  array y = make_array(n/4, double);
  for (int i = 0; i < n/4 ; i++){
    *grow(&x, double) = paires[i].intersec.x;
    *grow(&y, double) = paires[i].intersec.y;
  }
  double x_m = find_median(&x);
  double y_m = find_median(&y);

  free_array(&x);
  free_array(&y);
  free_array(&angles);
  return droite_tab;
}
