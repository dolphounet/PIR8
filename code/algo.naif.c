#include <math.h>
#include <stdio.h>
#include "structures.h"
#include "global.h"

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
      findCircle_deux_points(p, q, &centerX, &centerY, &rayon, &centerX_dessin, &centerY_dessin, &rayondessin);
      //verifiation des points 
      if (verification(tab, &centerX, &centerY, &rayon)== 1){
          dessinerCercle(file,centerX_dessin,centerY_dessin,rayondessin);
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
          findCircle(p, q, r, &centerX, &centerY, &rayon,&centerX_dessin, &centerY_dessin,&rayondessin);
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