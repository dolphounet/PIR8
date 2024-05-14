#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "median.h"

int N=11; // Nombre de points
int D=10; //Distance max à l'origine
double epsilon=0.0001; // Valeur de l'erreur prise pour la comparaison des distances des points au centre

// Définition de la structure Point
typedef struct {
    int x;
    int y;
} Point;

// Fonction pour initialiser les valeurs des points avec des coordonnées aléatoires
void initialiserPoints(Point *listePoints, int taille) {
    srand(time(NULL)); // Initialisation de la graine aléatoire

    for (int i = 0; i < taille; ++i) {
        double distance;
        do {
            listePoints[i].x = rand() % 21 - 10; // Valeurs aléatoires entre -10 et 10
            listePoints[i].y = rand() % 21 - 10;
            distance = sqrt(pow(listePoints[i].x, 2) + pow(listePoints[i].y, 2));
        } while (distance >= 10); // Tant que la distance à l'origine est supérieure ou égale à 10
    }
}

double valeurCritique(const Point p1, const Point p2){
    if (p1.x != p2.x){
        return (pow(p2.x,2) - pow(p1.x,2) + pow(p2.y,2) - pow(p1.y,2))/(2*(p2.x - p1.x));
    }
    return 0;
}

double g(double x, Point listePoints[], int estGarde[], int N){
    int i = 0;
    double gmax;
    double gi;
    do {
        gmax = pow(x-listePoints[i].x, 2) + pow(listePoints[i].y, 2);
        printf("gmax : %f, point numero : %d\n", gmax, i+1);
        i+=1;
    } while (estGarde[i] == 0 && i < N);

    for (int j = i; j < N; ++j) {
        if (estGarde[j] == 1){
            gi = pow(x-listePoints[j].x, 2) + pow(listePoints[j].y, 2);
            printf("gi : %f, point numero : %d\n", gi, j+1);
            if (gi > gmax){
                gmax = gi;
                printf("gmax : %f, point numero : %d\n", gmax, j+1);
            }
        }
    }
    return gmax;
}

int* findIndices(double x_med, Point* listePoints, int N, double gmax, int* taille) {
    int* indices = malloc(N * sizeof(int));
    if (indices == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(1);
    }

    int count = 0;
    for (int j = 0; j < N; j++) {
        if (gmax-epsilon < pow(x_med - listePoints[j].x, 2) + pow(listePoints[j].y, 2) && pow(x_med - listePoints[j].x, 2) + pow(listePoints[j].y, 2) < gmax+epsilon) {
            indices[count] = j;
            count++;
        }
    }

    // Réduire la taille du tableau à la taille réelle
    indices = realloc(indices, count * sizeof(int));
    if (indices == NULL) {
        printf("Erreur de réallocation de mémoire.\n");
        exit(1);
    }

    *taille = count;
    return indices;
}

int main() {
    // Initialisation des points
    int P=(int)floor(N/2); // Nombre de paires possibles
    int tailleI = N;
    Point listePoints[N];
    int estGarde[N];
    initialiserPoints(listePoints, N);

    // Premier parcours de la liste pour chercher des points ayant la même abscisse
    for (int i = 2*P - 2; i >= 0; i-=2) {
        if (listePoints[i].x == listePoints[i+1].x){
            if (abs(listePoints[i].y) < abs(listePoints[i+1].y)){
                estGarde[i+1] = 1;
            }
            else {
                estGarde[i] = 1;
            }
        }
        else {
            estGarde[i] = 1;
            estGarde[i+1] = 1;
        }
    }
    if (N % 2 == 1){ // Si N est impair, on garde le dernier point
        estGarde[N-1] = 1;
    }

    // Valeurs critiques
    double valeursCritiques[P];
    int j = 0;
    for (int i = 0; i < N; i+=2){
        if (listePoints[i].x != listePoints[i+1].x){
            valeursCritiques[j] = valeurCritique(listePoints[i], listePoints[i+1]);
            j+=1;
        }
    }


    // Affichage des points et des indices
    printf("Liste des points :\n");
    for (int i = 0; i < N; ++i) {
        printf("Point %d : (%d, %d)\n", i + 1, listePoints[i].x, listePoints[i].y);
    }

    // Affichage des point gardés
    printf("Liste des points gardés :\n");
    for (int i = 0; i < N; ++i) {
        if (estGarde[i] == 1){
            printf("Point %d : (%d, %d)\n", i + 1, listePoints[i].x, listePoints[i].y);
        }
    }

    double x_med = median(valeursCritiques, P);
    printf("Médiane des valeurs critiques : %f\n", x_med);

    // Affichage de la valeur de g(x_med)
    double gmax = g(x_med, listePoints, estGarde, N);
    printf("Valeur de g : %f\n", gmax);

    int *indices = findIndices(x_med, listePoints, N, gmax, &tailleI);
    printf("Points gardés : ");
    for (int i = 0; i < tailleI; ++i) {
        printf("%d \n", indices[i]+1);
    }

    // Test de la fin de l'algorithme
    int inf=1;
    int sup=1;

    for (int i = 0; i < tailleI; i++){
        if (listePoints[indices[i]].x <= x_med){
            sup=0;
            break;
        }
    }

    for (int i = 0; i < tailleI; i++){
        if (listePoints[indices[i]].x >= x_med){
            inf=0;
            break;
        }
    }

    if (inf == 0 && sup == 0){
        printf("Centre trouvé : (%f, 0) et le rayon est de %f\n", x_med, sqrt(gmax));
    }

    // Libération de la mémoire
    free(indices);
    return 0;
}
