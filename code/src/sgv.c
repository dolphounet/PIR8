
#include <math.h>
#include <stdio.h>
#include "global.h"
#include "structures.h"
#include "dessiner.h"
#include "calculs.h"

FILE *file;

//Dessine les points et le cercle dans le SVG
void ecritureSVG(POINT tab[], FILE* file , int N){
  for (int i = 0; i < N; i++) {
    POINT p;
    p.x = ((tab[i].x-inf)*1800/(sup-inf))+100;
    p.y = ((tab[i].y-inf)*1800/(sup-inf))+100;
    dessinerPoint(file, p, 8);
  }
  trouver_c(tab,file,N);
}

void GenerationFichierSVG(POINT* tab , int N){
  //creation et ouverture du fichier
  file= fopen("Points.svg", "w");
  
  //ecriture de l'entete

  fprintf(file,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
  fprintf(file,"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
  fprintf(file,"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
  fprintf(file,"<svg width=\"2000\" height=\"2000\" version=\"1.1\"\n");
  fprintf(file, "xmlns=\"http://www.w3.org/2000/svg\" style=\"background-color: white\">\n");
  fprintf(file, "<rect x=\"0\" y=\"0\" width=\"2000\" height=\"2000\" fill=\"#ffffff\" />\n");

  fprintf(file, "<line x1=\"100\" y1=\"100\" x2=\"1900\" y2=\"100\" stroke=\"black\" />\n"); // Axe x

  fprintf(file, "<text x=\"1900\" y=\"100\" font-family=\"Arial\" font-size=\"20\">%d</text>\n", sup);

  fprintf(file, "<line x1=\"100\" y1=\"100\" x2=\"100\" y2=\"1900\" stroke=\"black\" />\n"); // Axe y
  fprintf(file, "<text x=\"100\" y=\"100\" font-family=\"Arial\" font-size=\"20\">%d</text>\n", inf);
  fprintf(file, "<text x=\"100\" y=\"1900\" font-family=\"Arial\" font-size=\"20\">%d</text>\n", sup);    

 
  //ecriture du programme
  ecritureSVG(tab,file,N);
  //fin du programme et fermer le fichier
  fprintf(file, "</svg>\n");
  fclose(file);
}