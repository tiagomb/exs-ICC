#include <stdio.h>
#include <stdlib.h>
#include "polinomios.h"

void poliLagrange (int tam, double *x, double *y, double xe){
    double num = 1, res = 0;
    double *L = (double *) malloc (tam * sizeof(double));
    for (int i = 0; i<tam; i++){
        num *= (xe - x[i]);
    }
    for (int i = 0; i<tam; i++){
        L[i] = num;
        for (int j = 0; j<tam; j++){
            if (i != j){
                L[i] /= (x[i] - x[j]);
            }
        }
    }
    for (int i = 0; i<tam; i++){
        res += L[i] * y[i];
    }
    printf ("%1.16e\n", res);
    free (L);
}

void poliNewton (int tam, double *x, double *y, double xe){
    double res = 0, num = 1;
    double *D = (double *) malloc (tam * sizeof(double));
    for (int i = 0; i<tam; i++){
        D[i] = y[i];
    }
    for (int i = 0; i<tam; i++){
        if (i != 0){
            num *= (xe - x[i-1]);
        }
        res += num * D[i];
        for (int j = 0; j < tam - i - 1; j++){
            D[j+1] = (D[j+1] - D[j]) / (x[j+i+1] - x[j]);
        }
    }
    printf ("%1.16e\n", res);
    free (D);
}