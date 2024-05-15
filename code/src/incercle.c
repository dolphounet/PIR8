#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"

int determinant (int a, int b, int c, int d ){
  return a * d - b * c; 
}

double dis(POINT p1, POINT p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}
int point_in_cercle(POINT test, double cx, double cy, double r){
  POINT mon_centre;
  mon_centre.x = cx; 
  mon_centre.y = cy; 
  double dist_point_center = dis(mon_centre, test); 
  if (dist_point_center <= r){
    return 1; //INTERIEUR
  }else{
    return 0; //EXTERIEUR
  }
}

int point_in_cercle_trois_points (POINT a, POINT b, POINT c, POINT test){
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
    return 1; // INTERIEUR
  }else{
    return 0; // EXTERIEUR
  }
}

