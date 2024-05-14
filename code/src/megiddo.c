#include "megiddo.h"
#include "array.h"
#include "incercle.h"
#include <math.h>
#include <stdio.h>

int orientation(POINT c, DROITE2 d){
  int deter = 0;
  //int deter = determinant(d.x_a - c.x, d.y_a - c.y, d.x_b - c.x, d.y_b - c.y);
  if (deter > 0){
    return 1;
  }else if (deter < 0){
    return -1;
  }
  return 0;
}

DROITE2* creation_bissectrices(POINT* tab, int n){
  DROITE2* droite_tab = malloc((n/2 + 2) * sizeof(DROITE2));
  POINT midpoint;
  double pente;
  for (int i = 1 ; i <= n/2 ; i++){
    midpoint.x = (tab[2*i-1].x + tab[2*i].x) / 2;
    midpoint.y = (tab[2*i-1].y + tab[2*i].y) / 2;
    pente = -1 / ((tab[2*i].y - tab[2*i-1].y) / (tab[2*i].x - tab[2*i-1].x));
    if (pente == HUGE_VAL || pente == (- HUGE_VAL)){
      droite_tab[i-1].a = 1;
      droite_tab[i-1].b = 0;
      droite_tab[i-1].c = midpoint.x;
    }
    else {
      droite_tab[i-1].a = pente;
      droite_tab[i-1].b = 1;
      droite_tab[i-1].c = midpoint.y - midpoint.x * pente;

    }
    droite_tab[i-1].i = 2*i-1;
    droite_tab[i-1].j = 2*i;
  }

  return droite_tab;
}

array calcul_angles(DROITE2* droite_tab, int n){
  array angles = make_array(n/2, double);
  for (int i = 0; i < n/2 ; i++){
    *grow(&angles, double) = atan(droite_tab[i].a);
  }

  return angles;
}

PAIRE* creation_paires(double angle_m, DROITE2* droite_tab, int n){
  array positifs = make_array(n/4, DROITE2);
  array negatifs = make_array(n/4, DROITE2);
  array zeros = make_array(n/4, DROITE2);
  for (int i = 0; i < n/2 ; i++){
    if (atan(droite_tab[i].a) - angle_m > 0){
      *grow(&positifs, DROITE2) = droite_tab[i];
    }
    else if (atan(droite_tab[i].a) - angle_m < 0){
      *grow(&negatifs, DROITE2) = droite_tab[i];
    }
    else if (atan(droite_tab[i].a) - angle_m == 0){
      *grow(&zeros, DROITE2) = droite_tab[i];
    }
  }
  iter j = make_iter(&positifs);
  iter k = make_iter(&negatifs);
  PAIRE* paires = malloc(n/4 * sizeof(PAIRE));
  DROITE2 *c1, *c2;
  int i;
  for (i = 0, c1 = cur(j, DROITE2), c2 = cur(k, DROITE2); c1 && c2 && i < n/4; c1 = next(&j, DROITE2), c2 = next(&k, DROITE2), i++){
    paires[i].i = c1;
    paires[i].j = c2;
    if (paires[i].i->b == 0){
      paires[i].intersec.x = paires[i].i->c;
      paires[i].intersec.y = 0;
    }
    else if (paires[i].j->b == 0){
      paires[i].intersec.x = paires[i].j->c;
      paires[i].intersec.y = 0;
    }
    else if (paires[i].i->a != paires[i].j->a){
      paires[i].intersec.x = (paires[i].i->c - paires[i].j->c) / (paires[i].j->a - paires[i].i->a);
      paires[i].intersec.y = paires[i].j->a * paires[i].intersec.x + paires[i].j->c;
    }
  }

  iter l = make_iter(&zeros);
  for (c1 = cur(l, DROITE2), c2 = next(&l, DROITE2); c1 && c2; c1 = next(&l, DROITE2), c2 = next(&l, DROITE2)){
    printf("Pentes égales\n");
    paires[i].i = c1;
    paires[i].j = c2;
    // Pas de point  d'intersection (droites parallèles, toutes les deux à l'angle médian)
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

DROITE2* algo_megiddo(POINT* tab, int n){
  int faisable = 1;
  DROITE2* droite_tab;

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

    DROITE2 y, x;
    if (tan(angle_m) == HUGE_VAL || tan(angle_m) == (- HUGE_VAL)){
      y.a = 1;
      y.b = 0;
      y.c = median.x;
      x.a = 0;
      x.b = 1;
      x.c = median.y;
    }
    else if(tan(angle_m) == 0){
      y.a = 0;
      y.b = 1;
      y.c = median.y;
      x.a = 1;
      x.b = 0;
      x.c = median.x;
    }
    else {
      y.a = tan(angle_m);
      y.b = 1;
      y.c = median.y - median.x * y.a;
      x.a = -1/y.a;
      x.b = 1;
      x.c = median.y - median.x * x.a;
    }
  
    droite_tab[n/2 ] = x;
    droite_tab[n/2 +1] = y;
    
    faisable = 0;
    int orient_x = 1;
    int orient_y = 1;
    for (int i = 0; i < n/4; i++){
      if (orient_x == 1 && orient_y == 1 && paires[i].intersec.x < median.x && paires[i].intersec.y < median.y){
        if (atan(paires[i].i->a) < angle_m){
          if (orientation(tab[paires[i].i->i], *paires[i].i)){
            n = suppr_point(tab, n, paires[i].i->i);
          }else {
            n = suppr_point(tab, n, paires[i].i->j);
          }
        }else {
          if (orientation(tab[paires[i].j->i], *paires[i].j)){
            n = suppr_point(tab, n, paires[i].j->i);
          }else {
            n = suppr_point(tab, n, paires[i].j->j);
          }
        }

      }
      else if (orient_x == 1 && orient_y == -1 && paires[i].intersec.x < median.x && paires[i].intersec.y > median.y){
        if (atan(paires[i].i->a) < angle_m){
          if (orientation(tab[paires[i].i->i], *paires[i].i)){
            n = suppr_point(tab, n, paires[i].i->i);
          }else {
            n = suppr_point(tab, n, paires[i].i->j);
          }
        }else {
          if (orientation(tab[paires[i].j->i], *paires[i].j)){
            n = suppr_point(tab, n, paires[i].j->i);
          }else {
            n = suppr_point(tab, n, paires[i].j->j);
          }
        }
      }
      else if (orient_x == -1 && orient_y == 1 && paires[i].intersec.x > median.x && paires[i].intersec.y < median.y){ 
        if (atan(paires[i].i->a) < angle_m){
          if (orientation(tab[paires[i].i->i], *paires[i].i)){
            n = suppr_point(tab, n, paires[i].i->i);
          }else {
            n = suppr_point(tab, n, paires[i].i->j);
          }
        }else {
          if (orientation(tab[paires[i].j->i], *paires[i].j)){
            n = suppr_point(tab, n, paires[i].j->i);
          }else {
            n = suppr_point(tab, n, paires[i].j->j);
          }
        }
      }
      else if (orient_x == -1 && orient_y == -1 && paires[i].intersec.x > median.x && paires[i].intersec.y > median.y){
        if (atan(paires[i].i->a) < angle_m){
          if (orientation(tab[paires[i].i->i], *paires[i].i)){
            n = suppr_point(tab, n, paires[i].i->i);
          }else {
            n = suppr_point(tab, n, paires[i].i->j);
          }
        }else {
          if (orientation(tab[paires[i].j->i], *paires[i].j)){
            n = suppr_point(tab, n, paires[i].j->i);
          }else {
            n = suppr_point(tab, n, paires[i].j->j);
          }
        }

      }
    }
    free_array(&xs);
    free_array(&ys);
    free_array(&angles);

  }
  return droite_tab;
}

