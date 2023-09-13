#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <fenv.h>
#include "interval.h"

/*Soma os limites inferiores dos intervalos para dar o limite inferior do resultado e os limites superiores para dar o superior*/
void adicionaIntervalo (Float_t intervalo1[2], Float_t intervalo2[2], Float_t resultado[2]){
    fesetround (FE_DOWNWARD);
    resultado[0].f = intervalo1[0].f + intervalo2[0].f;
    fesetround (FE_UPWARD);
    resultado[1].f = intervalo1[1].f + intervalo2[1].f;
    printf ("[%1.8e, %1.8e]\n", resultado[0].f, resultado[1].f);
}

/*Subtrai o maior numero do intervalo 2 do menor do intervalo 1 para dar o menor resultado e subtrai o menor do intervalo 2 do maior 
do intervalo 1 para dar o maior resultado*/
void subtraiIntervalo (Float_t intervalo1[2], Float_t intervalo2[2], Float_t resultado[2]){
    fesetround (FE_DOWNWARD);
    resultado[0].f = intervalo1[0].f - intervalo2[1].f;
    fesetround (FE_UPWARD);
    resultado[1].f = intervalo1[1].f - intervalo2[0].f;
    printf ("[%1.8e, %1.8e]\n", resultado[0].f, resultado[1].f);
}

/*Realiza todas as multiplicações possíveis, selecionando o menor e o maior resultados obtidos para o intervalo*/
void multiplicaIntervalo (Float_t intervalo1[2], Float_t intervalo2[2], Float_t resultado[2]){
    fesetround (FE_DOWNWARD);
    float a = intervalo1[0].f * intervalo2[0].f;
    float b = intervalo1[0].f * intervalo2[1].f;
    float c = intervalo1[1].f * intervalo2[0].f;
    float d = intervalo1[1].f * intervalo2[1].f;
    resultado[0].f = fminf (fminf (a, b), fminf (c, d));
    fesetround (FE_UPWARD);
    a = intervalo1[0].f * intervalo2[0].f;
    b = intervalo1[0].f * intervalo2[1].f;
    c = intervalo1[1].f * intervalo2[0].f;
    d = intervalo1[1].f * intervalo2[1].f;
    resultado[1].f = fmaxf (fmaxf (a, b), fmaxf(c, d));
    printf ("[%1.8e, %1.8e]\n", resultado[0].f, resultado[1].f);
}

/*Mesma ideia da multiplicaçao. Caso 0 pertença ao intervalo 2, o resultado é um intervalo de -infinito a +infinito.*/
void divideIntervalo (Float_t intervalo1[2], Float_t intervalo2[2], Float_t resultado[2]){
    if(intervalo2[0].f <= 0 && intervalo2[1].f >= 0){
        resultado[0].f = -INFINITY;
        resultado[1].f = INFINITY;
        printf ("[%1.8e, %1.8e]\n", resultado[0].f, resultado[1].f);
        return;
    }

    fesetround (FE_DOWNWARD);
    float a = intervalo1[0].f / intervalo2[0].f;
    float b = intervalo1[0].f / intervalo2[1].f;
    float c = intervalo1[1].f / intervalo2[0].f;
    float d = intervalo1[1].f / intervalo2[1].f;
    resultado[0].f = fminf (fminf (a, b), fminf (c, d));
    fesetround (FE_UPWARD);
    a = intervalo1[0].f / intervalo2[0].f;
    b = intervalo1[0].f / intervalo2[1].f;
    c = intervalo1[1].f / intervalo2[0].f;
    d = intervalo1[1].f / intervalo2[1].f;
    resultado[1].f = fmaxf (fmaxf (a, b), fmaxf(c, d));
    printf ("[%1.8e, %1.8e]\n", resultado[0].f, resultado[1].f);
}

/*Calcula o intervalo que inclui o valor passado como parametro*/
void calculaIntervalo (Float_t valor, Float_t intervalo[2]){
    intervalo[0].f = valor.f;
    intervalo[1].f = nextafterf (valor.f, FLT_MAX);
}

/*Calcula o erro absoluto.*/
void calculaErroAbsoluto (Float_t a, Float_t b){
    printf("EA: %1.8e ", b.f-a.f);
}

/*Calcula o erro relativo*/
void calculaErroRelativo (Float_t a, Float_t b){
    printf("ER: %1.8e ", (b.f-a.f)/a.f);
}

/*Calcula ULPS entre dois floats. Caso os números tenham sinais diferentes, calcula a quantidade de ULPs representáveis
entre eles e 0 e depois soma.*/
void calculaULPs(Float_t A, Float_t B){
    if (A.parts.sign != B.parts.sign){
        A.parts.sign = 0;
        printf("ULPs: %d\n", abs(A.i) + abs(B.i) - 1);
    } else{
        printf("ULPs: %d\n", abs(A.i - B.i) - 1);
    }
}