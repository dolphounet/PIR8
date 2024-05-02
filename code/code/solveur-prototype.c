#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "structures.h"

#define TAILLEPOINT 3 //Diametre d'un point


POINT* convertirEntree (int N);
char* dessinerPoint(FILE *file, POINT p, int size);
void ecritureSVG(POINT tab[], FILE* file , int N);
void GenerationFichierSVG(POINT tab[] , int N);


int i=0, j=0;

/*
 * Convertit les coordonnées de l'entrée standard en un tableau de POINTS
 * @param N nombre de points
*/

POINT* convertirEntree (int N){
  POINT* tab=malloc (sizeof(POINT)*N);
  char chaine[10];
  for (i=0;i<N;i++){
    while((chaine[j] = getc(stdin)) != ' ' && chaine[j]!=EOF){
      j++;
    }
    /* printf("%s ", chaine); */
    tab[i].x=atoi(chaine);
    printf("%d ", tab[i].x); 
    strcpy(chaine, "");
    j=0;
    while((chaine[j]= getc(stdin)) != '\n' && chaine[j]!=EOF){
      j++;
    }
    /* printf("%s\n", chaine); */
    tab[i].y=atoi(chaine);
    printf("%d\n", tab[i].y); 
    strcpy(chaine, "");
    j=0;
  }
  return tab;
}

//dessine un cercle en SVG
char* dessinerCercle(FILE *file, int x, int y, int r){
  char* codeCercle= malloc (sizeof (*codeCercle) *500);
  sprintf(codeCercle,"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"red\" stroke-width=\"3\" fill=\"transparent\" fill-opacity=\"0\" />",x,y,r);
  fprintf(file,"%s\n", codeCercle);
  return codeCercle;
}


//Dessine un point en SVG
char* dessinerPoint(FILE *file, POINT p, int r){ 
  char* codePoint= malloc (sizeof (*codePoint) * 500);
  sprintf(codePoint,"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"black\" stroke-width=\"3\" fill=\"black\"/>",p.x,p.y,r);
  fprintf(file,"%s\n", codePoint);
  return codePoint;
}

//Dessine les points et le cercle dans le SVG
void ecritureSVG(POINT tab[], FILE* file , int N){
  //On dessine tous les points dans le SVG
  for(i=0; i<N; i++){
    dessinerPoint(file, tab[i], TAILLEPOINT);
  }
}


//Genere le fichier SVG complet
void GenerationFichierSVG(POINT tab[] , int N){
  //creation et ouverture du fichier
  FILE *file;
  file= fopen("Points.svg", "w");
  
  //ecriture de l'entete
  fprintf(file,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
  fprintf(file,"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
  fprintf(file,"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
  fprintf(file,"<svg width=\"500\" height=\"500\" version=\"1.1\"\n");
  fprintf(file,"xmlns=\"http://www.w3.org/2000/svg\">\n");
  
  //ecriture du programme
  ecritureSVG(tab,file,N);
  
  //fin du programme et fermer le fichier
  fprintf(file, "</svg>\n");
  fclose(file);
}

int main(){
  
  char nbPointsStr[10]; //Contiendra les caractères lus pour le nb de points
  int k = 0;

  while((nbPointsStr[k] = getc(stdin)) != ' ' && nbPointsStr[k]!=EOF){
      k++;
  }
  

  int nbPoints = atoi(nbPointsStr);
  printf("\n*\nNombre de points lu: %s \n*\n", nbPointsStr);
  
  POINT *tab = convertirEntree( nbPoints );
  printf("*\nPoints lus sur le stdin et convertis !\n*\n");
  
  GenerationFichierSVG(tab , nbPoints);
  printf("*\nFichier SVG généré !  \n*\n");
  
  return 0;
}
