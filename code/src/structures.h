#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct model_point{
	double x;
	double y;
} POINT;

typedef struct model_cercle{
	double x_cercle;
	double y_cercle;
	double rayon_cercle;
} CERCLE;

typedef struct model_droite{
	double x_a, x_b;
	double y_a, y_b;
	double pente;
	double ordonnee;
  int i;
  int j;
} DROITE;

typedef struct model_convex{
	POINT p;
	double pente; 
} CONVEX;

typedef struct model_droite2{
  double a, b, c; // ax + by + c = 0
  int i;
  int j;
} DROITE2;

typedef struct model_paire{
  DROITE2* i;
  DROITE2* j;
  POINT intersec;
}PAIRE;

#endif
