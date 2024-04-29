#include <math.h>
#include <stdio.h>
#include "structures.h"

//Dessine un point en SVG
char* dessinerPoint(FILE *file, POINT p, int r){ 
  char* codePoint= malloc (sizeof (*codePoint) * 500);
  sprintf(codePoint,"<circle cx=\"%f\" cy=\"%f\" r=\"%d\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>",p.x,p.y,r);
  fprintf(file,"%s\n", codePoint);
  return codePoint;
}

char* dessinerCercle(FILE *file, double x, double y, double r){
  char* codeCercle= malloc (sizeof (*codeCercle) *500);
  sprintf(codeCercle,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"red\" stroke-width=\"3\" fill=\"transparent\" fill-opacity=\"0\" />",x,y,r);
  fprintf(file,"%s\n", codeCercle);
  return codeCercle;
}