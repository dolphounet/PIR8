#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"
#include "dessiner.h"
#include "incercle.h"
#include "fonctions.h"
#include "algonaif.h"

double centre_x, centre_y, rayon_welz, centre_x_dessin_welz,centre_y_dessin_welz,rayon_dessin_welz,taille;
POINT reference;

int cercle_possible(POINT p, POINT q, POINT r){
    double d = (p.x * (q.y - r.y) + q.x * (r.y - p.y) + r.x * (p.y - q.y)) * 2 ;
    if (d!=0){
        return 1; //POSSIBLE
    }else{
        return 0; //PAS POSSIBLE 
    }
}

double dista(POINT p1, POINT p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

int is_inside(CERCLE c , POINT p) {
    POINT centre;
    centre.x = c.x_cercle; 
    centre.y = c.y_cercle;
    if (dista(centre, p) <= c.rayon_cercle){
        return 1;
    }else{
        return 0;
    }
}

int is_valid_circle(CERCLE c, POINT *P, int size) {
    for (int i = 0; i < size; i++) {
        if (!is_inside(c, P[i])) {
            return 0;
        }
    }
    return 1;
}

int point_in_cercle_welz(POINT test, double cx, double cy, double r){
  POINT centre;
  centre.x = cx; 
  centre.y = cy; 
  double dist_point_center = dista(centre, test); 
  if (dist_point_center <= r){
    return 1; //INTERIEUR
  }else{
    return 0; //EXTERIEUR
  }
}

void val_dessin (POINT p1, double centrex,double centrey){
    centre_x_dessin_welz = ((centrex-inf)*1800/(sup-inf))+100;
    centre_y_dessin_welz = ((centrey-inf)*1800/(sup-inf))+100;
    double n_pix = ((p1.x-inf)*1800/(sup-inf))+100;
    double n_piy = ((p1.y-inf)*1800/(sup-inf))+100;

    rayon_dessin_welz = sqrt(pow(centre_x_dessin_welz - n_pix, 2) + pow(centre_y_dessin_welz - n_piy, 2));
}
CERCLE findCircle_welz(POINT p1, POINT p2, POINT p3) {
    // Calcul des coordonnées du centre 
    double m1 = (p2.y - p1.y) / (p2.x - p1.x);
    double m2 = (p3.y - p2.y) / (p3.x - p2.x);

    centre_x = (m1 * m2 * (p3.y - p1.y) + m1 * (p2.x + p3.x) - m2 * (p1.x + p2.x)) / (2 * (m1 - m2));
    centre_y = -1 * (centre_x - (p1.x + p2.x) / 2) / m1 + (p1.y + p2.y) / 2;
    rayon_welz = sqrt(pow(centre_x - p1.x, 2) + pow(centre_y- p1.y, 2));
    return (CERCLE){centre_x,centre_y,rayon_welz};
}

CERCLE min_cercle_trivial(int size_points,POINT* R, int size_R){
 
    CERCLE d = (CERCLE){0,0,0 };

    if (size_points == 0 && size_R==0){
        return d;
    }else if (size_R == 1){
        d.x_cercle = R[0].x;
        d.y_cercle = R[0].y;
        d.rayon_cercle = 0;
    }else if (size_R == 2){
        d.x_cercle = (R[0].x+R[1].x)/2;
        d.y_cercle = (R[0].y+R[1].y)/2;
        d.rayon_cercle = dista(R[0],R[1])/2;
        reference = R[0];
        taille =1;
    }else{
        if(cercle_possible(R[0],R[1],R[2])==1){
            d = findCircle_welz (R[0],R[1],R[2]);
            //printf("CERCLE 3 x %.2f, y %.2f\n", centre_x,rayon_welz);
            reference = R[0];
            taille =1;
        } 
    }
    return d;
}


CERCLE welz (POINT* tab_copy, POINT* R, int N, int S){
    //printf("WELZ\nN %d\nR %d\n", N,S);
    CERCLE d;
    d.x_cercle = 0;
    d.y_cercle = 0; 
    d.rayon_cercle = -1;
    if (N==0 || S==3){
        return min_cercle_trivial(0,R, S);
    }else{
        int indice = rand()%N;
        POINT p = tab_copy[indice];
        tab_copy[indice].x = tab_copy[N-1].x;
        tab_copy[indice].y = tab_copy[N-1].y;
        d = welz (tab_copy, R, N-1, S);
        tab_copy[N-1].x = p.x;
        tab_copy[N-1].y = p.y;
        /*for (int i=0; i<N;i++){
            printf("TAB p1x %.2f, p2y %.2f\n",tab_copy[i].x, tab_copy[i].y);
        } */
        //printf("WELZ\n\nCERCLE %.2f, RAYON %.2f\n", d.x_cercle,d.rayon_cercle);
        if (point_in_cercle_welz(p,d.x_cercle, d.y_cercle, d.rayon_cercle)==0){
            R[S] = p; 
           /// printf("POINT AJOUTER\n\nx %.2f, y %.2f\n", p.x,p.y);
            d = welz (tab_copy, R, N-1, S+1);  
        }            
    }
    return d;
}

CERCLE welz_init (POINT* tab , int N){
    
    POINT *tab_copy = malloc(N * sizeof(POINT));
    for(int i = 0; i< N ; i++){
        tab_copy[i] = tab[i];
    }
    POINT *R = malloc(3 * sizeof(POINT));
    reference.x =0;
    reference.y =0; 
    taille = 0; 
    int size = 0;
    CERCLE resultat= welz(tab_copy, R, N, size);
    free(tab_copy);
    free(R);
    return resultat;
}

void solution_welz (POINT* tab,FILE *file, int N){
    CERCLE cercle_welz = welz_init(tab,N);
    printf("WELZ\n\ncentreX %.2f, centreY %.2f, rayon %.2f \n\n", cercle_welz.x_cercle, cercle_welz.y_cercle,cercle_welz.rayon_cercle);
    if (taille == 1){
        val_dessin(reference, cercle_welz.x_cercle, cercle_welz.y_cercle);
        dessinerCercle(file, centre_x_dessin_welz, centre_y_dessin_welz, rayon_dessin_welz,2);
    }
}
