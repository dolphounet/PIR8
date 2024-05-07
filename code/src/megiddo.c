#include "megiddo.h"
#include "array.h"


DROITE* creation_bissectrices(POINT* tab, int n){
  DROITE* droite_tab = malloc((n/2 + 2) * sizeof(DROITE));
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

/*
void rotation_plan(POINT* tab, int n, double angle_m){
  for (int i = 0; i < n ; i++){
    tab[i].x = tab[i].x * cos(angle_m) - tab[i].y * sin(angle_m);
    tab[i].y = tab[i].x * sin(angle_m) + tab[i].y * cos(angle_m);
  }
}
*/

array calcul_angles(DROITE* droite_tab, int n){
  array angles = make_array(n/2, double);
  for (int i = 0; i < n/2 ; i++){
    printf("Calcul Angle %f, %d\n", atan(droite_tab[i].pente), i);
    *grow(&angles, double) = atan(droite_tab[i].pente);
  }

  return angles;
}

PAIRE* creation_paires(double angle_m, DROITE* droite_tab, int n){
  array positifs = make_array(n/4, DROITE);
  array negatifs = make_array(n/4, DROITE);
  for (int i = 0; i < n/2 ; i++){
    printf("Angle soustrait %f, %d\n", atan(droite_tab[i].pente) - angle_m, i);
    if (atan(droite_tab[i].pente) - angle_m >= 0){
      *grow(&positifs, DROITE) = droite_tab[i];
    }
    else if (atan(droite_tab[i].pente) - angle_m < 0){
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
  }

  free_array(&positifs);
  free_array(&negatifs);
  return paires;
}

DROITE* algo_megiddo(POINT* tab, int n){
  DROITE* droite_tab = creation_bissectrices(tab, n);

  array angles = calcul_angles(droite_tab, n);
  double angle_m = find_median(&angles);
  
  PAIRE* paires = creation_paires(angle_m, droite_tab, n);
  array xs = make_array(n/4, double);
  array ys = make_array(n/4, double);
  for (int i = 0; i < n/4 ; i++){
    *grow(&xs, double) = paires[i].intersec.x;
    *grow(&ys, double) = paires[i].intersec.y;
    printf("Point intersec : x=%f y=%f\n", paires[i].intersec.x, paires[i].intersec.y);
    printf("Pentes par paires : %f, %f\n", paires[i].i.pente, paires[i].j.pente);
  }

  POINT median;
  median.x = find_median(&xs);
  median.y = find_median(&ys);
  printf("Point median : x=%f y=%f\n", median.x, median.y);

  DROITE y, x;
  y.pente = tan(angle_m);
  y.ordonnee = median.y - median.x * y.pente;
  x.pente = -1/y.pente;
  x.ordonnee = median.y - median.x * x.pente;
  x.x_a = 0;
  x.y_a = x.ordonnee;
  y.x_a = 0;
  y.y_a = y.ordonnee;
  x.x_b = 50;
  x.y_b = x.ordonnee + x.pente * 50;
  y.x_b = 50;
  y.y_b = y.ordonnee + y.pente * 50;

  droite_tab[0] = x;
  droite_tab[1] = y;

  free_array(&xs);
  free_array(&ys);
  free_array(&angles);
  return droite_tab;
}

