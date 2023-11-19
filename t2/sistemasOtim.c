// Matheus Sebastian Alencar de Carvalho - GRr->fim0220065
// Tiago Mendes Bottamedi - GRr->fim0220068

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "sistemasOtim.h"
#include "utilsOtim.h"

/*Recebe como parâmetro a matriz e o vetor que representam o sistema linear, e dois inteiros indicando a linha
atual e a linha do pivô para que possam ser trocadas, tanto na matriz quando no vetor*/
void trocaLinhas (intervalo_t ** restrict a, intervaloA_t * restrict b, int i, int pivo){
    intervalo_t *aux;
    aux = a[i];
    a[i] = a[pivo];
    a[pivo] = aux;
    double aux1, aux2;
    aux1 = b->inicio[i];
    aux2 = b->fim[i];
    b->inicio[i] = b->inicio[pivo];
    b->inicio[pivo] = aux1;
    b->fim[i] = b->fim[pivo];
    b->fim[pivo] = aux2;
}

/*Recebe como parâmetro a matriz que representa o lado esquerdo do sistema linear, e dois inteiros representando
a linha atual e o tamanho da matriz. Retorna a linha do pivôs*/
int encontraPivo (intervalo_t ** restrict a, int  i, int tam){
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
void gaussComMult (intervalo_t ** restrict a, intervaloA_t * restrict b, int tam){
    intervalo_t m, mult;
    for (int i = 0; i < tam; i++){ //modificar loops (talvez loop unroll para 4)
        int pivo = encontraPivo (a, i, tam);
        if (pivo != i){
            trocaLinhas (a, b, i, pivo);
        }
        for (int j = i + 1; j < tam; j++){
            divideIntervalo (a[j][i].inicio, a[j][i].fim, a[i][i].inicio, a[i][i].fim, &m.inicio, &m.fim);
            a[j][i].inicio = a[j][i].fim =  0;
            for (int k = i+1; k < tam; k++){
                multiplicaIntervalo(m.inicio, m.fim, a[i][k].inicio, a[i][k].fim, &mult.inicio, &mult.fim);
                subtraiIntervalo (a[j][k].inicio, a[j][k].fim, mult.inicio, mult.fim, &a[j][k].inicio, &a[j][k].fim);
            }
            multiplicaIntervalo(m.inicio, m.fim, b->inicio[i], b->fim[i], &mult.inicio, &mult.fim);
            subtraiIntervalo (b->inicio[j], b->fim[j], mult.inicio, mult.fim, &b->inicio[j], &b->fim[j]);
        }
    }
}

/*Recebe como parâmetros a matriz de intervalos, o vetor de intervalos e o tamanho do sistema.
Realiza a retrosubstituição e retorna o vetor solução*/
void retroSub (intervalo_t ** restrict a, intervaloA_t * restrict b, intervaloA_t * restrict x, int tam){
    intervalo_t aux;
    aux.inicio = aux.fim = 0;
    for (int i = tam - 1; i >= 0; i--){ //alterar loops
        x->inicio[i] = b->inicio[i];
        x->fim[i] = b->fim[i];
        for (int j = i + 1; j < tam; j++){
            multiplicaIntervalo(a[i][j].inicio, a[i][j].fim, x->inicio[j], x->fim[j], &aux.inicio, &aux.fim);
            subtraiIntervalo (x->inicio[i], x->fim[i], aux.inicio, aux.fim, &x->inicio[i], &x->fim[i]);
        }
        divideIntervalo (x->inicio[i], x->fim[i], a[i][i].inicio, a[i][i].fim, &aux.inicio, &aux.fim);
        x->inicio[i] = aux.inicio;
        x->fim[i] = aux.fim;
    }
}

/*Recebe como parâmetros os coeficientes obtidos após a resolução do sistema linear, os pontos x e f(x), a quantidade de pontos e o tamanho do polinômio.
Calcula o resíduo na forma r(i) = f(x(i)) - p(x(i)) e imprime na tela*/
void calculaResiduo (intervaloA_t * restrict coef, intervaloA_t * restrict x, intervaloA_t * restrict y, long long int pontos, int tam, intervaloA_t * restrict r){
    long long int istart, iend;
    intervaloA_t *p;
    p = alocaVetor(4);
    for (long long int ii = 0; ii < pontos/BK; ii++){
        istart = ii*BK; iend = istart + BK;
        for (long long int i = istart; i < iend; i+=UF){
            r->inicio[i] = y->inicio[i];
            r->fim[i] = y->fim[i];
            r->inicio[i+1] = y->inicio[i+1];
            r->fim[i+1] = y->fim[i+1];
            r->inicio[i+2] = y->inicio[i+2];
            r->fim[i+2] = y->fim[i+2];
            r->inicio[i+3] = y->inicio[i+3];
            r->fim[i+3] = y->fim[i+3];
            for (int j = 0; j < tam; j++){
                potenciaIntervalo (x->inicio[i], x->fim[i], j, &p->inicio[0], &p->fim[0]);
                potenciaIntervalo (x->inicio[i+1], x->fim[i+1], j, &p->inicio[1], &p->fim[1]);
                potenciaIntervalo (x->inicio[i+2], x->fim[i+2], j, &p->inicio[2], &p->fim[2]);
                potenciaIntervalo (x->inicio[i+3], x->fim[i+3], j, &p->inicio[3], &p->fim[3]);
                multiplicaIntervalo(p->inicio[0], p->fim[0], coef->inicio[j], coef->fim[j], &p->inicio[0], &p->fim[0]);
                multiplicaIntervalo(p->inicio[1], p->fim[1], coef->inicio[j], coef->fim[j], &p->inicio[1], &p->fim[1]);
                multiplicaIntervalo(p->inicio[2], p->fim[2], coef->inicio[j], coef->fim[j], &p->inicio[2], &p->fim[2]);
                multiplicaIntervalo(p->inicio[3], p->fim[3], coef->inicio[j], coef->fim[j], &p->inicio[3], &p->fim[3]);
                subtraiIntervalo (r->inicio[i], r->fim[i], p->inicio[0], p->fim[0], &r->inicio[i], &r->fim[i]);
                subtraiIntervalo (r->inicio[i+1], r->fim[i+1], p->inicio[1], p->fim[1], &r->inicio[i+1], &r->fim[i+1]);
                subtraiIntervalo (r->inicio[i+2], r->fim[i+2], p->inicio[2], p->fim[2], &r->inicio[i+2], &r->fim[i+2]);
                subtraiIntervalo (r->inicio[i+3], r->fim[i+3], p->inicio[3], p->fim[3], &r->inicio[i+3], &r->fim[i+3]);
            }
        }
    }
    
    for (long long int i = pontos-pontos%BK; i < pontos; i++){
        r->inicio[i] = y->inicio[i];
        r->fim[i] = y->fim[i];
        for (int j = 0; j < tam; j++){
            potenciaIntervalo (x->inicio[i], x->fim[i], j, &p->inicio[0], &p->fim[0]);
            multiplicaIntervalo(p->inicio[0], p->fim[0], coef->inicio[j], coef->fim[j], &p->inicio[0], &p->fim[0]);
            subtraiIntervalo (r->inicio[i], r->fim[i], p->inicio[0], p->fim[0], &r->inicio[i], &r->fim[i]);
        }
    }
    p = liberaVetor(p);
}

/*Recebe como parâmetros a matriz e o vetor que representam o sistema linear, e um inteiro indicando seu tamanho.
Imprime a matriz para fins de teste*/
void imprimeMatriz (intervalo_t ** restrict a, intervaloA_t * restrict b, int tam){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            printf ("[%1.16e, %1.16e] ", a[i][j].inicio, a[i][j].fim);
        }
        printf ("[%1.16e, %1.16e]\n ", b->inicio[i], b->fim[i]);
    }
}

void calculaAeB (intervalo_t ** restrict a, intervaloA_t * restrict b, int n, int k, intervaloA_t * restrict x, intervaloA_t * restrict y){
    long long int istart, iend;
    intervaloA_t *s, *p;
    s = alocaVetor(2*n);
    p = alocaVetor(8);
    for (int i = 0; i < n; i++){
        s->inicio[i] = 0;
        s->fim[i] = 0;
        b->inicio[i] = 0;
        b->fim[i] = 0;
        s->inicio[i+n] = 0;
        s->fim[i+n] = 0;
    }
    for (long long int ii = 0; ii < k/BK; ii++){
        istart = ii*BK; iend = istart + BK;
        for (long long int i = istart; i < iend; i+=UF){
            p->inicio[0] = p->fim[0] = 1;
            p->inicio[1] = p->fim[1] = 1;
            p->inicio[2] = p->fim[2] = 1;
            p->inicio[3] = p->fim[3] = 1;
            for (int j = 0; j < n; j++){
                potenciaIntervalo (x->inicio[i], x->fim[i], j, &p->inicio[0], &p->fim[0]);
                potenciaIntervalo (x->inicio[i+1], x->fim[i+1], j, &p->inicio[1], &p->fim[1]);
                potenciaIntervalo (x->inicio[i+2], x->fim[i+2], j, &p->inicio[2], &p->fim[2]);
                potenciaIntervalo (x->inicio[i+3], x->fim[i+3], j, &p->inicio[3], &p->fim[3]);
                potenciaIntervalo (x->inicio[i], x->fim[i], j+n, &p->inicio[4], &p->fim[4]);
                potenciaIntervalo (x->inicio[i+1], x->fim[i+1], j+n, &p->inicio[5], &p->fim[5]);
                potenciaIntervalo (x->inicio[i+2], x->fim[i+2], j+n, &p->inicio[6], &p->fim[6]);
                potenciaIntervalo (x->inicio[i+3], x->fim[i+3], j+n, &p->inicio[7], &p->fim[7]);
                adicionaIntervalo(s->inicio[j], s->fim[j], p->inicio[0], p->fim[0], &s->inicio[j], &s->fim[j]);
                adicionaIntervalo(s->inicio[j], s->fim[j], p->inicio[1], p->fim[1], &s->inicio[j], &s->fim[j]);
                adicionaIntervalo(s->inicio[j], s->fim[j], p->inicio[2], p->fim[2], &s->inicio[j], &s->fim[j]);
                adicionaIntervalo(s->inicio[j], s->fim[j], p->inicio[3], p->fim[3], &s->inicio[j], &s->fim[j]);
                adicionaIntervalo(s->inicio[j+n], s->fim[j+n], p->inicio[4], p->fim[4], &s->inicio[j+n], &s->fim[j+n]);
                adicionaIntervalo(s->inicio[j+n], s->fim[j+n], p->inicio[5], p->fim[5], &s->inicio[j+n], &s->fim[j+n]);
                adicionaIntervalo(s->inicio[j+n], s->fim[j+n], p->inicio[6], p->fim[6], &s->inicio[j+n], &s->fim[j+n]);
                adicionaIntervalo(s->inicio[j+n], s->fim[j+n], p->inicio[7], p->fim[7], &s->inicio[j+n], &s->fim[j+n]);
                multiplicaIntervalo(p->inicio[0], p->fim[0], y->inicio[i], y->fim[i], &p->inicio[0], &p->fim[0]);
                multiplicaIntervalo(p->inicio[1], p->fim[1], y->inicio[i+1], y->fim[i+1], &p->inicio[1], &p->fim[1]);
                multiplicaIntervalo(p->inicio[2], p->fim[2], y->inicio[i+2], y->fim[i+2], &p->inicio[2], &p->fim[2]);
                multiplicaIntervalo(p->inicio[3], p->fim[3], y->inicio[i+3], y->fim[i+3], &p->inicio[3], &p->fim[3]);
                adicionaIntervalo (b->inicio[j], b->fim[j], p->inicio[0], p->fim[0], &b->inicio[j], &b->fim[j]);
                adicionaIntervalo (b->inicio[j], b->fim[j], p->inicio[1], p->fim[1], &b->inicio[j], &b->fim[j]);
                adicionaIntervalo (b->inicio[j], b->fim[j], p->inicio[2], p->fim[2], &b->inicio[j], &b->fim[j]);
                adicionaIntervalo (b->inicio[j], b->fim[j], p->inicio[3], p->fim[3], &b->inicio[j], &b->fim[j]);
            }
        }
    }
    
    for (long long int i = k-k%8; i < k; i++){
        for (int j = 0; j < n; j++){
            potenciaIntervalo (x->inicio[i], x->fim[i], j, &p->inicio[0], &p->fim[0]);
            potenciaIntervalo (x->inicio[i], x->fim[i], j+n, &p->inicio[1], &p->fim[1]);
            adicionaIntervalo(s->inicio[j], s->fim[j], p->inicio[0], p->fim[0], &s->inicio[j], &s->fim[j]);
            adicionaIntervalo(s->inicio[j+n], s->fim[j+n], p->inicio[1], p->fim[1], &s->inicio[j+n], &s->fim[j+n]);
            multiplicaIntervalo(p->inicio[0], p->fim[0], y->inicio[i], y->fim[i], &p->inicio[0], &p->fim[0]);
            adicionaIntervalo (b->inicio[j], b->fim[j], p->inicio[0], p->fim[0], &b->inicio[j], &b->fim[j]);
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            a[i][j].inicio = s->inicio[i+j];
            a[i][j].fim = s->fim[i+j];
        }
    }
    s = liberaVetor(s);
    p = liberaVetor(p);
}
