// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "sistemas.h"
#include "utils.h"
#include "interval.h"

/*A função abaixo realiza a troca de linhas para o pivoteamento parcial da Eliminação de Gauss*/
void trocaLinhas (intervalo_t **a, intervalo_t *b, int i, int pivo){
    intervalo_t *aux;
    aux = a[i];
    a[i] = a[pivo];
    a[pivo] = aux;
    intervalo_t aux2;
    aux2 = b[i];
    b[i] = b[pivo];
    b[pivo] = aux2;
}

/*Encontra o pivo para o pivoteamento parcial da Eliminação de Gauss*/
int encontraPivo (intervalo_t **a, int i, int tam){
    int pivo = i;
    for (int j = i + 1; j < tam; j++){
        if (fabs(a[j][i].inicio) > fabs(a[pivo][i].inicio)){
            pivo = j;
        }
    }
    return pivo;
}

/*Realiza a Eliminação de Gauss com pivoteamento parcial em uma matriz de intervalos*/
void gaussComMult (intervalo_t **a, intervalo_t *b, int tam){
    intervalo_t m, mult;
    for (int i = 0; i < tam; i++){
        int pivo = encontraPivo (a, i, tam);
        if (pivo != i)
            trocaLinhas (a, b, i, pivo);
        for (int j = i + 1; j < tam; j++){
            divideIntervalo (a[j][i], a[i][i], &m);
            a[j][i].inicio = a[j][i].fim =  0;
            for (int k = i+1; k < tam; k++){
                multiplicaIntervalo (m, a[i][k], &mult);
                subtraiIntervalo (a[j][k], mult , &a[j][k]);
            }
            multiplicaIntervalo (m, b[i], &mult);
            subtraiIntervalo (b[j], mult, &b[j]);
        }
    }
}

/*Aplica a retrossubstituição em uma matriz de intervalos triangularizada pela Eliminação de Gauss*/
void retroSub (intervalo_t **a, intervalo_t *b, intervalo_t *x, int tam){
    intervalo_t aux;
    for (int i = tam - 1; i >= 0; i--){
        x[i].inicio = b[i].inicio;
        x[i].fim = b[i].fim;
        for (int j = i + 1; j < tam; j++){
            multiplicaIntervalo (a[i][j], x[j], &aux);
            subtraiIntervalo (x[i], aux, &x[i]);
        }
        divideIntervalo (x[i], a[i][i], &aux);
        x[i].inicio = aux.inicio;
        x[i].fim = aux.fim;
    }
}

/*Calcula o resíduo do polinômio obtido através do Método dos Mínimos Quadrados com base na fórmula r[i] = y[i] -f(x[i])*/
void calculaResiduo (intervalo_t *coef, intervalo_t *x, intervalo_t *y, int pontos, int tam){
    intervalo_t *r, aux, potencia;
    r = malloc (pontos * sizeof (intervalo_t ));
    for (int i = 0; i < pontos; i++){
        r[i].inicio = y[i].inicio;
        r[i].fim = y[i].fim;
        for (int j = 0; j < tam; j++){
            potencia.inicio = x[i].inicio;
            potencia.fim = x[i].fim;
            potenciaIntervalo (x[i], j, &potencia);
            multiplicaIntervalo (coef[j], potencia, &aux);
            subtraiIntervalo (r[i], aux, &r[i]);
        }
        printf ("[%1.16e, %1.16e] ", r[i].inicio, r[i].fim);
    }
    printf ("\n");
    free (r);
}

/*Imprime a matriz de intervalos*/
void imprimeMatriz (intervalo_t **a, intervalo_t *b, int tam){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            printf ("[%1.16e, %1.16e] ", a[i][j].inicio, a[i][j].fim);
        }
        printf ("[%1.16e, %1.16e]\n ", b[i].inicio, b[i].fim);
    }
}

/*Calcula o somatório do Método dos Mínimos Quadrados*/
void somatorio (int expoenteCima, int expoenteBaixo, intervalo_t *x, int k, intervalo_t *soma){
    intervalo_t potencia1, potencia2, mult;
    soma->inicio = soma->fim = 0;
    for (int i = 0; i < k; i++){
        potenciaIntervalo (x[i], expoenteCima, &potencia1);
        potenciaIntervalo (x[i], expoenteBaixo, &potencia2);
        multiplicaIntervalo (potencia1, potencia2, &mult);
        adicionaIntervalo (*soma, mult, soma);
    }
}

/*Calcula o lado direito do sistema linear*/
void calculaB (intervalo_t *b, int n, int k, intervalo_t *y, intervalo_t *x){
    intervalo_t potencia, mult;
    for (int i = 0; i < n; i++){
        b[i].inicio = b[i].fim = 0;
        for (int j = 0; j < k; j++){
            potenciaIntervalo (x[j], i, &potencia);
            multiplicaIntervalo (potencia, y[j], &mult);
            adicionaIntervalo (b[i], mult, &b[i]);
        }
    }
    
}