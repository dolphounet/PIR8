#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "global.h"

//Dessine un point en SVG
char* dessinerPoint(FILE *file, POINT p, int r) { 
  char* codePoint = malloc (sizeof (*codePoint) * 500);
  sprintf(codePoint,"<circle cx=\"%f\" cy=\"%f\" r=\"%d\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>",p.x,p.y,r);
  fprintf(file,"%s\n", codePoint);
  return codePoint;
}

char* dessinerCercle(FILE *file, double x, double y, double r)  {
  char* codeCercle = malloc (sizeof (*codeCercle) * 500);
  sprintf(codeCercle,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"red\" stroke-width=\"3\" fill=\"transparent\" fill-opacity=\"0\" />",x,y,r);
  fprintf(file,"%s\n", codeCercle);
  return codeCercle;
}

char* dessinerDroite(FILE *file, DROITE d)  {
  double xa = (d.x_a*1800/(sup - inf)) + 100;
  double xb = (d.x_b*1800/(sup - inf)) + 100;
  double yb = (d.y_b*1800/(sup - inf)) + 100;
  double ya = yb;
  fprintf(file, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"blue\" stroke-width=\"5\" />\n", xa, ya, xb, yb);
  return 0;
}

char* dessinerCentre(FILE *file, double x, double y) { 
  char* codeCentre = malloc (sizeof (*codeCentre) * 500);
  sprintf(codeCentre,"<circle cx=\"%f\" cy=\"%f\" r=\"10\" stroke=\"red\" stroke-width=\"1\" fill=\"red\"/>",x,y);
  fprintf(file,"%s\n", codeCentre);
  return codeCentre;
}