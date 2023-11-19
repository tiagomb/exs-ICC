// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "sistemas.h"
#include "utils.h"
#include "interval.h"

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

/*Recebe como parâmetros a matriz de intervalos, o vetor de intervalos e o tamanho do sistema.
Realiza a retrosubstituição e retorna o vetor solução*/
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

/*Recebe como parâmetros os coeficientes obtidos após a resolução do sistema linear, os pontos x e f(x), a quantidade de pontos e o tamanho do polinômio.
Calcula o resíduo na forma r(i) = f(x(i)) - p(x(i)) e imprime na tela*/
void calculaResiduo (intervalo_t *coef, intervalo_t *x, intervalo_t *y, long long int pontos, int tam){
    intervalo_t *r, aux, potencia;
    r = malloc (pontos * sizeof (intervalo_t ));
    for (long long int i = 0; i < pontos; i++){ //loop unroll
        r[i].inicio = y[i].inicio;
        r[i].fim = y[i].fim;
        for (int j = 0; j < tam; j++){ //acabar com esse loop (tam vai ser sempre o mesmo)
            potencia.inicio = x[i].inicio;
            potencia.fim = x[i].fim;
            potenciaIntervalo (x[i], j, &potencia);
            multiplicaIntervalo (coef[j], potencia, &aux);
            subtraiIntervalo (r[i], aux, &r[i]);
        }
        //printf ("[%1.16e, %1.16e] ", r[i].inicio, r[i].fim);
    }
    //printf ("\n");
    free (r);
}

/*Recebe como parâmetros a matriz e o vetor que representam o sistema linear, e um inteiro indicando seu tamanho.
Imprime a matriz para fins de teste*/
void imprimeMatriz (intervalo_t **a, intervalo_t *b, int tam){ //irrelevante, so é usada para teste
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            printf ("[%1.16e, %1.16e] ", a[i][j].inicio, a[i][j].fim);
        }
        printf ("[%1.16e, %1.16e]\n ", b[i].inicio, b[i].fim);
    }
}

/*Recebe como paramêtros os expoentes dos elementos a serem multiplicados, o vetor de pontos x, a quantidade de pontos k e
um intervalo onde será armazenado o somatório. A função calcula o somatório presente no Método dos Mínimos Quadrados*/
void somatorio (int expoenteCima, int expoenteBaixo, intervalo_t *x, long long int k, intervalo_t *soma){
    intervalo_t potencia1, potencia2, mult;
    soma->inicio = soma->fim = 0;
    for (long long int i = 0; i < k; i++){ 
        potenciaIntervalo (x[i], expoenteCima, &potencia1);
        potenciaIntervalo (x[i], expoenteBaixo, &potencia2);
        multiplicaIntervalo (potencia1, potencia2, &mult);
        adicionaIntervalo (*soma, mult, soma);
    }
}

void calculaA (intervalo_t **a, int n, long long int k, intervalo_t *x){
    intervalo_t *somas;
    int i;
    somas = malloc ((2*n - 1) * sizeof (intervalo_t));
     //Calcula os somatórios necessários para a matriz A
    for (i = 0; i < n-1; i++){
        somatorio(i, 0, x, k, &somas[i]);
    }
    for (int j = 0; j < n; j++){
        somatorio(i, j, x, k, &somas[i+j]);
    }
    //Realiza as atribuições dos somatórios para a matriz A, evitando cálculos repetidos
    for (int i = 0; i < n; i++){ 
        for (int j = 0; j < n; j++){
            a[i][j].inicio = somas[i+j].inicio;
            a[i][j].fim = somas[i+j].fim;
        }
    }
    somas = liberaVetor (somas);
}

/*Recebe como parâmetros o vetor de pontos x, o vetor de pontos y, a quantidade de pontos k, o tamanho do polinômio n 
e um vetor de intervalos onde será armazenado o lado direito do sistema linear. Realiza os cálculos necessários conforme
o Método dos Mínimos Quadrados*/
void calculaB (intervalo_t *b, int n, long long int k, intervalo_t *y, intervalo_t *x){
    intervalo_t potencia, mult;
    for (int i = 0; i < n; i++){ 
        b[i].inicio = b[i].fim = 0;
        for (long long int j = 0; j < k; j++){
            potenciaIntervalo (x[j], i, &potencia);
            multiplicaIntervalo (potencia, y[j], &mult);
            adicionaIntervalo (b[i], mult, &b[i]);
        }
    }
    
}
