#include <stdio.h>
#include <stdlib.h>

#include "median.h"

// Fonction pour échanger deux valeurs dans un tableau
void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction pour trouver l'indice du pivot pour la partition
int partition(double *arr, int low, int high) {
    double pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Fonction pour trouver la médiane
double findMedian(double *arr, int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        int pivotIndex = partition(arr, low, high);
        if (pivotIndex - low == k - 1)
            return arr[pivotIndex];
        if (pivotIndex - low > k - 1)
            return findMedian(arr, low, pivotIndex - 1, k);
        return findMedian(arr, pivotIndex + 1, high, k - pivotIndex + low - 1);
    }
    return -1;
}

// Fonction pour calculer la médiane d'une liste de valeurs
double median(double *arr, int n) {
    if (n % 2 != 0)
        return findMedian(arr, 0, n - 1, n / 2 + 1);
    else
        return (findMedian(arr, 0, n - 1, n / 2) + findMedian(arr, 0, n - 1, n / 2 + 1)) / 2;
}

