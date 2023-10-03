#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "sistemas.h"
#include "utils.h"
#include "interval.h"

/*A função abaixo realiza a troca de linhas para o pivoteamento parcial da Eliminação de Gauss*/
void trocaLinhas (double ***a, double **b, int i, int pivo){
    double **aux;
    aux = a[i];
    a[i] = a[pivo];
    a[pivo] = aux;
    double *aux2;
    aux2 = b[i];
    b[i] = b[pivo];
    b[pivo] = aux2;
}

/*Encontra o pivo para o pivoteamento parcial da Eliminação de Gauss*/
int encontraPivo (double ***a, int i, int tam){
    int pivo = i;
    for (int j = i + 1; j < tam; j++){
        if (fabs(a[j][i][0]) > fabs(a[pivo][i][0])){
            pivo = j;
        }
    }
    return pivo;
}

/*Realiza a Eliminação de Gauss com pivoteamento parcial em uma matriz de intervalos*/
void gaussComMult (double ***a, double **b, int tam){
    double m[2], mult[2];
    for (int i = 0; i < tam; i++){
        int pivo = encontraPivo (a, i, tam);
        if (pivo != i)
            trocaLinhas (a, b, i, pivo);
        for (int j = i + 1; j < tam; j++){
            divideIntervalo (a[j][i], a[i][i], m);
            a[j][i][0] = a[j][i][1] =  0;
            for (int k = i+1; k < tam; k++){
                multiplicaIntervalo (m, a[i][k], mult);
                subtraiIntervalo (a[j][k], mult , a[j][k]);
            }
            multiplicaIntervalo (m, b[i], mult);
            subtraiIntervalo (b[j], mult, b[j]);
        }
    }
}

/*Aplica a retrossubstituição em uma matriz de intervalos triangularizada pela Eliminação de Gauss*/
void retroSub (double ***a, double **b, double **x, int tam){
    double aux[2];
    for (int i = tam - 1; i >= 0; i--){
        x[i][0] = b[i][0];
        x[i][1] = b[i][1];
        for (int j = i + 1; j < tam; j++){
            multiplicaIntervalo (a[i][j], x[j], aux);
            subtraiIntervalo (x[i], aux, x[i]);
        }
        divideIntervalo (x[i], a[i][i], aux);
        x[i][0] = aux[0];
        x[i][1] = aux[1];
    }
}

/*Calcula o resíduo do polinômio obtido através do Método dos Mínimos Quadrados com base na fórmula r[i] = y[i] -f(x[i])*/
void calculaResiduo (double **coef, double **x, double **y, int pontos, int tam){
    double **r, aux[2], potencia[2];
    r = malloc (pontos * sizeof (double *));
    for (int i = 0; i < pontos; i++){
        r[i] = malloc (2 * sizeof (double));
    }
    for (int i = 0; i < pontos; i++){
        r[i][0] = y[i][0];
        r[i][1] = y[i][1];
        for (int j = 0; j < tam; j++){
            potencia[0] = x[i][0];
            potencia[1] = x[i][1];
            potenciaIntervalo (x[i], j, potencia);
            multiplicaIntervalo (coef[j], potencia, aux);
            subtraiIntervalo (r[i], aux, r[i]);
        }
        printf ("[%1.16e, %1.16e] ", r[i][0], r[i][1]);
        free (r[i]);
    }
    printf ("\n");
    free (r);
}

/*Imprime a matriz de intervalos*/
void imprimeMatriz (double ***a, double **b, int tam){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            printf ("[%1.16e, %1.16e] ", a[i][j][0], a[i][j][1]);
        }
        printf ("[%1.16e, %1.16e]\n ", b[i][0], b[i][1]);
    }
}

/*Calcula o somatório do Método dos Mínimos Quadrados*/
void somatorio (int expoenteCima, int expoenteBaixo, double **x, int k, double soma[2]){
    double potencia1[2], potencia2[2], mult[2];
    soma[0] = soma[1] = 0;
    for (int i = 0; i < k; i++){
        potenciaIntervalo (x[i], expoenteCima, potencia1);
        potenciaIntervalo (x[i], expoenteBaixo, potencia2);
        multiplicaIntervalo (potencia1, potencia2, mult);
        adicionaIntervalo (soma, mult, soma);
    }
}

/*Calcula o lado direito do sistema linear*/
void calculaB (double **b, int n, int k, double **y, double **x){
    double potencia[2], mult[2];
    for (int i = 0; i < n; i++){
        b[i][0] = b[i][1] = 0;
        for (int j = 0; j < k; j++){
            potenciaIntervalo (x[j], i, potencia);
            multiplicaIntervalo (potencia, y[j], mult);
            adicionaIntervalo (b[i], mult, b[i]);
        }
    }
}