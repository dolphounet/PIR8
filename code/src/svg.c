
#include <math.h>
#include <stdio.h>
#include "global.h"
#include "structures.h"
#include "dessiner.h"
#include "algonaif.h"
#include "brutForce.h"
#include "megiddo.h"
#include "welz.h"

FILE *file;
int i;

void GenerationFichierSVG(POINT* tab , int N, int choix){
  //creation et ouverture du fichier
  remove("Points.svg");
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

 
  //affichage des points
  affichage_tous_les_points(tab, file, N);
  if(choix == 1) {
    solution_algo_naif(tab, file, N);
  }else if (choix == 2){
    solution_welz(tab, file, N);
  }else if(choix == 3) {
    DROITE d;
    d.x_a = xmin - inf;
    d.x_b = xmax - inf;
    d.y_b = (ymax - inf)/2;
    d.y_a = d.y_b;
    d.pente = (d.y_b - d.y_a) / (d.x_b - d.x_a);
    d.ordonnee = d.y_a - d.pente * d.x_a;
    dessinerDroite(file, d);
    recherche(tab, d);
  }
  else if(choix == 4) {
    
    DROITE* droite_tab = algo_megiddo(tab, N);
    
    for (i = 0; i<(N/2 + 2); i++) {
      dessinerDroite(file, droite_tab[i]);
    }
    
  }
  //fin du programme et fermer le fichier
  fprintf(file, "</svg>\n");
  fclose(file);
}
