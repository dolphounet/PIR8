
#include <stdio.h>
#include <math.h>
#include "structures.h"
#include "global.h"  
#include "dessiner.h"

double centerX, centerY, rayon, centerX_dessin, centerY_dessin, rayondessin; 
double res_x, res_y, res_rayon, res_x_dessin, res_y_dessin, res_rayon_dessin;

void findCircle_deux_points(POINT p1, POINT p2, double *centerX, double *centerY, double *rayon) {
    *centerX = (p1.x + p2.x) / 2;
    *centerY = (p1.y + p2.y) / 2;
    double a =p1.x;
    double b = p1.y;
    *rayon = sqrt(pow(*centerX - a, 2) + pow(*centerY - b, 2));
    centerX_dessin = ((*centerX-inf)*1800/(sup-inf))+100;
    centerY_dessin = ((*centerY-inf)*1800/(sup-inf))+100;
    double n_pix = ((p1.x-inf)*1800/(sup-inf))+100;
    double n_piy = ((p1.y-inf)*1800/(sup-inf))+100;
    rayondessin = sqrt(pow(centerX_dessin - n_pix, 2) + pow(centerY_dessin - n_piy, 2));
}

// Fonction pour trouver le cercle passant par trois points
void findCircle(POINT p1, POINT p2, POINT p3, double *centerX, double *centerY, double *rayon) {
    // Calcul des coordonnées du centre potentiel du cercle
    double m1 = (p2.y - p1.y) / (p2.x - p1.x);
    double m2 = (p3.y - p2.y) / (p3.x - p2.x);

    *centerX = (m1 * m2 * (p3.y - p1.y) + m1 * (p2.x + p3.x) - m2 * (p1.x + p2.x)) / (2 * (m1 - m2));
    *centerY = -1 * (*centerX - (p1.x + p2.x) / 2) / m1 + (p1.y + p2.y) / 2;
    *rayon = sqrt(pow(*centerX - p1.x, 2) + pow(*centerY - p1.y, 2));
    centerX_dessin = ((*centerX-inf)*1800/(sup-inf))+100;
    centerY_dessin = ((*centerY-inf)*1800/(sup-inf))+100;
    double n_pix = ((p1.x-inf)*1800/(sup-inf))+100;
    double n_piy = ((p1.y-inf)*1800/(sup-inf))+100;
    rayondessin = sqrt(pow(centerX_dessin - n_pix, 2) + pow(centerY_dessin - n_piy, 2));
}

int verification (POINT* tab, double *centerX, double *centerY, double *rayon){
  for (int i = 0; i < N; i++) {  
    POINT p;
    p.x = tab[i].x;
    p.y = tab[i].y;
    double distance = sqrt(pow(*centerX - p.x, 2) + pow(*centerY - p.y, 2));
    if (distance > *rayon) {
      return 0;
    }
  }
  return 1;
}

void algo_naif (FILE *file,POINT* tab, int N){
  for (int i = 0; i < N-1; i++) {
    POINT p;
    p.x = tab[i].x;
    p.y = tab[i].y;
    for (int j = i+1; j < N; j++) {
      POINT q;
      q.x = tab[j].x;
      q.y = tab[j].y;
      printf("%2f , %.2f \n", p.x, p.y);
      printf("%.2f , %.2f \n", q.x, q.y);
      findCircle_deux_points(p, q, &centerX, &centerY, &rayon);
      //verifiation des points 
      if (verification(tab, &centerX, &centerY, &rayon)== 1){
          dessinerCercle(file, centerX_dessin, centerY_dessin, rayondessin);
          return ; 
      }
    }
  }
  
  for (int i = 0; i < N-2; i++) {
    POINT p;
    p.x = tab[i].x;
    p.y = tab[i].y;
    for (int j = i+1; j < N-1; j++) {
      POINT q;
      q.x = tab[j].x;
      q.y = tab[j].y;
      for (int k = j+1; k < N; k++) {
        POINT r;
        r.x = tab[k].x;
        r.y = tab[k].y;
        double d = (p.x * (q.y - r.y) + q.x * (r.y - p.y) + r.x * (p.y - q.y)) * 2 ;
        if (d==0){
          printf("Pas de cercle possible passant par ces 3 points");
        }else{
          printf("%2f , %.2f \n", p.x, p.y);
          printf("%.2f , %.2f \n", q.x, q.y);
          printf("%.2f , %.2f \n", r.x, r.y);
          findCircle(p, q, r, &centerX, &centerY, &rayon);
          printf("centreX %.2f, centreY %.2f, rayon %.2f \n", centerX, centerY, rayon);
          if (verification(tab, &centerX, &centerY, &rayon)== 1 && rayon<res_rayon){
              res_x = centerX;
              res_y = centerY;
              res_rayon = rayon; 
              res_x_dessin = centerX_dessin;
              res_y_dessin = centerY_dessin;
              res_rayon_dessin = rayondessin;
          }
        }
      }
    }
  }
  dessinerCercle(file, res_x_dessin, res_y_dessin, res_rayon_dessin);
}

void trouver_c (POINT tab[], FILE* file, int N){
  if(N < 2) {
    centerX = 0; 
    centerY = 0; 
    rayon = 0; 
  }
  else  {
    algo_naif(file, tab, N);
  }
}
