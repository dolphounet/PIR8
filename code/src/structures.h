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
} DROITE;

#endif
