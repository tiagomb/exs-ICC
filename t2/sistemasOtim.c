// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "sistemasOtim.h"
#include "utilsOtim.h"
#include "intervalOtim.h"

/*Recebe como parâmetro a matriz e o vetor que representam o sistema linear, e dois inteiros indicando a linha
atual e a linha do pivô para que possam ser trocadas, tanto na matriz quando no vetor*/
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

/*Recebe como parâmetro a matriz que representa o lado esquerdo do sistema linear, e dois inteiros representando
a linha atual e o tamanho da matriz. Retorna a linha do pivôs*/
int encontraPivo (intervalo_t **a, int i, int tam){
    int pivo = i;
    for (int j = i + 1; j < tam; j++){
        if (fabs(a[j][i].inicio) > fabs(a[pivo][i].inicio)){
            pivo = j;
        }
    }
    return pivo;
}

/*Recebe como paramêtros a matriz e o vetor que representam o sistema linear e o tamanho desse sistema.
Realiza a Eliminação de Gauss com multiplicador e pivoteamento parcial*/
void gaussComMult (intervalo_t **a, intervalo_t *b, int tam){
    intervalo_t m, mult;
    for (int i = 0; i < tam; i++){ //modificar loops (talvez loop unroll para 4)
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

/*Recebe como parâmetros a matriz de intervalos, o vetor de intervalos e o tamanho do sistema.
Realiza a retrosubstituição e retorna o vetor solução*/
void retroSub (intervalo_t **a, intervalo_t *b, intervalo_t *x, int tam){
    intervalo_t aux;
    for (int i = tam - 1; i >= 0; i--){ //alterar loops
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

void calculaParteResiduo (intervalo_t x, int expoente, intervalo_t coef, intervalo_t r){
    intervalo_t potencia, aux;
    potencia.inicio = x.inicio;
    potencia.fim = x.fim;
    potenciaIntervalo (x, expoente, &potencia);
    multiplicaIntervalo (potencia, coef, &aux);
    subtraiIntervalo (r, aux, &r);
}

/*Recebe como parâmetros os coeficientes obtidos após a resolução do sistema linear, os pontos x e f(x), a quantidade de pontos e o tamanho do polinômio.
Calcula o resíduo na forma r(i) = f(x(i)) - p(x(i)) e imprime na tela*/
void calculaResiduo (intervalo_t *coef, intervalo_t *x, intervalo_t *y, long long int pontos, int tam){
    intervalo_t *r;
    r = malloc (pontos * sizeof (intervalo_t ));
    for (long long int i = 0; i < pontos-pontos%8; i+=8){ //loop unroll e block
        r[i].inicio = y[i].inicio;
        r[i].fim = y[i].fim;
        r[i+1].inicio = y[i+1].inicio;
        r[i+1].fim = y[i+1].fim;
        r[i+2].inicio = y[i+2].inicio;
        r[i+2].fim = y[i+2].fim;
        r[i+3].inicio = y[i+3].inicio;
        r[i+3].fim = y[i+3].fim;
        r[i+4].inicio = y[i+4].inicio;
        r[i+4].fim = y[i+4].fim;
        r[i+5].inicio = y[i+5].inicio;
        r[i+5].fim = y[i+5].fim;
        r[i+6].inicio = y[i+6].inicio;
        r[i+6].fim = y[i+6].fim;
        r[i+7].inicio = y[i+7].inicio;
        r[i+7].fim = y[i+7].fim;
        for (int j = 0; j < tam; j++){
            calculaParteResiduo (x[i], j, coef[j], r[i]);
            calculaParteResiduo (x[i+1], j, coef[j], r[i+1]);
            calculaParteResiduo (x[i+2], j, coef[j], r[i+2]);
            calculaParteResiduo (x[i+3], j, coef[j], r[i+3]);
            calculaParteResiduo (x[i+4], j, coef[j], r[i+4]);
            calculaParteResiduo (x[i+5], j, coef[j], r[i+5]);
            calculaParteResiduo (x[i+6], j, coef[j], r[i+6]);
            calculaParteResiduo (x[i+7], j, coef[j], r[i+7]);
        }
        printf ("[%1.16e, %1.16e] ", r[i].inicio, r[i].fim);
        printf ("[%1.16e, %1.16e] ", r[i+1].inicio, r[i+1].fim);
        printf ("[%1.16e, %1.16e] ", r[i+2].inicio, r[i+2].fim);
        printf ("[%1.16e, %1.16e] ", r[i+3].inicio, r[i+3].fim);
        printf ("[%1.16e, %1.16e] ", r[i+4].inicio, r[i+4].fim);
        printf ("[%1.16e, %1.16e] ", r[i+5].inicio, r[i+5].fim);
        printf ("[%1.16e, %1.16e] ", r[i+6].inicio, r[i+6].fim);
        printf ("[%1.16e, %1.16e] ", r[i+7].inicio, r[i+7].fim);
    }
    for (long long int i = pontos-pontos%8; i < pontos; i++){
        r[i].inicio = y[i].inicio;
        r[i].fim = y[i].fim;
        for (int j = 0; j < tam; j++){
            calculaParteResiduo (x[i], j, coef[j], r[i]);
        }
        printf ("[%1.16e, %1.16e] ", r[i].inicio, r[i].fim);
    }
    printf ("\n");
    free (r);
}

/*Recebe como parâmetros a matriz e o vetor que representam o sistema linear, e um inteiro indicando seu tamanho.
Imprime a matriz para fins de teste*/
void imprimeMatriz (intervalo_t **a, intervalo_t *b, int tam){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            printf ("[%1.16e, %1.16e] ", a[i][j].inicio, a[i][j].fim);
        }
        printf ("[%1.16e, %1.16e]\n ", b[i].inicio, b[i].fim);
    }
}

void calculaParte (intervalo_t x, intervalo_t y, int expoente, intervalo_t b, intervalo_t soma){
    intervalo_t potencia;
    potenciaIntervalo(x, expoente, &potencia);
    adicionaIntervalo(soma, potencia, &soma);
    multiplicaIntervalo(potencia, y, &potencia);
    adicionaIntervalo(b, potencia, &b);
}

void calculaAeB (intervalo_t **a, intervalo_t *b, int n, int k, intervalo_t *x, intervalo_t *y){
    intervalo_t *somas, potencia;
    somas = malloc ((2*n - 1) * sizeof (intervalo_t));
    for (int i = 0; i < n; i++){
        somas[i].inicio = 0;
        somas[i].fim = 0;
        b[i].inicio = 0;
        b[i].fim = 0;
    }
    for (int i = n; i < 2*n - 1; i++){
        somas[i].inicio = 0;
        somas[i].fim = 0;
    }
    for (long long int i = 0; i < k-k%8; i+=8){
        for (int j = 0; j < n; j++){
            calculaParte(x[i], y[i], j, b[j], somas[j]);
            calculaParte(x[i+1], y[i+2], j, b[j], somas[j]);
            calculaParte(x[i+2], y[i+3], j, b[j], somas[j]);
            calculaParte(x[i+3], y[i+4], j, b[j], somas[j]);
            calculaParte(x[i+4], y[i+5], j, b[j], somas[j]);
            calculaParte(x[i+5], y[i+6], j, b[j], somas[j]);
            calculaParte(x[i+6], y[i+7], j, b[j], somas[j]);
            calculaParte(x[i+7], y[i+8], j, b[j], somas[j]);
        }
        for (int j = n; j < 2*n - 1; j++){
            potenciaIntervalo (x[i], j, &potencia);
            adicionaIntervalo (somas[j], potencia, &somas[j]);
            potenciaIntervalo (x[i+1], j, &potencia);
            adicionaIntervalo (somas[j], potencia, &somas[j]);
            potenciaIntervalo (x[i+2], j, &potencia);
            adicionaIntervalo (somas[j], potencia, &somas[j]);
            potenciaIntervalo (x[i+3], j, &potencia);
            adicionaIntervalo (somas[j], potencia, &somas[j]);
            potenciaIntervalo (x[i+4], j, &potencia);
            adicionaIntervalo (somas[j], potencia, &somas[j]);
            potenciaIntervalo (x[i+5], j, &potencia);
            adicionaIntervalo (somas[j], potencia, &somas[j]);
            potenciaIntervalo (x[i+6], j, &potencia);
            adicionaIntervalo (somas[j], potencia, &somas[j]);
            potenciaIntervalo (x[i+7], j, &potencia);
            adicionaIntervalo (somas[j], potencia, &somas[j]);
        }
    }
    for (long long int i = k-k%8; i < k; i++){
        for (int j = 0; j < n; j++){
            calculaParte(x[i], y[i], j, b[j], somas[j]);
        }
        for (int j = n; j < 2*n - 1; j++){
            potenciaIntervalo (x[i], j, &potencia);
            adicionaIntervalo (somas[j], potencia, &somas[j]);
        }
    }
    //Realiza as atribuições dos somatórios para a matriz A, evitando cálculos repetidos
    for (int i = 0; i < n - n%4; i+=4){ //loop unroll
        for (int j = 0; j < n; j++){
            a[i][j].inicio = somas[i+j].inicio;
            a[i][j].fim = somas[i+j].fim;
            a[(i+1)][j].inicio = somas[i+1+j].inicio;
            a[(i+1)][j].fim = somas[i+1+j].fim;
            a[(i+2)][j].inicio = somas[i+2+j].inicio;
            a[(i+2)][j].fim = somas[i+2+j].fim;
            a[(i+3)][j].inicio = somas[i+3+j].inicio;
            a[(i+3)][j].fim = somas[i+3+j].fim;
        }
    }
    for (int i = n - n%4; i < n; i++){
        for (int j = 0; j < n; j++){
            a[i][j].inicio = somas[i+j].inicio;
            a[i][j].fim = somas[i+j].fim;
        }
    }
    somas = liberaVetor (somas);
}