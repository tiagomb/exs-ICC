// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#ifndef ___SISTEMAS_H___
#define ___SISTEMAS_H___

#include <stdio.h>
#include "interval.h"

void trocaLinhas (intervalo_t **a, intervalo_t *b, int i, int pivo);

int encontraPivo (intervalo_t **a, int i, int tam);

void gaussComMult (intervalo_t **a, intervalo_t *b, int tam);

void retroSub (intervalo_t **a, intervalo_t *b, intervalo_t *x, int tam);

void calculaResiduo (intervalo_t *coef, intervalo_t *x, intervalo_t *y, int pontos, int tam);

void imprimeMatriz (intervalo_t **a, intervalo_t *b, int tam);

void somatorio (int expoenteCima, int expoenteBaixo, intervalo_t *x, int k, intervalo_t *soma);

void calculaA (intervalo_t **a, int n, int k, intervalo_t *x);

void calculaB (intervalo_t *b, int n, int k, intervalo_t *y, intervalo_t *x);

#endif // ___SISTEMAS_H___