#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "dessiner.h"

int determinant (int a, int b, int c, int d ){
  return a * d - b * c; 
}

int in_cercle_deux_points (POINT a, POINT b, POINT d){
    int adx = a.x - d.x;
    int ady = a.y - d.x; 
    int bdx = b.x - d.x; 
    int bdy = b.y - d.y; 
    int ab_det = determinant (adx, ady, bdx, bdy);  
    return ab_det>=0; 
}

int in_cercle_trois_points (POINT a, POINT b, POINT c, POINT d){
  int adx = a.x - d.x;
  int ady = a.y - d.x; 
  int bdx = b.x - d.x; 
  int bdy = b.y - d.y; 
  int cdx = c.x - d.x; 
  int cdy = c.y - d.y;  
  
  int ab_det = determinant (adx, ady, bdx, bdy); 
  int bc_det = determinant (bdx, cdy, cdx, cdy); 
  int ca_det = determinant (cdx, cdy, adx, ady);
  int a_val = adx * adx + ady * ady ; 
  int b_val = bdx * bdx + bdy * bdy ; 
  int c_val = cdx * cdx + cdy * cdy ;

  return a_val * bc_det + b_val * ca_det + c_val * ab_det; 
}

