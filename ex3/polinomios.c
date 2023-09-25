#include <stdio.h>
#include <stdlib.h>
#include "polinomios.h"

void poliLagrange (int tam, double *x, double *y, double xe){
    double num = 1, res = 0;
    double *L = (double *) malloc (tam * sizeof(double));
    for (int i = 0; i<tam; i++){ //calcula o numerador
        num *= (xe - x[i]);
    }
    for (int i = 0; i<tam; i++){
        L[i] = num/(xe - x[i]); //começa dividindo pelo termo adicionado
        for (int j = 0; j<tam; j++){
            if (i != j){
                L[i] /= (x[i] - x[j]); //divide pelos termos restantes
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
        D[i] = y[i]; //dif. dividida de ordem 0
    }
    for (int i = 0; i<tam; i++){
        if (i != 0){
            num *= (xe - x[i-1]);
        }
        res += num * D[i];
        for (int j = tam - 1; j > i; j--){
            D[j] = (D[j] - D[j - 1]) / (x[j] - x[j - i - 1]); //calcula diferenças divididas de ordem i+1
        }
    }
    printf ("%1.16e\n", res);
    free (D);
}