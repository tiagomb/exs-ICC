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
void trocaLinhas (intervalo_t *a, intervalo_t *b, int i, int pivo){
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
int encontraPivo (intervalo_t *a, int i, int tam){
    int pivo = i;
    for (int j = i + 1; j < tam; j++){
        if (fabs(a[j*tam+i].inicio) > fabs(a[pivo*tam+i].inicio)){
            pivo = j;
        }
    }
    return pivo;
}

/*Recebe como paramêtros a matriz e o vetor que representam o sistema linear e o tamanho desse sistema.
Realiza a Eliminação de Gauss com multiplicador e pivoteamento parcial*/
void gaussComMult (intervalo_t *a, intervalo_t *b, int tam){
    intervalo_t m, mult;
    for (int i = 0; i < tam; i++){ //modificar loops (talvez loop unroll para 4)
        int pivo = encontraPivo (a, i, tam);
        if (pivo != i)
            trocaLinhas (a, b, i, pivo);
        for (int j = i + 1; j < tam; j++){
            divideIntervalo (a[j*tam+i], a[i*tam+i], &m);
            a[j*tam+i].inicio = a[j*tam+i].fim =  0;
            for (int k = i+1; k < tam; k++){
                multiplicaIntervalo (m, a[i*tam+k], &mult);
                subtraiIntervalo (a[j*tam+k], mult , &a[j*tam+k]);
            }
            multiplicaIntervalo (m, b[i], &mult);
            subtraiIntervalo (b[j], mult, &b[j]);
        }
    }
}

/*Recebe como parâmetros a matriz de intervalos, o vetor de intervalos e o tamanho do sistema.
Realiza a retrosubstituição e retorna o vetor solução*/
void retroSub (intervalo_t *a, intervalo_t *b, intervalo_t *x, int tam){
    intervalo_t aux;
    for (int i = tam - 1; i >= 0; i--){ //alterar loops
        x[i].inicio = b[i].inicio;
        x[i].fim = b[i].fim;
        for (int j = i + 1; j < tam; j++){
            multiplicaIntervalo (a[i*tam+j], x[j], &aux);
            subtraiIntervalo (x[i], aux, &x[i]);
        }
        divideIntervalo (x[i], a[i*tam+i], &aux);
        x[i].inicio = aux.inicio;
        x[i].fim = aux.fim;
    }
}

/*Recebe como parâmetros os coeficientes obtidos após a resolução do sistema linear, os pontos x e f(x), a quantidade de pontos e o tamanho do polinômio.
Calcula o resíduo na forma r(i) = f(x(i)) - p(x(i)) e imprime na tela*/
void calculaResiduo (intervalo_t *coef, intervalo_t *x, intervalo_t *y, long long int pontos, int tam){
    intervalo_t *r, aux, potencia;
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
            potencia.inicio = x[i].inicio;
            potencia.fim = x[i].fim;
            potenciaIntervalo (x[i], j, &potencia);
            multiplicaIntervalo (coef[j], potencia, &aux);
            subtraiIntervalo (r[i], aux, &r[i]);
            potencia.inicio = x[i+1].inicio;
            potencia.fim = x[i+1].fim;
            potenciaIntervalo (x[i+1], j, &potencia);
            multiplicaIntervalo (coef[j], potencia, &aux);
            subtraiIntervalo (r[i+1], aux, &r[i+1]);
            potencia.inicio = x[i+2].inicio;
            potencia.fim = x[i+2].fim;
            potenciaIntervalo (x[i+2], j, &potencia);
            multiplicaIntervalo (coef[j], potencia, &aux);
            subtraiIntervalo (r[i+2], aux, &r[i+2]);
            potencia.inicio = x[i+3].inicio;
            potencia.fim = x[i+3].fim;
            potenciaIntervalo (x[i+3], j, &potencia);
            multiplicaIntervalo (coef[j], potencia, &aux);
            subtraiIntervalo (r[i+3], aux, &r[i+3]);
            potencia.inicio = x[i+4].inicio;
            potencia.fim = x[i+4].fim;
            potenciaIntervalo (x[i+4], j, &potencia);
            multiplicaIntervalo (coef[j], potencia, &aux);
            subtraiIntervalo (r[i+4], aux, &r[i+4]);
            potencia.inicio = x[i+5].inicio;
            potencia.fim = x[i+5].fim;
            potenciaIntervalo (x[i+5], j, &potencia);
            multiplicaIntervalo (coef[j], potencia, &aux);
            subtraiIntervalo (r[i+5], aux, &r[i+5]);
            potencia.inicio = x[i+6].inicio;
            potencia.fim = x[i+6].fim;
            potenciaIntervalo (x[i+6], j, &potencia);
            multiplicaIntervalo (coef[j], potencia, &aux);
            subtraiIntervalo (r[i+6], aux, &r[i+6]);
            potencia.inicio = x[i+7].inicio;
            potencia.fim = x[i+7].fim;
            potenciaIntervalo (x[i+7], j, &potencia);
            multiplicaIntervalo (coef[j], potencia, &aux);
            subtraiIntervalo (r[i+7], aux, &r[i+7]);
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

/*Recebe como parâmetros a matriz e o vetor que representam o sistema linear, e um inteiro indicando seu tamanho.
Imprime a matriz para fins de teste*/
void imprimeMatriz (intervalo_t *a, intervalo_t *b, int tam){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            printf ("[%1.16e, %1.16e] ", a[i*tam+j].inicio, a[i*tam+j].fim);
        }
        printf ("[%1.16e, %1.16e]\n ", b[i].inicio, b[i].fim);
    }
}

/*Recebe como paramêtros os expoentes dos elementos a serem multiplicados, o vetor de pontos x, a quantidade de pontos k e
um intervalo onde será armazenado o somatório. A função calcula o somatório presente no Método dos Mínimos Quadrados*/
void somatorio (int expoente, intervalo_t *x, long long int k, intervalo_t *soma){
    intervalo_t potencia, mult;
    soma->inicio = soma->fim = 0;
    for (long long int i = 0; i < k-k%8; i+=8){ // loop unroll e calcular as duas potencias de uma vez so
        potenciaIntervalo (x[i], expoente, &potencia);
        adicionaIntervalo (*soma, mult, soma);
        potenciaIntervalo (x[i+1], expoente, &potencia);
        adicionaIntervalo (*soma, mult, soma);
        potenciaIntervalo (x[i+2], expoente, &potencia);
        adicionaIntervalo (*soma, mult, soma);
        potenciaIntervalo (x[i+3], expoente, &potencia);
        adicionaIntervalo (*soma, mult, soma);
        potenciaIntervalo (x[i+4], expoente, &potencia);
        adicionaIntervalo (*soma, mult, soma);
        potenciaIntervalo (x[i+5], expoente, &potencia);
        adicionaIntervalo (*soma, mult, soma);
        potenciaIntervalo (x[i+6], expoente, &potencia);
        adicionaIntervalo (*soma, mult, soma);
        potenciaIntervalo (x[i+7], expoente, &potencia);
        adicionaIntervalo (*soma, mult, soma);
    }
    for (long long int i = k-k%8; i < k; i++){
        potenciaIntervalo (x[i], expoente, &potencia);
        adicionaIntervalo (*soma, mult, soma);
    }
}

void calculaA (intervalo_t *a, int n, int k, intervalo_t *x){
    intervalo_t *somas;
    somas = malloc ((2*n - 1) * sizeof (intervalo_t));
     //Calcula os somatórios necessários para a matriz A
    for (int i = 0; i < n - n%4; i+=4){
        somatorio(i, x, k, &somas[i]);
        somatorio(i+1, x, k, &somas[i+1]);
        somatorio(i+2, x, k, &somas[i+2]);
        somatorio(i+3, x, k, &somas[i+3]);
    }
    for (int i = n - n%4; i < n; i++){
        somatorio(i, x, k, &somas[i]);
    }
    //Realiza as atribuições dos somatórios para a matriz A, evitando cálculos repetidos
    for (int i = 0; i < n - n%4; i+=4){ //loop unroll
        for (int j = 0; j < n; j++){
            a[i*tam+j].inicio = somas[i+j].inicio;
            a[i*tam+j].fim = somas[i+j].fim;
            a[(i+1)*tam+j].inicio = somas[i+1+j].inicio;
            a[(i+1)*tam+j].fim = somas[i+1+j].fim;
            a[(i+2)*tam+j].inicio = somas[i+2+j].inicio;
            a[(i+2)*tam+j].fim = somas[i+2+j].fim;
            a[(i+3)*tam+j].inicio = somas[i+3+j].inicio;
            a[(i+3)*tam+j].fim = somas[i+3+j].fim;
        }
    }
    for (int i = n - n%4; i < n; i++){
        for (int j = 0; j < n; j++){
            a[i*tam+j].inicio = somas[i+j].inicio;
            a[i*tam+j].fim = somas[i+j].fim;
        }
    }
    somas = liberaVetor (somas);
}

/*Recebe como parâmetros o vetor de pontos x, o vetor de pontos y, a quantidade de pontos k, o tamanho do polinômio n 
e um vetor de intervalos onde será armazenado o lado direito do sistema linear. Realiza os cálculos necessários conforme
o Método dos Mínimos Quadrados*/
void calculaB (intervalo_t *b, int n, long long int k, intervalo_t *y, intervalo_t *x){
    intervalo_t potencia, mult;
    for (int j = 0; j < n; j++)
        b[j].inicio = b[j].fim = 0;
    for (long long int i = 0; i < k-k%8; i+=8){
        for (int j = 0; j < n; j++){
            potenciaIntervalo (x[i], j, &potencia);
            multiplicaIntervalo (potencia, y[i], &mult);
            adicionaIntervalo (b[j], mult, &b[j]);
            potenciaIntervalo (x[i+1], j, &potencia);
            multiplicaIntervalo (potencia, y[i+1], &mult);
            adicionaIntervalo (b[j], mult, &b[j]);
            potenciaIntervalo (x[i+2], j, &potencia);
            multiplicaIntervalo (potencia, y[i+2], &mult);
            adicionaIntervalo (b[j], mult, &b[j]);
            potenciaIntervalo (x[i+3], j, &potencia);
            multiplicaIntervalo (potencia, y[i+3], &mult);
            adicionaIntervalo (b[j], mult, &b[j]);
            potenciaIntervalo (x[i+4], j, &potencia);
            multiplicaIntervalo (potencia, y[i+4], &mult);
            adicionaIntervalo (b[j], mult, &b[j]);
            potenciaIntervalo (x[i+5], j, &potencia);
            multiplicaIntervalo (potencia, y[i+5], &mult);
            adicionaIntervalo (b[j], mult, &b[j]);
            potenciaIntervalo (x[i+6], j, &potencia);
            multiplicaIntervalo (potencia, y[i+6], &mult);
            adicionaIntervalo (b[j], mult, &b[j]);
            potenciaIntervalo (x[i+7], j, &potencia);
            multiplicaIntervalo (potencia, y[i+7], &mult);
            adicionaIntervalo (b[j], mult, &b[j]);
        }
    }
    for (long long int i = k-k%8; i < k; i++){
        for (int j = 0; j < n; j++){
            potenciaIntervalo (x[i], j, &potencia);
            multiplicaIntervalo (potencia, y[i], &mult);
            adicionaIntervalo (b[j], mult, &b[j]);
        }
    }  
}