#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <fenv.h>
#include "interval.h"

/*Soma os limites inferiores dos intervalos para dar o limite inferior do resultado e os limites superiores para dar o superior*/
void adicionaIntervalo (double intervalo1[2], double intervalo2[2], double resultado[2]){
    fesetround (FE_DOWNWARD);
    resultado[0] = intervalo1[0] + intervalo2[0];
    fesetround (FE_UPWARD);
    resultado[1] = intervalo1[1] + intervalo2[1];
}

/*Subtrai o maior numero do intervalo 2 do menor do intervalo 1 para dar o menor resultado e subtrai o menor do intervalo 2 do maior 
do intervalo 1 para dar o maior resultado*/
void subtraiIntervalo (double intervalo1[2], double intervalo2[2], double resultado[2]){
    fesetround (FE_DOWNWARD);
    resultado[0] = intervalo1[0] - intervalo2[1];
    fesetround (FE_UPWARD);
    resultado[1] = intervalo1[1] - intervalo2[0];
}

/*Realiza todas as multiplicações possíveis, selecionando o menor e o maior resultados obtidos para o intervalo*/
void multiplicaIntervalo (double intervalo1[2], double intervalo2[2], double resultado[2]){
    fesetround (FE_DOWNWARD);
    double a = intervalo1[0] * intervalo2[0];
    double b = intervalo1[0] * intervalo2[1];
    double c = intervalo1[1] * intervalo2[0];
    double d = intervalo1[1] * intervalo2[1];
    resultado[0] = fmin (fmin (a, b), fmin (c, d));
    fesetround (FE_UPWARD);
    a = intervalo1[0] * intervalo2[0];
    b = intervalo1[0] * intervalo2[1];
    c = intervalo1[1] * intervalo2[0];
    d = intervalo1[1] * intervalo2[1];
    resultado[1] = fmax (fmax (a, b), fmax(c, d));
}

/*Mesma ideia da multiplicaçao. Caso 0 pertença ao intervalo 2, o resultado é um intervalo de -infinito a +infinito.*/
void divideIntervalo (double intervalo1[2], double intervalo2[2], double resultado[2]){
    if(intervalo2[0] <= 0 && intervalo2[1] >= 0){
        resultado[0] = -INFINITY;
        resultado[1] = INFINITY;
        return;
    }

    fesetround (FE_DOWNWARD);
    double a = intervalo1[0] / intervalo2[0];
    double b = intervalo1[0] / intervalo2[1];
    double c = intervalo1[1] / intervalo2[0];
    double d = intervalo1[1] / intervalo2[1];
    resultado[0] = fmin (fmin (a, b), fmin (c, d));
    fesetround (FE_UPWARD);
    a = intervalo1[0] / intervalo2[0];
    b = intervalo1[0] / intervalo2[1];
    c = intervalo1[1] / intervalo2[0];
    d = intervalo1[1] / intervalo2[1];
    resultado[1] = fmax (fmax (a, b), fmax(c, d));
}

void potenciaIntervalo (double intervalo[2], int expoente, double resultado[2]){
    if (expoente == 0){
        resultado[0] = 1;
        resultado[1] = 1;
    } else if (expoente % 2 != 0 || intervalo[0] >= 0){
        fesetround (FE_DOWNWARD);
        resultado[0] = pow (intervalo[0], expoente);
        fesetround (FE_UPWARD);
        resultado[1] = pow (intervalo[1], expoente);
    } else if (intervalo[1] < 0){
        fesetround (FE_DOWNWARD);
        resultado[0] = pow (intervalo[1], expoente);
        fesetround (FE_UPWARD);
        resultado[1] = pow (intervalo[0], expoente);
    } else{
        resultado[0] = 0;
        resultado[1] = fmax (pow (intervalo[0], expoente), pow (intervalo[1], expoente));
    }
}

/*Calcula o intervalo que inclui o valor passado como parametro*/
void calculaIntervalo (double valor, double intervalo[2]){
    fesetround (FE_DOWNWARD);
    intervalo[0] = valor;
    intervalo[1] = nextafter (valor, FLT_MAX);
}