// Matheus Sebastian Alencar de Carvalho - GRr->fim0220065
// Tiago Mendes Bottamedi - GRr->fim0220068

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <fenv.h>
#include <float.h>
#include "sistemasOtim.h"
#include "utilsOtim.h"

/*Recebe como parâmetro a matriz e o vetor que representam o sistema linear, e dois inteiros indicando a linha
atual e a linha do pivô para que possam ser trocadas, tanto na matriz quando no vetor*/
void trocaLinhas (intervaloA_t * restrict a, intervaloA_t * restrict b, int i, int pivo){
    intervaloA_t *aux;
    aux = alocaVetor (5);
    memcpy (aux->inicio, &a->inicio[i*5], 5 * sizeof(double));
    memcpy (aux->fim, &a->fim[i*5], 5 * sizeof(double));
    memcpy (&a->inicio[i*5], &a->inicio[pivo*5], 5 * sizeof(double));
    memcpy (&a->fim[i*5], &a->fim[pivo*5], 5 * sizeof(double));
    memcpy (&a->inicio[pivo*5], aux->inicio, 5 * sizeof(double));
    memcpy (&a->fim[pivo*5], aux->fim, 5 * sizeof(double));
    double aux1, aux2;
    aux1 = b->inicio[i];
    aux2 = b->fim[i];
    b->inicio[i] = b->inicio[pivo];
    b->inicio[pivo] = aux1;
    b->fim[i] = b->fim[pivo];
    b->fim[pivo] = aux2;
    aux = liberaVetor (aux);
}

/*Recebe como parâmetro a matriz que representa o lado esquerdo do sistema linear, e dois inteiros representando
a linha atual e o tamanho da matriz. Retorna a linha do pivôs*/
int encontraPivo (intervaloA_t * restrict a, int  i, int tam){
    int pivo = i;
    for (int j = i + 1; j < tam; j++){
        if (fabs(a->inicio[j*tam+i]) > fabs(a->inicio[pivo*tam+i])){
            pivo = j;
        }
    }
    return pivo;
}

/*Recebe como paramêtros a matriz e o vetor que representam o sistema linear e o tamanho desse sistema.
Realiza a Eliminação de Gauss com multiplicador e pivoteamento parcial*/
void gaussComMult (intervaloA_t * restrict a, intervaloA_t * restrict b, int tam){
    intervalo_t m, mult;
    for (int i = 0; i < tam; i++){ //modificar loops (talvez loop unroll para 4)
        int pivo = encontraPivo (a, i, tam);
        if (pivo != i){
            trocaLinhas (a, b, i, pivo);
        }
        for (int j = i + 1; j < tam; j++){
            DIVIDE_INTERVALO(a->inicio[j*tam+i], a->fim[j*tam+i], a->inicio[i*tam+i], a->fim[i*tam+i], &m.inicio, &m.fim);
            a->inicio[j*tam+i] = a->fim[j*tam+i] =  0;
            for (int k = i+1; k < tam; k++){
                MULTIPLICA_INTERVALO(m.inicio, m.fim, a->inicio[i*tam+k], a->fim[i*tam+k], &mult.inicio, &mult.fim);
                SUBTRAI_INTERVALO(a->inicio[j*tam+k], a->fim[j*tam+k], mult.inicio, mult.fim, &a->inicio[j*tam+k], &a->fim[j*tam+k]);
            }
            MULTIPLICA_INTERVALO(m.inicio, m.fim, b->inicio[i], b->fim[i], &mult.inicio, &mult.fim);
            SUBTRAI_INTERVALO(b->inicio[j], b->fim[j], mult.inicio, mult.fim, &b->inicio[j], &b->fim[j]);
        }
    }
}

/*Recebe como parâmetros a matriz de intervalos, o vetor de intervalos e o tamanho do sistema.
Realiza a retrosubstituição e retorna o vetor solução*/
void retroSub (intervaloA_t * restrict a, intervaloA_t * restrict b, intervaloA_t * restrict x, int tam){
    intervalo_t aux;
    aux.inicio = aux.fim = 0;
    for (int i = tam - 1; i >= 0; i--){ //alterar loops
        x->inicio[i] = b->inicio[i];
        x->fim[i] = b->fim[i];
        for (int j = i + 1; j < tam; j++){
            MULTIPLICA_INTERVALO(a->inicio[i*tam+j], a->fim[i*tam+j], x->inicio[j], x->fim[j], &aux.inicio, &aux.fim);
            SUBTRAI_INTERVALO(x->inicio[i], x->fim[i], aux.inicio, aux.fim, &x->inicio[i], &x->fim[i]);
        }
        DIVIDE_INTERVALO(x->inicio[i], x->fim[i], a->inicio[i*tam+i], a->fim[i*tam+i], &aux.inicio, &aux.fim);
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
            p->inicio[0] = p->fim[0] = 1;
            p->inicio[1] = p->fim[1] = 1;
            p->inicio[2] = p->fim[2] = 1;
            p->inicio[3] = p->fim[3] = 1;
            for (int j = 0; j < tam; j++){
                fesetround(FE_DOWNWARD);
                r->inicio[i] -= p->fim[0] * coef->fim[j];
                r->inicio[i+1] -= p->fim[1] * coef->fim[j];
                r->inicio[i+2] -= p->fim[2] * coef->fim[j];
                r->inicio[i+3] -= p->fim[3] * coef->fim[j];
                fesetround(FE_UPWARD);
                r->fim[i] -= p->inicio[0] * coef->inicio[j];
                r->fim[i+1] -= p->inicio[1] * coef->inicio[j];
                r->fim[i+2] -= p->inicio[2] * coef->inicio[j];
                r->fim[i+3] -= p->inicio[3] * coef->inicio[j];
                fesetround(FE_DOWNWARD);
                p->inicio[0] *= x->inicio[i];
                p->inicio[1] *= x->inicio[i+1];
                p->inicio[2] *= x->inicio[i+2];
                p->inicio[3] *= x->inicio[i+3];
                fesetround(FE_UPWARD);
                p->fim[0] *= x->fim[i];
                p->fim[1] *= x->fim[i+1];
                p->fim[2] *= x->fim[i+2];
                p->fim[3] *= x->fim[i+3];
            }
        }
    }
    
    for (long long int i = pontos-pontos%BK; i < pontos; i++){
        r->inicio[i] = y->inicio[i];
        r->fim[i] = y->fim[i];
        p->inicio[0] = p->fim[0] = 1;
        for (int j = 0; j < tam; j++){
            fesetround(FE_DOWNWARD);
            r->inicio[i] -= p->fim[0] * coef->fim[j];
            fesetround(FE_UPWARD);
            r->fim[i] -= p->inicio[0] * coef->inicio[j];
            fesetround(FE_DOWNWARD);
            p->inicio[0] *= x->inicio[i];
            fesetround(FE_UPWARD);
            p->fim[0] *= x->fim[i];
        }
    }
    p = liberaVetor(p);
}

/*Recebe como parâmetros a matriz e o vetor que representam o sistema linear, e um inteiro indicando seu tamanho.
Imprime a matriz para fins de teste*/
void imprimeMatriz (intervaloA_t * restrict a, intervaloA_t * restrict b, int tam){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            printf ("[%1.16e, %1.16e] ", a->inicio[i*tam+j], a->fim[i*tam+j]);
        }
        printf ("[%1.16e, %1.16e]\n ", b->inicio[i], b->fim[i]);
    }
}

void calculaAeB (intervaloA_t * restrict a, intervaloA_t * restrict b, int n, int k, intervaloA_t * restrict x, intervaloA_t * restrict y){
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
            POTENCIA_INTERVALO (x->inicio[i], x->fim[i], n, &p->inicio[4], &p->fim[4]);
            POTENCIA_INTERVALO (x->inicio[i+1], x->fim[i+1], n, &p->inicio[5], &p->fim[5]);
            POTENCIA_INTERVALO (x->inicio[i+2], x->fim[i+2], n, &p->inicio[6], &p->fim[6]);
            POTENCIA_INTERVALO (x->inicio[i+3], x->fim[i+3], n, &p->inicio[7], &p->fim[7]);
            for (int j = 0; j < n; j++){
                fesetround(FE_DOWNWARD);
                s->inicio[j] += p->inicio[0];
                s->inicio[j] += p->inicio[1];
                s->inicio[j] += p->inicio[2];
                s->inicio[j] += p->inicio[3];
                s->inicio[j+n] += p->inicio[4];
                s->inicio[j+n] += p->inicio[5];
                s->inicio[j+n] += p->inicio[6];
                s->inicio[j+n] += p->inicio[7];
                fesetround(FE_UPWARD);
                s->fim[j] += p->fim[0];
                s->fim[j] += p->fim[1];
                s->fim[j] += p->fim[2];
                s->fim[j] += p->fim[3];
                s->fim[j+n] += p->fim[4];
                s->fim[j+n] += p->fim[5];
                s->fim[j+n] += p->fim[6];
                s->fim[j+n] += p->fim[7];
                fesetround(FE_DOWNWARD);
                b->inicio[j] += p->inicio[0] * y->inicio[i];;
                b->inicio[j] += p->inicio[1] * y->inicio[i+1];
                b->inicio[j] += p->inicio[2] * y->inicio[i+2];
                b->inicio[j] += p->inicio[3] * y->inicio[i+3];
                fesetround(FE_UPWARD);
                b->fim[j] += p->fim[0] * y->fim[i];
                b->fim[j] += p->fim[1] * y->fim[i+1];
                b->fim[j] += p->fim[2] * y->fim[i+2];
                b->fim[j] += p->fim[3] * y->fim[i+3];
                fesetround(FE_DOWNWARD);
                p->inicio[0] *= x->inicio[i];
                p->inicio[1] *= x->inicio[i+1];
                p->inicio[2] *= x->inicio[i+2];
                p->inicio[3] *= x->inicio[i+3];
                p->inicio[4] *= x->inicio[i];
                p->inicio[5] *= x->inicio[i+1];
                p->inicio[6] *= x->inicio[i+2];
                p->inicio[7] *= x->inicio[i+3];
                fesetround(FE_UPWARD);
                p->fim[0] *= x->fim[i];
                p->fim[1] *= x->fim[i+1];
                p->fim[2] *= x->fim[i+2];
                p->fim[3] *= x->fim[i+3];
                p->fim[4] *= x->fim[i];
                p->fim[5] *= x->fim[i+1];
                p->fim[6] *= x->fim[i+2];
                p->fim[7] *= x->fim[i+3];
            }
        }
    }
    
    for (long long int i = k-k%8; i < k; i++){
        p->inicio[0] = p->fim[0] = 1;
        POTENCIA_INTERVALO (x->inicio[i], x->fim[i], n, &p->inicio[1], &p->fim[1]);
        for (int j = 0; j < n; j++){
            fesetround(FE_DOWNWARD);
            s->inicio[j] += p->inicio[0];
            s->inicio[j+n] += p->inicio[1];
            fesetround(FE_UPWARD);
            s->fim[j] += p->fim[0];
            s->fim[j+n] += p->fim[1];
            fesetround(FE_DOWNWARD);
            b->inicio[j] += p->inicio[0] * y->inicio[i];
            fesetround(FE_UPWARD);
            b->fim[j] += p->fim[0] * y->fim[i];
            fesetround(FE_DOWNWARD);
            p->inicio[0] *= x->inicio[i];
            p->inicio[1] *= x->inicio[i];
            fesetround(FE_UPWARD);
            p->fim[0] *= x->fim[i];
            p->fim[1] *= x->fim[i];
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            a->inicio[i*n+j] = s->inicio[i+j];
            a->fim[i*n+j] = s->fim[i+j];
        }
    }
    s = liberaVetor(s);
    p = liberaVetor(p);
}
