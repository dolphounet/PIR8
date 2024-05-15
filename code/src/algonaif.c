#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"  
#include "incercle.h"
#include "fonctions.h"
#include "dessiner.h"

int N, xmin, xmax, ymin, ymax, inf, sup;
double centerX, centerY, rayon, centerX_dessin, centerY_dessin, rayondessin; 
double res_x, res_y, res_rayon, res_x_dessin, res_y_dessin, res_rayon_dessin;

char* dessinerCercle_naif(FILE *file, double x, double y, double r)  {
  char* codeCercle = malloc (sizeof (*codeCercle) * 500);
  sprintf(codeCercle,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"red\" stroke-width=\"3\" fill=\"transparent\" fill-opacity=\"0\" />",x,y,r);
  fprintf(file,"%s\n", codeCercle);
  return codeCercle;
}

int test_cercle_naif(POINT p, POINT q, POINT r){
    double d = (p.x * (q.y - r.y) + q.x * (r.y - p.y) + r.x * (p.y - q.y)) * 2 ;
    if (d>=0){
        return 1; //INTERIEUR
    }else{
        return 0; //EXTERIEUR 
    }
}

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

int tous_les_points_dans_cercle_trois_points (POINT* tab, POINT a, POINT b, POINT c){
  //verifier si tous les points sont dans un cercle définit par trois points
  int inside = 1; 
  for (int i = 0; i < N; i++) {  
    POINT test;
    test.x = tab[i].x;
    test.y = tab[i].y;
    if (point_in_cercle_trois_points(a,b,c,test)==0) {
      inside = 0; // EXTERIEUR
      break;
    }
  }
  return inside;
}

int tous_les_points_dans_cercle(POINT* tab, double *centerX, double *centerY, double *rayon){
  ///verifier si tous les points points sont dans un cercle definit par deux points
  int inside = 1;
  for (int i = 0; i < N; i++) {  
    POINT d;
    d.x = tab[i].x;
    d.y = tab[i].y;
    if (point_in_cercle(d, *centerX, *centerY, *rayon)==0) {
      inside = 0; 
      break;
    }
  }
  return inside;
}

void algo_naif (FILE *file,POINT* tab, int N){
  // ON teste les combinaisons de 2 et 3 points 
  for (int i = 0; i < N-1; i++) {
    POINT p;
    p.x = tab[i].x;
    p.y = tab[i].y;
    for (int j = i+1; j < N; j++) {
      POINT q;
      q.x = tab[j].x;
      q.y = tab[j].y;
      findCircle_deux_points(p, q, &centerX, &centerY, &rayon);
      //verifiation des points 
      if (tous_les_points_dans_cercle(tab, &centerX, &centerY, &rayon)== 1){
          res_x = centerX; 
          res_y = centerY; 
          res_rayon = rayon;
          printf("\n\ncentreX %.2f, centreY %.2f, rayon %.2f \n\n", centerX, centerY, rayon);
          dessinerCercle_naif(file, centerX_dessin, centerY_dessin, rayondessin);
          return ; 
      }
    }
  }
  // On n'a pas trouvé des cercles de deux points qui entourent tous les points
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
        if(test_cercle_naif(p,q,r)==0){
          printf("Pas de cercle possible passant par p,q,r\n\n");
        }else{
          printf("%2f , %.2f \n", p.x, p.y);
          printf("%.2f , %.2f \n", q.x, q.y);
          printf("%.2f , %.2f \n", r.x, r.y);
          findCircle(p, q, r, &centerX, &centerY, &rayon);
          printf("centreX %.2f, centreY %.2f, rayon %.2f \n\n", centerX, centerY, rayon);
          if (rayon<res_rayon && tous_les_points_dans_cercle_trois_points(tab,p,q,r)== 1){
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
  dessinerCercle_naif(file, res_x_dessin, res_y_dessin, res_rayon_dessin);
}

void solution_algo_naif(POINT tab[], FILE* file, int N){
  res_rayon = 99999999;
  if(N == 0) {
    res_x = 0; 
    res_y = 0; 
    res_rayon = 0; 
  }
  else if (N == 1) {
    res_x = tab[1].x;
    res_y = tab[1].y;
    res_rayon = 0;
  } else {
    algo_naif(file, tab, N);
  }
}