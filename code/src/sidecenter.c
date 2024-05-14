#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "global.h"

#define INF 999999999

int in_convex(POINT center, POINT* I, int N){
    CONVEX pente_min;
    CONVEX pente_max;
    /// Centre c'est dans 0,0
    for(int i = 0; i< N ; i++){
        I[i].x = I[i].x - center.x; 
    }
    /// On mets un points en (0,1)
    int x_decalage = I[0].x;
    int y_decalage = I[0].y;
    I[0].x = 0; 
    I[0].x = 1;
    for(int i = 0; i< N ; i++){
        I[i].x = I[i].x-x_decalage;
        I[i].y = I[i].y-y_decalage+1;
    }
    for(int i = 0; i< N ; i++){
        printf(" %.2f,%.2f ", I[i].x, I[i].y) ;
    }
    ///Verification des points avec x = 0
    for(int i = 0; i< N ; i++){
        if(I[i].x == 0 && I[i].y<0 ){
            //INTERIEUR
            return 0;
        }
    }
    int gauche = 0;
    int droite = 0; 
    CONVEX *pentes_gauche = malloc(N * sizeof(CONVEX));
    CONVEX *pentes_droite = malloc(N * sizeof(CONVEX));
    for(int i = 0; i< N ; i++){
        CONVEX res;
        if(I[i].x < 0){
            //La on cherche le max
            res.p = I[i];
            res.pente = I[i].y/I[i].x;
            pentes_gauche[gauche] = res;
            gauche = gauche + 1;
        }else if(I[i].x > 0){
            //La on cherche le min
            res.p = I[i];
            res.pente = I[i].y/I[i].x;
            pentes_droite[droite] = res; 
            droite = droite + 1;
        }
    }
    //Trouver le max des pentes gauches 
    if(gauche >0){
        pente_max.pente = pentes_gauche[0].pente;
        pente_max.p = pentes_gauche[0].p;
        for(int i = 1; i< gauche;i++){
            if(pentes_gauche[i].pente>pente_max.pente){
                pente_max.pente = pentes_gauche[i].pente;
                pente_max.p = pentes_gauche[i].p;
            }
        }  
    }else {
        pente_max.p.x = 0; 
        pente_max.p.y = 1;
        pente_max.pente = INFINITY * -1;    
    }
    // Trouver le min des pentes droites 
    if(droite>0){
        pente_min.pente = pentes_droite[0].pente;
        pente_min.p = pentes_droite[0].p;
        for(int i = 1; i< droite;i++){
            if(pentes_droite[i].pente<pente_min.pente){
                pente_min.pente = pentes_droite[i].pente;
                pente_min.p = pentes_droite[i].p;
            }
        }  
    }else {
        pente_min.p.x = 0; 
        pente_min.p.y = 1;
        pente_min.pente = INFINITY;    
    }

    ///Analyse des pentes 
    if(pente_min.pente!= INFINITY && pente_max.pente != (INFINITY * -1)){
        if(pente_min.pente > pente_max.pente){
            ///EXTERIEUR 
            double milieu = (pente_min.p.y+pente_max.p.y)/2;
            return milieu;
        }else {
            //INTERIEUR
            return 0;
        }    
    }else{
        //EXTERIEUR
        double milieu = (pente_min.p.y+pente_max.p.y)/2;
        return milieu;
    } 
}

int side_center (POINT center, POINT* contour, int longueur){
    int res = INF;
    if(longueur == 1){
        res = contour[0].y;
    }else if (longueur == 2){
        res = (contour[0].y+contour[1].y)/2;
    }else{
        /// On a au moins trois points 
        POINT *contour_copy = malloc(longueur * sizeof(POINT));
        for(int i = 0; i< longueur ; i++){
            contour_copy[i] = contour[i];
        }
        double s = in_convex(center,contour_copy, longueur);
        if (s == 0){
            res = 0; 
        }else if (s > 0){
            res = 1;             
        }else{
            res = -1;
        }
    }
    printf("cote %d", res);
    return res;
}