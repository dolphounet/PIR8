#include "array.h"
#include "median.h"
#include "structures.h"
#include <math.h>
#include <stdio.h>

int orientation(POINT a, POINT b, DROITE2 d) {
  return (
      (d.a * a.x + d.b * a.y + d.c < 0) ==
      (d.a * b.x + d.b * b.y + d.c < 0)); // 0 : a et b ne sont pas du même côté
                                          // de la droite ; 1 : ils le sont
}

DROITE2 *creation_bissectrices(POINT *tab, int n) {
  DROITE2 *droite_tab = malloc((n / 2 + 2) * sizeof(DROITE2));
  POINT midpoint;
  double pente;
  for (int i = 1; i <= n / 2; i++) {
    midpoint.x = (tab[2 * i - 1].x + tab[2 * i].x) / 2;
    midpoint.y = (tab[2 * i - 1].y + tab[2 * i].y) / 2;
    pente = -1 / ((tab[2 * i].y - tab[2 * i - 1].y) /
                  (tab[2 * i].x - tab[2 * i - 1].x));
    if (pente == HUGE_VAL || pente == (-HUGE_VAL)) {
      droite_tab[i - 1].a = -1;
      droite_tab[i - 1].b = 0;
      droite_tab[i - 1].c = midpoint.x;
    } else {
      droite_tab[i - 1].a = pente;
      droite_tab[i - 1].b = -1;
      droite_tab[i - 1].c = midpoint.y - midpoint.x * pente;
    }
    droite_tab[i - 1].i = 2 * i - 1;
    droite_tab[i - 1].j = 2 * i;
  }

  return droite_tab;
}

array calcul_angles(DROITE2 *droite_tab, int n) {
  array angles = make_array(n / 2, double);
  for (int i = 0; i < n / 2; i++) {
    *grow(&angles, double) = atan(droite_tab[i].a);
  }

  return angles;
}

PAIRE *creation_paires(double angle_m, DROITE2 *droite_tab, int n) {
  array positifs = make_array(n / 4, DROITE2);
  array negatifs = make_array(n / 4, DROITE2);
  array zeros = make_array(n / 4, DROITE2);
  for (int i = 0; i < n / 2; i++) {
    if (atan(droite_tab[i].a) - angle_m > 0) {
      *grow(&positifs, DROITE2) = droite_tab[i];
    } else if (atan(droite_tab[i].a) - angle_m < 0) {
      *grow(&negatifs, DROITE2) = droite_tab[i];
    } else if (atan(droite_tab[i].a) - angle_m == 0) {
      *grow(&zeros, DROITE2) = droite_tab[i];
    }
  }
  iter j = make_iter(&positifs);
  iter kq = make_iter(&negatifs);
  PAIRE *paires = malloc(n / 4 * sizeof(PAIRE));
  DROITE2 *c1, *c2;
  int i;
  for (i = 0, c1 = cur(j, DROITE2), c2 = cur(kq, DROITE2);
       c1 && c2 && i < n / 4;
       c1 = next(&j, DROITE2), c2 = next(&kq, DROITE2), i++) {
    paires[i].i = c1;
    paires[i].j = c2;
    if (paires[i].i->b == 0) {
      paires[i].intersec.x = paires[i].i->c;
      paires[i].intersec.y = 0;
    } else if (paires[i].j->b == 0) {
      paires[i].intersec.x = paires[i].j->c;
      paires[i].intersec.y = 0;
    } else if (paires[i].i->a != paires[i].j->a) {
      paires[i].intersec.x =
          (paires[i].i->c - paires[i].j->c) / (paires[i].j->a - paires[i].i->a);
      paires[i].intersec.y =
          paires[i].j->a * paires[i].intersec.x + paires[i].j->c;
    }
  }

  iter l = make_iter(&zeros);
  for (c1 = cur(l, DROITE2), c2 = next(&l, DROITE2); c1 && c2;
       c1 = next(&l, DROITE2), c2 = next(&l, DROITE2)) {
    printf("Pentes égales\n");
    paires[i].i = c1;
    paires[i].j = c2;
    // Pas de point  d'intersection (droites parallèles, toutes les deux à
    // l'angle médian)
    i++;
  }

  free_array(&positifs);
  free_array(&negatifs);
  free_array(&zeros);
  return paires;
}

POINT rotation(POINT p, double angle_m) {
  POINT p_rot;
  p_rot.x = p.x * cos(angle_m) - p.y * sin(angle_m);
  p_rot.y = p.x * sin(angle_m) + p.y * cos(angle_m);
  return p_rot;
}

int algo_megiddo(POINT *tab, int n) {
  int faisable = 1;

  while (faisable) {

    DROITE2 *droite_tab = creation_bissectrices(tab, n);

    array angles = calcul_angles(droite_tab, n);
    double angle_m = find_median(&angles);

    PAIRE *paires = creation_paires(angle_m, droite_tab, n);
    array xs = make_array(n / 4, double);
    array ys = make_array(n / 4, double);
    for (int i = 0; i < n / 4; i++) {
      *grow(&xs, double) = paires[i].intersec.x;
      *grow(&ys, double) = paires[i].intersec.y;
    }

    POINT median;
    median.x = find_median(&xs);
    median.y = find_median(&ys);
    printf("median : %f, %f\n", median.x, median.y);

    DROITE2 y, x;
    if (tan(angle_m) == HUGE_VAL || tan(angle_m) == (-HUGE_VAL)) {
      y.a = 1;
      y.b = 0;
      y.c = median.x;
      x.a = 0;
      x.b = 1;
      x.c = median.y;
    } else if (tan(angle_m) == 0) {
      y.a = 0;
      y.b = 1;
      y.c = median.y;
      x.a = 1;
      x.b = 0;
      x.c = median.x;
    } else {
      y.a = tan(angle_m);
      y.b = 1;
      y.c = median.y - median.x * y.a;
      x.a = -1 / y.a;
      x.b = 1;
      x.c = median.y - median.x * x.a;
    }

    droite_tab[n / 2] = x;
    droite_tab[n / 2 + 1] = y;

    faisable = 0;
    int nb_suppr = 0;
    int orient_y = 1; // Appeler le problème contraint à y=ym
    POINT p_rot_m = rotation(median, angle_m);
    POINT *new_tab = malloc(sizeof(POINT) * n);
    int j = 0;
    for (int i = 0; i < n / 4; i++) {
      if (paires[i].i->b == paires[i].j->b) {
        POINT p_rot_i = rotation(tab[paires[i].i->i], angle_m);
        POINT p_rot_j = rotation(tab[paires[i].j->i], angle_m);
        if (orient_y == 1 && p_rot_i.y > p_rot_m.y) {
          if (orientation(tab[paires[i].i->i], median, *paires[i].i)) {
            new_tab[j] = tab[paires[i].i->j];
            new_tab[j + 1] = tab[paires[i].j->j];
            new_tab[j + 2] = tab[paires[i].j->i];
          } else {
            new_tab[j] = tab[paires[i].i->i];
            new_tab[j + 1] = tab[paires[i].j->i];
            new_tab[j + 2] = tab[paires[i].j->j];
          }
          j += 3;
          nb_suppr++;
        } else if (orient_y == -1 && p_rot_i.y < p_rot_m.y) {
          if (orientation(tab[paires[i].i->i], median, *paires[i].i)) {
            new_tab[j] = tab[paires[i].i->j];
            new_tab[j + 1] = tab[paires[i].j->j];
            new_tab[j + 2] = tab[paires[i].j->i];
          } else {
            new_tab[j] = tab[paires[i].i->i];
            new_tab[j + 1] = tab[paires[i].j->i];
            new_tab[j + 2] = tab[paires[i].j->j];
          }
          j += 3;
          nb_suppr++;
        } else if (orient_y == 1 && p_rot_j.y > p_rot_m.y) {
          if (orientation(tab[paires[i].j->i], median, *paires[i].j)) {
            new_tab[j] = tab[paires[i].i->j];
            new_tab[j + 1] = tab[paires[i].j->j];
            new_tab[j + 2] = tab[paires[i].i->i];
          } else {
            new_tab[j] = tab[paires[i].i->j];
            new_tab[j + 1] = tab[paires[i].i->i];
            new_tab[j + 2] = tab[paires[i].j->i];
            nb_suppr++;
          }
          j += 3;
          nb_suppr++;
        } else if (orient_y == -1 && p_rot_j.y < p_rot_m.y) {
          if (orientation(tab[paires[i].j->i], median, *paires[i].j)) {
            new_tab[j] = tab[paires[i].i->j];
            new_tab[j + 1] = tab[paires[i].j->j];
            new_tab[j + 2] = tab[paires[i].i->i];
          } else {
            new_tab[j] = tab[paires[i].i->j];
            new_tab[j + 1] = tab[paires[i].i->i];
            new_tab[j + 2] = tab[paires[i].j->i];
          }
          j += 3;
          nb_suppr++;
        } else {
          new_tab[j] = tab[paires[i].i->i];
          new_tab[j + 1] = tab[paires[i].i->j];
          new_tab[j + 2] = tab[paires[i].j->i];
          new_tab[j + 3] = tab[paires[i].j->j];
          j += 4;
        }
      }
    }

    int orient_x = 1; // Problemme contraint à x = xm

    for (int i = 0; i < n / 4; i++) {
      if (paires[i].i->b != paires[i].j->b) {
        POINT p_rot = rotation(paires[i].intersec, angle_m);
        if (orient_x == 1 && orient_y == 1 && p_rot.x < p_rot_m.x &&
            p_rot.y < p_rot_m.y) {
          if (atan(paires[i].i->a) < angle_m) {
            if (orientation(tab[paires[i].i->i], median, *paires[i].i)) {
              new_tab[j] = tab[paires[i].i->j];
              new_tab[j + 1] = tab[paires[i].j->j];
              new_tab[j + 2] = tab[paires[i].j->i];
            } else {
              new_tab[j] = tab[paires[i].i->i];
              new_tab[j + 1] = tab[paires[i].j->i];
              new_tab[j + 2] = tab[paires[i].j->j];
            }
            j += 3;
            nb_suppr++;
          } else {
            if (orientation(tab[paires[i].j->i], median, *paires[i].j)) {
              new_tab[j] = tab[paires[i].i->j];
              new_tab[j + 1] = tab[paires[i].j->j];
              new_tab[j + 2] = tab[paires[i].i->i];
            } else {
              new_tab[j] = tab[paires[i].i->j];
              new_tab[j + 1] = tab[paires[i].i->i];
              new_tab[j + 2] = tab[paires[i].j->i];
            }
            j += 3;
            nb_suppr++;
          }
        } else if (orient_x == 1 && orient_y == -1 && p_rot.x < p_rot_m.x &&
                   p_rot.y > p_rot_m.y) {
          if (atan(paires[i].i->a) > angle_m) {
            if (orientation(tab[paires[i].i->i], median, *paires[i].i)) {
              new_tab[j] = tab[paires[i].i->j];
              new_tab[j + 1] = tab[paires[i].j->j];
              new_tab[j + 2] = tab[paires[i].j->i];
            } else {
              new_tab[j] = tab[paires[i].i->i];
              new_tab[j + 1] = tab[paires[i].j->i];
              new_tab[j + 2] = tab[paires[i].j->j];
            }
            j += 3;
            nb_suppr++;
          } else {
            if (orientation(tab[paires[i].j->i], median, *paires[i].j)) {
              new_tab[j] = tab[paires[i].i->j];
              new_tab[j + 1] = tab[paires[i].j->j];
              new_tab[j + 2] = tab[paires[i].i->i];
            } else {
              new_tab[j] = tab[paires[i].i->j];
              new_tab[j + 1] = tab[paires[i].i->i];
              new_tab[j + 2] = tab[paires[i].j->i];
            }
            j += 3;
            nb_suppr++;
          }
        } else if (orient_x == -1 && orient_y == 1 && p_rot.x > p_rot_m.x &&
                   p_rot.y < p_rot_m.y) {
          if (atan(paires[i].i->a) > angle_m) {
            if (orientation(tab[paires[i].i->i], median, *paires[i].i)) {
              new_tab[j] = tab[paires[i].i->j];
              new_tab[j + 1] = tab[paires[i].j->j];
              new_tab[j + 2] = tab[paires[i].j->i];
            } else {
              new_tab[j] = tab[paires[i].i->i];
              new_tab[j + 1] = tab[paires[i].j->i];
              new_tab[j + 2] = tab[paires[i].j->j];
            }
            j += 3;
            nb_suppr++;
          } else {
            if (orientation(tab[paires[i].j->i], median, *paires[i].j)) {
              new_tab[j] = tab[paires[i].i->j];
              new_tab[j + 1] = tab[paires[i].j->j];
              new_tab[j + 2] = tab[paires[i].i->i];
            } else {
              new_tab[j] = tab[paires[i].i->j];
              new_tab[j + 1] = tab[paires[i].i->i];
              new_tab[j + 2] = tab[paires[i].j->i];
            }
            j += 3;
            nb_suppr++;
          }
        } else if (orient_x == -1 && orient_y == -1 && p_rot.x > p_rot_m.x &&
                   p_rot.y > p_rot_m.y) {
          if (atan(paires[i].i->a) < angle_m) {
            if (orientation(tab[paires[i].i->i], median, *paires[i].i)) {
              new_tab[j] = tab[paires[i].i->j];
              new_tab[j + 1] = tab[paires[i].j->j];
              new_tab[j + 2] = tab[paires[i].j->i];
            } else {
              new_tab[j] = tab[paires[i].i->i];
              new_tab[j + 1] = tab[paires[i].j->i];
              new_tab[j + 2] = tab[paires[i].j->j];
            }
            j += 3;
            nb_suppr++;
          } else {
            if (orientation(tab[paires[i].j->i], median, *paires[i].j)) {
              new_tab[j] = tab[paires[i].i->j];
              new_tab[j + 1] = tab[paires[i].j->j];
              new_tab[j + 2] = tab[paires[i].i->i];
            } else {
              new_tab[j] = tab[paires[i].i->j];
              new_tab[j + 1] = tab[paires[i].i->i];
              new_tab[j + 2] = tab[paires[i].j->i];
            }
            j += 3;
            nb_suppr++;
          }
        } else {
          new_tab[j] = tab[paires[i].i->i];
          new_tab[j + 1] = tab[paires[i].i->j];
          new_tab[j + 2] = tab[paires[i].j->i];
          new_tab[j + 3] = tab[paires[i].j->j];
          j += 4;
        }
      }
    }
    free(tab);
    tab = new_tab;
    n = n - nb_suppr;
    free_array(&xs);
    free_array(&ys);
    free_array(&angles);
    free(droite_tab);
  }
  return 0;
}
