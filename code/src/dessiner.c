#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "global.h"


char* dessinerPoint(FILE *file, POINT p, int r) { 
  // Dessine un point en SVG.
  // Prend un pointeur vers un fichier FILE, un point p de type POINT, et un entier r représentant le rayon du point.
  // Retourne une chaîne de caractères contenant le code SVG pour dessiner le point.
  char* codePoint = malloc (sizeof (*codePoint) * 500);
  sprintf(codePoint,"<circle cx=\"%f\" cy=\"%f\" r=\"%d\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>",p.x,p.y,r);
  fprintf(file,"%s\n", codePoint);
  return codePoint;
}

void affichage_tous_les_points(POINT tab[], FILE* file , int N){
  // Affiche tous les points du tableau en SVG.
  // Prend un tableau de points tab, un pointeur vers un fichier FILE, et un entier N représentant le nombre de points.
  for (int i = 0; i < N; i++) {
    POINT p;
    p.x = ((tab[i].x-inf)*1800/(sup-inf))+100;
    p.y = ((tab[i].y-inf)*1800/(sup-inf))+100;
    dessinerPoint(file, p, 8);
  }
}

char* dessinerCercle(FILE *file, double x, double y, double r, int algo)  {
  // Dessine un cercle en SVG.
  // Prend un pointeur vers un fichier FILE, les coordonnées x et y du centre, le rayon r, et un entier algo représentant l'algorithme.
  // Retourne une chaîne de caractères contenant le code SVG pour dessiner le cercle.
  char* codeCercle = malloc (sizeof (*codeCercle) * 500);
  if (algo == 1) {
    sprintf(codeCercle,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"red\" stroke-width=\"3\" fill=\"transparent\" fill-opacity=\"0\" />",x,y,r);
  }else if (algo == 2){
    sprintf(codeCercle,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"blue\" stroke-width=\"3\" fill=\"transparent\" fill-opacity=\"0\" />",x,y,r);
  }
  fprintf(file,"%s\n", codeCercle);
  return codeCercle;
}

char* dessinerDroite(FILE *file, DROITE d)  {
  // Dessine une droite en SVG.
  // Prend un pointeur vers un fichier FILE et une droite d de type DROITE.
  // Retourne une chaîne de caractères contenant le code SVG pour dessiner la droite.
  printf("Dessine la droite %f %f %f %f, pente:%f\n", d.x_a, d.y_a, d.x_b, d.y_b, d.pente);
  double xa = (d.x_a*1800/(sup - inf)) + 100;
  double xb = (d.x_b*1800/(sup - inf)) + 100;
  double yb = (d.y_b*1800/(sup - inf)) + 100;
  double ya = (d.y_a*1800/(sup - inf)) + 100;
  if (d.pente == HUGE_VAL || d.pente == (- HUGE_VAL)){
    fprintf(file, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"red\" stroke-width=\"5\" />\n", xa, ya, xb, yb);
    return 0;
  }
  fprintf(file, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"blue\" stroke-width=\"5\" />\n", xa, ya, xb, yb);
  return 0;
}

char* dessinerCentre(FILE *file, double x, double y) { 
  // Dessine une droite en SVG.
  // Prend un pointeur vers un fichier FILE et une droite d de type DROITE.
  // Retourne une chaîne de caractères contenant le code SVG pour dessiner la droite.
  char* codeCentre = malloc (sizeof (*codeCentre) * 500);
  sprintf(codeCentre,"<circle cx=\"%f\" cy=\"%f\" r=\"10\" stroke=\"red\" stroke-width=\"1\" fill=\"red\"/>",x,y);
  fprintf(file,"%s\n", codeCentre);
  return codeCentre;
}
