#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "metodos.h"
#include "utils.h"

void trocaLinhas (double **a, double *b, int i, int pivo){
    double *aux;
    aux = a[i];
    a[i] = a[pivo];
    a[pivo] = aux;
    double aux2;
    aux2 = b[i];
    b[i] = b[pivo];
    b[pivo] = aux2;
}
int encontraPivo (double **a, int i, int tam){
    int pivo = i;
    for (int j = i + 1; j < tam; j++){
        if (fabs(a[j][i]) > fabs(a[pivo][i])){
            pivo = j;
        }
    }
    return pivo;
}

void gaussComMult (double **a, double *b, int tam){
    double m;
    for (int i = 0; i < tam; i++){
        int pivo = encontraPivo (a, i, tam);
        if (pivo != i)
            trocaLinhas (a, b, i, pivo);
        for (int j = i + 1; j < tam; j++){
            m = a[j][i] / a[i][i];
            a[j][i] = 0;
            for (int k = i+1; k < tam; k++){
                a[j][k] -= m * a[i][k];
            }
            b[j] -= m * b[i];
        }
    }
}

void gaussSemMult (double **a, double *b, int tam){
    for (int i = 0; i < tam; i++){
        int pivo = encontraPivo (a, i, tam);
        if (pivo != i)
            trocaLinhas (a, b, i, pivo);
        for (int j = i + 1; j < tam; j++){
            for (int k = i+1; k < tam; k++){
                a[j][k] = a[j][k] * a[i][i] - a[i][k] * a[j][i];
            }
            b[j] = b[j] * a[i][i] - b[i] * a[j][i];
            a[j][i] = 0;
        }
    }
}

void semPivo (double **a, double *b, int tam){
    double m;
    for (int i = 0; i < tam - 1; i++){
        m = a[i][i];
        for (int j = i; j < tam; j++){
            a[i][j] /= m;
        }
        b[i] /= m;
        for (int k = i+1; k < tam; k++){
            m = a[k][i];
            for (int j = i; j < tam; j++){
                a[k][j] -= m * a[i][j];
            }
            b[k] -= m * b[i];
        }
    }
}

void retroSub (double **a, double *b, double *x, int tam){
    for (int i = tam - 1; i >= 0; i--){
        x[i] = b[i];
        for (int j = i + 1; j < tam; j++){
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }
}

void leMatriz (double **a, double *b, int tam){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            if (scanf ("%lf", &a[i][j]) != 1){
                printf ("Erro na leitura da matriz\n");
                exit (1);
            }
        }
        if (scanf ("%lf", &b[i]) != 1){
            printf ("Erro na leitura da matriz\n");
            exit (1);
        }
    }
}

void calculaResiduo (double **a, double *b, double *x, int tam){
    double *r;
    r = malloc (tam * sizeof (double));
    for (int i = 0; i < tam; i++){
        r[i] = 0;
        for (int j = 0; j < tam; j++){
            r[i] += a[i][j] * x[j];
        }
        r[i] -= b[i];
    }
    printf ("[ ");
    for (int i = 0; i < tam; i++){
        printf ("%1.8e ", r[i]);
    }
    printf ("]\n");
    free (r);
}

// void imprimeMatriz (double **a, double *b, int tam){
//     for (int i = 0; i < tam; i++){
//         for (int j = 0; j < tam; j++){
//             printf ("%lf ", a[i][j]);
//         }
//         printf ("%lf\n", b[i]);
//     }
// }

void copiaMatriz (double **a, double **a2, double *b, double *b2, int tam){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            a2[i][j] = a[i][j];
        }
        b2[i] = b[i];
    }
}