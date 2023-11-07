// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <fenv.h>
#include "interval.h"

/*Todas as funções neste arquivo, com exceção da calculaIntervalo, recebem como parâmetros 3 intervalos: os 2 primeiros serão os operandos
e o terceiro é onde será armazenado o resultado.*/

/*Soma os limites inferiores dos intervalos para dar o limite inferior do resultado e os limites superiores para dar o superior*/
void adicionaIntervalo (intervalo_t intervalo1, intervalo_t intervalo2, intervalo_t *resultado){
    fesetround (FE_DOWNWARD);
    resultado->inicio = intervalo1.inicio + intervalo2.inicio;
    fesetround (FE_UPWARD);
    resultado->fim = intervalo1.fim + intervalo2.fim;
}

/*Subtrai o maior numero do intervalo 2 do menor do intervalo 1 para dar o menor resultado e subtrai o menor do intervalo 2 do maior 
do intervalo 1 para dar o maior resultado*/
void subtraiIntervalo (intervalo_t intervalo1, intervalo_t intervalo2, intervalo_t *resultado){
    fesetround (FE_DOWNWARD);
    resultado->inicio = intervalo1.inicio - intervalo2.fim;
    fesetround (FE_UPWARD);
    resultado->fim = intervalo1.fim - intervalo2.inicio;
}

/*Realiza todas as multiplicações possíveis, selecionando o menor e o maior resultados obtidos para o intervalo*/
void multiplicaIntervalo (intervalo_t intervalo1, intervalo_t intervalo2, intervalo_t *resultado){
    fesetround (FE_DOWNWARD);
    double a = intervalo1.inicio * intervalo2.inicio;
    double b = intervalo1.inicio * intervalo2.fim;
    double c = intervalo1.fim * intervalo2.inicio;
    double d = intervalo1.fim * intervalo2.fim;
    resultado->inicio = fmin (fmin (a, b), fmin (c, d));
    fesetround (FE_UPWARD);
    a = intervalo1.inicio * intervalo2.inicio;
    b = intervalo1.inicio * intervalo2.fim;
    c = intervalo1.fim * intervalo2.inicio;
    d = intervalo1.fim * intervalo2.fim;
    resultado->fim = fmax (fmax (a, b), fmax(c, d));
}

/*Mesma ideia da multiplicaçao. Caso 0 pertença ao intervalo 2, o resultado é um intervalo de -infinito a +infinito.*/
void divideIntervalo (intervalo_t intervalo1, intervalo_t intervalo2, intervalo_t *resultado){
    if(intervalo2.inicio <= 0 && intervalo2.fim >= 0){
        resultado->inicio = -INFINITY;
        resultado->fim = INFINITY;
        return;
    }

    fesetround (FE_DOWNWARD);
    double a = intervalo1.inicio / intervalo2.inicio;
    double b = intervalo1.inicio / intervalo2.fim;
    double c = intervalo1.fim / intervalo2.inicio;
    double d = intervalo1.fim / intervalo2.fim;
    resultado->inicio = fmin (fmin (a, b), fmin (c, d));
    fesetround (FE_UPWARD);
    a = intervalo1.inicio / intervalo2.inicio;
    b = intervalo1.inicio / intervalo2.fim;
    c = intervalo1.fim / intervalo2.inicio;
    d = intervalo1.fim / intervalo2.fim;
    resultado->fim = fmax (fmax (a, b), fmax(c, d));
}

/*Realiza as operações de potenciação conforme explicitado pelo enunciado.*/
void potenciaIntervalo (intervalo_t intervalo, int expoente, intervalo_t *resultado){
    if (expoente == 0){
        resultado->inicio = 1;
        resultado->fim = 1;
    } else if (expoente % 2 != 0 || intervalo.inicio >= 0){
        fesetround (FE_DOWNWARD);
        resultado->inicio = pow (intervalo.inicio, expoente);
        fesetround (FE_UPWARD);
        resultado->fim = pow (intervalo.fim, expoente);
    } else if (intervalo.fim < 0){
        fesetround (FE_DOWNWARD);
        resultado->inicio = pow (intervalo.fim, expoente);
        fesetround (FE_UPWARD);
        resultado->fim = pow (intervalo.inicio, expoente);
    } else{
        resultado->inicio = 0;
        resultado->fim = fmax (pow (intervalo.inicio, expoente), pow (intervalo.fim, expoente));
    }
}

/*Recebe 2 parâmetros: um valor e um intervalo. Calcula o intervalo ao qual esse valor pertence e armazena no intervalo
passado como parâmetro*/
void calculaIntervalo (double valor, intervalo_t *intervalo){
    fesetround (FE_DOWNWARD);
    intervalo->inicio = valor;
    intervalo->fim = nextafter (valor, FLT_MAX);
}