// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#ifndef ___SISTEMASOTIM_H___
#define ___SISTEMASOTIM_H___

#include <stdio.h>
#include "intervalOtim.h"

void trocaLinhas (intervalo_t **a, intervalo_t *b, int i, int pivo);

int encontraPivo (intervalo_t **a, int i, int tam);

void gaussComMult (intervalo_t **a, intervalo_t *b, int tam);

void retroSub (intervalo_t **a, intervalo_t *b, intervalo_t *x, int tam);

void calculaParteResiduo (intervalo_t x, int expoente, intervalo_t coef, intervalo_t r);

void calculaResiduo (intervalo_t *coef, intervalo_t *x, intervalo_t *y, long long int pontos, int tam);

void imprimeMatriz (intervalo_t **a, intervalo_t *b, int tam);

void calculaParte (intervalo_t x, intervalo_t y, int expoente, intervalo_t b, intervalo_t soma);

void calculaAeB (intervalo_t **a, intervalo_t *b, int n, int k, intervalo_t *x, intervalo_t *y);

#endif // ___SISTEMASOTIM_H___