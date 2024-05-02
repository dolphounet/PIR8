#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "global.h"

//Dessine un point en SVG
char* dessinerPoint(FILE *file, POINT p, int r) { 
  char* codePoint= malloc (sizeof (*codePoint) * 500);
  sprintf(codePoint,"<circle cx=\"%f\" cy=\"%f\" r=\"%d\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>",p.x,p.y,r);
  fprintf(file,"%s\n", codePoint);
  return codePoint;
}

char* dessinerCercle(FILE *file, double x, double y, double r)  {
  char* codeCercle= malloc (sizeof (*codeCercle) *500);
  sprintf(codeCercle,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"red\" stroke-width=\"3\" fill=\"transparent\" fill-opacity=\"0\" />",x,y,r);
  fprintf(file,"%s\n", codeCercle);
  return codeCercle;
}

/* char* dessinerDroite(FILE *file, int x_min, int x_max, int y_min, int y_max)  {
  double y_middle = (y_min + y_max) / 2;
  fprintf(file, "<line x1=\"%d\" y1=\"%f\" x2=\"%d\" y2=\"%F\" stroke=\"blue\" />\n", x_min, y_middle, x_max, y_middle); // Axe x
  return 0;
}
*/