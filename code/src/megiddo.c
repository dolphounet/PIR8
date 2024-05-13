#include "megiddo.h"
#include "array.h"
#include "incercle.h"
#include <math.h>
#include <stdio.h>

int orientation(POINT c, DROITE d){
  int deter = determinant(d.x_a - c.x, d.y_a - c.y, d.x_b - c.x, d.y_b - c.y);
  if (deter > 0){
    return 1;
  }else if (deter < 0){
    return -1;
  }
  return 0;
}

DROITE* creation_bissectrices(POINT* tab, int n){
  DROITE* droite_tab = malloc((n/2 + 2) * sizeof(DROITE));
  POINT midpoint;
  for (int i = 1 ; i <= n/2 ; i++){
    midpoint.x = (tab[2*i-1].x + tab[2*i].x) / 2;
    midpoint.y = (tab[2*i-1].y + tab[2*i].y) / 2;
    droite_tab[i-1].pente = -1 / ((tab[2*i].y - tab[2*i-1].y) / (tab[2*i].x - tab[2*i-1].x));
    if (droite_tab[i-1].pente == HUGE_VAL || droite_tab[i-1].pente == (- HUGE_VAL)){
      droite_tab[i-1].ordonnee = HUGE_VAL;
      droite_tab[i-1].x_a = midpoint.x;
      droite_tab[i-1].x_b = midpoint.x;
      droite_tab[i-1].y_a = midpoint.y -5;
      droite_tab[i-1].y_b = midpoint.y +5;
    }
    else {
      droite_tab[i-1].ordonnee = midpoint.y - midpoint.x * droite_tab[i-1].pente;
      droite_tab[i-1].x_a = midpoint.x -5;
      droite_tab[i-1].x_b = midpoint.x +5;
      droite_tab[i-1].y_a = midpoint.y -5 * droite_tab[i-1].pente;
      droite_tab[i-1].y_b = midpoint.y +5 * droite_tab[i-1].pente;
    }
    droite_tab[i-1].i = 2*i-1;
    droite_tab[i-1].j = 2*i;
  }

  return droite_tab;
}

array calcul_angles(DROITE* droite_tab, int n){
  array angles = make_array(n/2, double);
  for (int i = 0; i < n/2 ; i++){
    *grow(&angles, double) = atan(droite_tab[i].pente);
  }

  return angles;
}

PAIRE* creation_paires(double angle_m, DROITE* droite_tab, int n){
  array positifs = make_array(n/4, DROITE);
  array negatifs = make_array(n/4, DROITE);
  array zeros = make_array(n/4, DROITE);
  for (int i = 0; i < n/2 ; i++){
    if (atan(droite_tab[i].pente) - angle_m > 0){
      *grow(&positifs, DROITE) = droite_tab[i];
    }
    else if (atan(droite_tab[i].pente) - angle_m < 0){
      *grow(&negatifs, DROITE) = droite_tab[i];
    }
    else if (atan(droite_tab[i].pente) - angle_m == 0){
      *grow(&zeros, DROITE) = droite_tab[i];
    }
  }
  iter j = make_iter(&positifs);
  iter k = make_iter(&negatifs);
  PAIRE* paires = malloc(n/4 * sizeof(PAIRE));
  DROITE *c1, *c2;
  int i;
  for (i = 0, c1 = cur(j, DROITE), c2 = cur(k, DROITE); c1 && c2 && i < n/4; c1 = next(&j, DROITE), c2 = next(&k, DROITE), i++){
    paires[i].i = c1;
    paires[i].j = c2;
    if (paires[i].i->pente == HUGE_VAL || paires[i].i->pente == (- HUGE_VAL)){
      printf("Pente inf i, %f, %f\n", paires[i].i->x_a, paires[i].i->x_b);
      paires[i].intersec.x = paires[i].i->x_a + 5;
      paires[i].intersec.y = 0;
    }
    else if (paires[i].j->pente == HUGE_VAL || paires[i].j->pente == (- HUGE_VAL)){
      printf("Pente inf j, %f, %f\n", paires[i].i->x_a, paires[i].i->x_b);
      paires[i].intersec.x = paires[i].j->x_a + 5;
      paires[i].intersec.y = 0;
    }
    else if (paires[i].i->pente != paires[i].j->pente){
      paires[i].intersec.x = (paires[i].i->ordonnee - paires[i].j->ordonnee) / (paires[i].j->pente - paires[i].i->pente);
      paires[i].intersec.y = paires[i].j->pente * paires[i].intersec.x + paires[i].j->ordonnee;
    }
  }

  iter l = make_iter(&zeros);
  for (c1 = cur(l, DROITE), c2 = next(&l, DROITE); c1 && c2; c1 = next(&l, DROITE), c2 = next(&l, DROITE)){
    printf("Pentes égales\n");
    paires[i].i = c1;
    paires[i].j = c2;
    paires[i].intersec.x = paires[i].i->x_a + 5;
    paires[i].intersec.y = paires[i].i->pente * paires[i].intersec.x + paires[i].i->ordonnee;
    i++;
  }

  free_array(&positifs);
  free_array(&negatifs);
  free_array(&zeros);
  return paires;
}

int suppr_point(POINT* tab, int n, int i){
  for (int j = i; j < n-1; j++){
    tab[j] = tab[j+1];
  }
  return n-1;
}

DROITE* algo_megiddo(POINT* tab, int n){
  int faisable = 1;
  DROITE* droite_tab;

  while (faisable) {
    
    droite_tab = creation_bissectrices(tab, n);

    array angles = calcul_angles(droite_tab, n);
    double angle_m = find_median(&angles);
  
    PAIRE* paires = creation_paires(angle_m, droite_tab, n);
    array xs = make_array(n/4, double);
    array ys = make_array(n/4, double);
    for (int i = 0; i < n/4 ; i++){
      *grow(&xs, double) = paires[i].intersec.x;
      *grow(&ys, double) = paires[i].intersec.y;
    }

    POINT median;
    median.x = find_median(&xs);
    median.y = find_median(&ys);
    printf("median : %f, %f\n", median.x, median.y);

    DROITE y, x;
    y.pente = tan(angle_m);
    if (y.pente == HUGE_VAL || y.pente == (- HUGE_VAL)){
      y.ordonnee = 9999999;
      y.x_a = median.x ;
      y.y_a = 0;
      y.x_b = median.x ;
      y.y_b = 9999999;
      x.pente = 0;
      x.ordonnee = median.y;
      x.x_a = 0;
      x.y_a = median.y;
      x.x_b = 9999999;
      x.y_b = median.y;
    }
    else if(y.pente == 0){
      y.ordonnee = median.y;
      x.pente = HUGE_VAL;
      x.ordonnee = 9999999;
      x.x_a = median.x;
      x.y_a = 0;
      x.x_b = median.x;
      x.y_b = 9999999;
      y.x_a = 0;
      y.y_a = median.y;
      y.x_b = 9999999;
      y.y_b = median.y;
    }
    else {
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
    }
  
    droite_tab[n/2 ] = x;
    droite_tab[n/2 +1] = y;
    
    faisable = 0;

    free_array(&xs);
    free_array(&ys);
    free_array(&angles);

  }
  return droite_tab;
}

