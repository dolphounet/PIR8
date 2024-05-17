#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"

int determinant (int a, int b, int c, int d ){
  // Calcule le déterminant d'une matrice 2x2.
  // Prend les coefficients a, b, c, d de la matrice comme arguments.
  // Retourne le déterminant calculé comme (a * d - b * c).
  return a * d - b * c; 
}

double dis(POINT p1, POINT p2) {
  // Calcule la distance entre deux points.
  // Prend deux points p1 et p2 de type POINT comme arguments.
  // Retourne la distance entre les deux points en utilisant la formule de la distance euclidienne.
  return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

int point_in_cercle(POINT test, double cx, double cy, double r){
  // Détermine si un point est à l'intérieur d'un cercle.
  // Prend un point test de type POINT, les coordonnées du centre du cercle (cx, cy) et le rayon du cercle r comme arguments.
  // Retourne 1 si le point est à l'intérieur du cercle, sinon retourne 0.
  POINT mon_centre;
  mon_centre.x = cx; 
  mon_centre.y = cy; 
  double dist_point_center = dis(mon_centre, test); 
  if (dist_point_center <= r){
    return 1; //Le cercle est à l'intérieur
  }else{
    return 0; //Le cercle est à l'extérieur
  }
}

int point_in_cercle_trois_points (POINT a, POINT b, POINT c, POINT test){
  // Détermine si un point est à l'intérieur ou à l'extérieur du cercle passant par trois autres points.
  // Prend quatre points a, b, c, et test de type POINT comme arguments.
  // Utilise des déterminants pour calculer si le point test est à l'intérieur ou à l'extérieur du cercle formé par a, b, et c.
  // Retourne 1 si le point est à l'intérieur ou sur le contour du cercle, sinon retourne 0.
  int adx = a.x - test.x;
  int ady = a.y - test.y; 
  int bdx = b.x - test.x; 
  int bdy = b.y - test.y; 
  int cdx = c.x - test.x; 
  int cdy = c.y - test.y;  
  
  int ab_det = determinant (adx, ady, bdx, bdy); 
  int bc_det = determinant (bdx, bdy, cdx, cdy); 
  int ca_det = determinant (cdx, cdy, adx, ady);
  int a_val = adx * adx + ady * ady ; 
  int b_val = bdx * bdx + bdy * bdy ; 
  int c_val = cdx * cdx + cdy * cdy ;
  
  int res = a_val * bc_det + b_val * ca_det + c_val * ab_det;

  if (res >=0){
    return 1; // Le point est à l'intérieur ou sur le contour
  }else{
    return 0; // Le point est à l'extérieur
  }
}

